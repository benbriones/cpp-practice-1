// =============================================================================
//  07_pointers_advanced / 05_ownership_raii.cpp
//  Lesson: ownership, RAII, and the rule of three
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/07_pointers_advanced/05_ownership_raii.cpp -o raii
//    ./raii
//
// -----------------------------------------------------------------------------
//  LESSON 1: the question a raw pointer cannot answer
// -----------------------------------------------------------------------------
//        int* p = make_squares(6);
//
//  Who calls delete[]? Nothing in that line says. The type `int*` is the same
//  whether the pointer owns the memory, borrows it, or points at a stack array.
//  In file 04 the answer lived in a comment -- and comments are not checked.
//
//  OWNERSHIP is the answer to "whose job is it to clean this up". Every resource
//  needs exactly one owner. The whole design problem is making that visible.
//
// -----------------------------------------------------------------------------
//  LESSON 2: RAII
// -----------------------------------------------------------------------------
//  Resource Acquisition Is Initialisation -- a terrible name for a great idea:
//
//        the CONSTRUCTOR acquires the resource
//        the DESTRUCTOR releases it
//
//  Because C++ guarantees the destructor runs when the object goes out of scope,
//  cleanup stops being something you remember and becomes something the language
//  does. And it holds on EVERY exit path:
//
//        {
//            IntBuffer b(1000);
//            if (bad) return;        // freed
//            if (worse) throw ...;   // freed
//            ...
//        }                           // freed
//
//  Try getting all three right by hand with delete[] and you will see the value.
//  This is also how std::string, std::fstream, std::lock_guard and every other
//  resource-holding class in the standard library works.
//
// -----------------------------------------------------------------------------
//  LESSON 3: the copy problem
// -----------------------------------------------------------------------------
//  The moment a class owns a raw pointer, the compiler's free copy constructor
//  becomes a bug factory. It copies members one by one -- and copying a pointer
//  gives you two pointers to ONE block:
//
//        IntBuffer a(3);        a.data_ ---> [ 0 0 0 ]
//        IntBuffer b = a;       b.data_ ---^
//
//        ~b  ->  delete[] that block
//        ~a  ->  delete[] the same block again        -> DOUBLE FREE
//
//  So: if your class needs a destructor, it almost certainly also needs to say
//  what copying means. That is the RULE OF THREE:
//
//        destructor          how to release
//        copy constructor    how to duplicate
//        copy assignment     how to release, then duplicate
//
//  You have three options, and picking one deliberately is the job:
//    - DEEP COPY: each object gets its own block  (what you will write below)
//    - FORBID:    `IntBuffer(const IntBuffer&) = delete;`
//    - SHARE:     reference counting -- std::shared_ptr, file 06
//
//  (C++11 added move construction and move assignment, making it the "rule of
//   five", and the "rule of zero" says the happiest classes hold members that
//   manage themselves so they need none of the five. File 06 gets there.)
//
// -----------------------------------------------------------------------------
//  YOUR TASKS -- fill in the class below, then run it
// -----------------------------------------------------------------------------

#include <cstddef>
#include <iostream>
#include <stdexcept>

class IntBuffer {
public:
    // Given: the constructor acquires the resource.
    explicit IntBuffer(int size)
        : size_(size), data_(nullptr) {
        if (size <= 0) {
            throw std::invalid_argument("IntBuffer size must be positive");
        }
        data_ = new int[static_cast<std::size_t>(size)]();  // () zero-initialises
        std::cout << "  [ctor] allocated " << size_ << " ints\n";
    }

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: the destructor
    // -------------------------------------------------------------------------
    //  Write ~IntBuffer(). It prints
    //        [dtor] freeing N ints
    //  and then delete[]s data_. One new[] up there, one delete[] here, and the
    //  caller can no longer get the pairing wrong -- there is nothing for them
    //  to pair.
    //
    //  Build and run BEFORE writing it, with the sanitizers on. On Linux you get
    //  a leak report; on macOS you get silence. Then write it.

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: access with a bounds check
    // -------------------------------------------------------------------------
    //  Write three members:
    //
    //      int& at(int index);          // throws std::out_of_range if bad
    //      int  at(int index) const;    // the read-only overload
    //      int  size() const;
    //
    //  Why two versions of at()? The non-const one returns int& so callers can
    //  write:  buffer.at(0) = 42;  The const one exists so a `const IntBuffer&`
    //  can still be read. Overloading on constness like this is standard
    //  practice -- std::vector does exactly the same.
    //
    //  Also write:
    //      void print(const char* label) const;

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: the rule of three
    // -------------------------------------------------------------------------
    //  First, prove the problem exists. Temporarily add this to main:
    //
    //      IntBuffer a(3);
    //      IntBuffer b = a;        // compiler's default copy: shares the pointer
    //
    //  and run it under the sanitizers. Read the report -- it will name a double
    //  free, and point at your destructor. That is the compiler-generated copy
    //  constructor doing precisely what Lesson 3 describes.
    //
    //  Now fix it. Write:
    //
    //      IntBuffer(const IntBuffer& other);              // deep copy
    //      IntBuffer& operator=(const IntBuffer& other);   // deep copy assign
    //
    //  Three things the assignment operator must get right, and each one is a
    //  classic interview question:
    //    - self-assignment (`x = x`, usually via a reference or two pointers to
    //      the same object) must not destroy the data it is about to copy
    //    - the old block must be freed, or you leak
    //    - allocate the new block BEFORE deleting the old one, so that if the
    //      allocation throws, the object is still intact
    //    - return *this, so that a = b = c works

    // TODO

private:
    int size_;   // declared before data_, so it is initialised first
    int* data_;
};

int main() {
    std::cout << "-- scope opens --\n";
    {
        IntBuffer buffer(5);

        // ---------------------------------------------------------------------
        //  Once the tasks above are done, exercise them here:
        //    - fill buffer with (i + 1) * 3 using at()
        //    - copy it, modify the copy's element 0 to 999, print both, and
        //      confirm the original did not change (that is what makes it deep)
        //    - copy-assign into a differently-sized IntBuffer
        //    - bind a reference to one buffer and assign it to itself
        //    - call buffer.at(9) inside a try block and catch std::out_of_range
        // ---------------------------------------------------------------------

        // TODO

        std::cout << "-- scope closes, destructors run in reverse order --\n";
    }
    std::cout << "-- everything freed, no delete written by the caller --\n";

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT
// -----------------------------------------------------------------------------
//    -- scope opens --
//      [ctor] allocated 5 ints
//    buffer   : 3 6 9 12 15
//      [copy ctor] deep-copied 5 ints
//    copy     : 999 6 9 12 15
//    original : 3 6 9 12 15
//      [ctor] allocated 2 ints
//      [copy assign] deep-copied 5 ints
//    assigned : 3 6 9 12 15
//    self-assigned: 3 6 9 12 15
//    caught: IntBuffer index out of range
//    -- scope closes, destructors run in reverse order --
//      [dtor] freeing 5 ints
//      [dtor] freeing 5 ints
//      [dtor] freeing 5 ints
//    -- everything freed, no delete written by the caller --
