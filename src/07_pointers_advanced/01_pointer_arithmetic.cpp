// =============================================================================
//  07_pointers_advanced / 01_pointer_arithmetic.cpp
//  Lesson: doing arithmetic on pointers, and what an array really is
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/07_pointers_advanced/01_pointer_arithmetic.cpp -o ptr_arith
//    ./ptr_arith
//
//  In 04_pointers a pointer always pointed at ONE thing. From here on it points
//  at one thing that happens to sit in a row of things -- and that changes what
//  you can do with it.
//
// -----------------------------------------------------------------------------
//  LESSON 1: an array name IS a pointer to its first element
// -----------------------------------------------------------------------------
//        int data[5] = {10, 20, 30, 40, 50};
//
//              data[0]  data[1]  data[2]  data[3]  data[4]
//              +-----+  +-----+  +-----+  +-----+  +-----+
//              |  10 |  |  20 |  |  30 |  |  40 |  |  50 |
//              +-----+  +-----+  +-----+  +-----+  +-----+
//              ^                                          ^
//              data                                       data + 5
//              (== &data[0])                              (one past the end)
//
//  Used in almost any expression, `data` decays into `&data[0]`, so this works:
//
//        int* p = data;        // no & needed -- the array decays
//        std::cout << *p;      // 10
//
// -----------------------------------------------------------------------------
//  LESSON 2: p + 1 means "the next ELEMENT", not "the next byte"
// -----------------------------------------------------------------------------
//  Pointer arithmetic is scaled by the size of the pointed-at type. For an int*
//  on a typical machine, p + 1 is 4 bytes further along; for a char* it is 1.
//  You never write the sizeof yourself -- the type already carries it.
//
//  Which is the whole secret behind subscripting:
//
//        data[i]   is defined as   *(data + i)
//
//  They are the same expression. (Amusing consequence: i[data] compiles and
//  does the same thing. Never write that.)
//
// -----------------------------------------------------------------------------
//  LESSON 3: half-open ranges [begin, end)
// -----------------------------------------------------------------------------
//  C++ describes a stretch of elements with two pointers: the first element,
//  and ONE PAST the last. `end` is a legal address to compute and compare, and
//  illegal to dereference.
//
//        for (const int* p = begin; p != end; ++p)   <- the standard shape
//
//  Why one-past-the-end rather than "the last element"?
//    - end - begin is exactly the number of elements
//    - an empty range is just begin == end, no special case
//    - no subtraction in the loop condition to get wrong
//
//  This is precisely how every STL algorithm and every iterator works. Learn the
//  shape here with raw pointers and the rest of the library comes free.
//
// -----------------------------------------------------------------------------
//  LESSON 4: the decay trap
// -----------------------------------------------------------------------------
//        void f(int values[]) {          // this is really int* values
//            sizeof(values);             // size of a POINTER (8), not the array
//        }
//
//  An array passed to a function loses its length. That is why every function
//  you have written so far takes a `count` alongside the array -- the length is
//  not smuggled in with it. Passing begin/end pointers is the other way to say
//  the same thing.
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written -- run it first)
// -----------------------------------------------------------------------------

#include <cstddef>
#include <iostream>

int main() {
    int data[5] = {10, 20, 30, 40, 50};

    const int* first = data;  // decay: no & needed
    std::cout << "data     -> " << static_cast<const void*>(first) << '\n';
    std::cout << "data + 1 -> " << static_cast<const void*>(first + 1) << '\n';
    std::cout << "step     =  " << (reinterpret_cast<const char*>(first + 1) -
                                    reinterpret_cast<const char*>(first))
              << " bytes = sizeof(int)\n\n";

    for (int i = 0; i < 5; ++i) {
        std::cout << "data[" << i << "] = " << data[i]
                  << "   *(data + " << i << ") = " << *(data + i) << '\n';
    }
    std::cout << '\n';

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: sum a range
    // -------------------------------------------------------------------------
    //  Write above main():
    //
    //      int sum_range(const int* begin, const int* end)
    //
    //  It adds up everything in [begin, end) -- no index variable anywhere, just
    //  a pointer that walks. Use `p != end` rather than `p < end`; that is the
    //  habit iterators require later.
    //
    //  In main, set up:
    //      int* begin = data;
    //      int* end   = data + 5;
    //
    //  and print the element count (end - begin), the whole sum, and the sum of
    //  just the tail -- sum_range(begin + 2, end). Notice you got a "sub-array"
    //  for free, without copying anything.

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: find, the STL way
    // -------------------------------------------------------------------------
    //  Write:
    //
    //      const int* find_value(const int* begin, const int* end, int target)
    //
    //  Return a pointer to the first match, or `end` if there is none. Then the
    //  caller writes:
    //
    //      const int* hit = find_value(begin, end, 30);
    //      if (hit != end) { ... }
    //
    //  and gets the index back with `hit - begin`. Two questions worth sitting
    //  with: why return `end` rather than nullptr for "not found", and why is
    //  the return type const int* rather than int*?

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: reverse with two pointers
    // -------------------------------------------------------------------------
    //  Write:
    //
    //      void reverse_range(int* begin, int* end)
    //
    //  One pointer starts at the front, one at the last element (end - 1), and
    //  they swap and step towards each other until they meet.
    //
    //  Careful: for an EMPTY range, end - 1 computes an address before the array
    //  even starts -- undefined behaviour, even though you never read it. Guard
    //  with `if (begin == end) return;` first.
    //
    //  Print the array afterwards by walking it with a pointer, not an index.

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 4: how strlen works
    // -------------------------------------------------------------------------
    //  Write:
    //
    //      std::size_t c_string_length(const char* s)
    //
    //  A C string is a char array ending in the character '\0'. There is no
    //  stored length: you walk until you hit the terminator, then the answer is
    //  how far you walked (p - s).
    //
    //  Test it with:  const char* word = "pointers";   -> 8
    //
    //  This is the one place where a pointer alone is enough, with no count and
    //  no end pointer -- the data carries its own end marker. It is also why a
    //  missing '\0' walks off into memory that is not yours.

    // TODO

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT   (your addresses will be different -- the step will not)
// -----------------------------------------------------------------------------
//    data     -> 0x16ee26620
//    data + 1 -> 0x16ee26624
//    step     =  4 bytes = sizeof(int)
//
//    data[0] = 10   *(data + 0) = 10
//    data[1] = 20   *(data + 1) = 20
//    data[2] = 30   *(data + 2) = 30
//    data[3] = 40   *(data + 3) = 40
//    data[4] = 50   *(data + 4) = 50
//
//    elements   : 5
//    sum_range  : 150
//    sum of tail: 120
//    found 30 at index 2
//    99 found? no
//    reversed   : 50 40 30 20 10
//    length of "pointers" = 8
