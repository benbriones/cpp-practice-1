// =============================================================================
//  07_pointers_advanced / 04_dynamic_memory.cpp
//  Lesson: new and delete -- memory whose lifetime YOU decide
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/07_pointers_advanced/04_dynamic_memory.cpp -o dynamic_mem
//    ./dynamic_mem
//
//  Run this one with the sanitizers on -- ./run does it for you. Half of this
//  lesson is reading their reports.
//
// -----------------------------------------------------------------------------
//  LESSON 1: two places memory lives
// -----------------------------------------------------------------------------
//  THE STACK -- everything you have declared so far:
//
//        void f() {
//            int x = 5;        // born here
//        }                     // dies here, automatically, always
//
//  Fast, automatic, and strictly scope-shaped. Size must be known at compile
//  time, and the memory is gone the instant the function returns.
//
//  THE HEAP -- memory you ask for explicitly:
//
//        int* p = new int(42);   // born here
//        ...
//        delete p;               // dies here -- because YOU said so
//
//  Slower, unlimited-ish, and its lifetime is whatever you choose. You need it
//  when the size is only known at runtime, or when the data must outlive the
//  function that created it.
//
// -----------------------------------------------------------------------------
//  LESSON 2: the syntax, and the pairing rule
// -----------------------------------------------------------------------------
//        int*  one  = new int(42);            delete   one;
//        int*  many = new int[n];             delete[] many;
//        Node* node = new Node{5, nullptr};   delete   node;
//
//  Two rules, no exceptions:
//    - every  new    is matched by exactly one  delete
//    - every  new[]  is matched by exactly one  delete[]
//
//  Mixing them (new[] freed with plain delete) is undefined behaviour.
//
// -----------------------------------------------------------------------------
//  LESSON 3: the three bugs this creates
// -----------------------------------------------------------------------------
//  1. LEAK -- you never delete. The memory is still allocated but nothing points
//     at it any more, so it can never be freed. A long-running program that
//     leaks in a loop eventually dies.
//
//         int* p = new int(1);
//         p = new int(2);        // the first int is now unreachable. Leaked.
//
//  2. USE-AFTER-FREE (dangling pointer) -- you delete, then use it anyway. The
//     pointer still holds the old address; that memory now belongs to someone
//     else.
//
//         delete p;
//         std::cout << *p;       // reads memory that is no longer yours
//         p = nullptr;           // <- the habit that prevents this
//
//  3. DOUBLE FREE -- you delete the same block twice. Corrupts the allocator.
//
//  AddressSanitizer catches (2) and (3) loudly, with a stack trace naming the
//  line that freed it. Leaks are the sneaky one: on macOS nothing complains at
//  all -- your program just quietly uses more and more memory. That asymmetry is
//  exactly why the discipline matters.
//
// -----------------------------------------------------------------------------
//  LESSON 4: this is not how you will write C++
// -----------------------------------------------------------------------------
//  Modern C++ code hardly ever contains a bare `new` or `delete` -- std::vector,
//  std::string and std::unique_ptr do it for you, correctly, every time. You are
//  learning it here because those tools are built out of exactly this, and
//  because you cannot debug what you cannot picture. Files 05 and 06 put the
//  training wheels back on.
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written)
// -----------------------------------------------------------------------------

#include <cstddef>
#include <iostream>

int main() {
    int local = 7;              // stack: freed automatically at the closing brace
    int* heap = new int(42);    // heap: freed when I say so

    std::cout << "local = " << local << ", *heap = " << *heap << '\n';

    delete heap;
    heap = nullptr;  // cheap habit: a null pointer cannot be used by accident
    std::cout << "after delete, heap is " << (heap == nullptr ? "null" : "dangling") << "\n\n";

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: an array whose size is a runtime value
    // -------------------------------------------------------------------------
    //  Write above main():
    //
    //      int* make_squares(int n)     // caller owns the result, must delete[]
    //
    //  It allocates n ints on the heap, fills element i with i * i, and returns
    //  the pointer. Return nullptr for n <= 0.
    //
    //  Two things to notice:
    //    - `new int[n]` wants an unsigned size, so with -Wconversion on you will
    //      need  new int[static_cast<std::size_t>(n)]  once you have guarded n
    //    - the comment on the signature is the ONLY thing telling the caller it
    //      must free this. Nothing enforces it. Hold that thought until file 06.
    //
    //  Print it with a small helper:
    //
    //      void print_array(const int* values, int count, const char* label)
    //
    //  squares  : 0 1 4 9 16 25

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: grow the array
    // -------------------------------------------------------------------------
    //  Heap arrays cannot be resized -- you make a bigger one and move over.
    //
    //      int* grow(int* old_data, int old_size, int new_size)
    //
    //    - allocate new_size ints
    //    - copy the first old_size across, zero-fill the rest
    //    - delete[] the old block
    //    - return the new one
    //
    //      grown    : 0 1 4 9 16 25 0 0 0
    //
    //  Get the order wrong -- return before deleting, or delete before copying --
    //  and you have written a leak or a use-after-free. This function is a
    //  miniature of what std::vector does on every push_back that outgrows its
    //  capacity. Remember to delete[] the final array yourself.

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: a linked list, one allocation per node
    // -------------------------------------------------------------------------
    //  This is the exercise where pointers stop being an abstraction.
    //
    //      struct Node {
    //          int   value;
    //          Node* next;      // a struct containing a pointer to its own type
    //      };
    //
    //          head
    //           |
    //           v
    //        +----+----+   +----+----+   +----+----+
    //        | 40 |  o-+-->| 30 |  o-+-->| 20 |  / |     / = nullptr
    //        +----+----+   +----+----+   +----+----+
    //
    //  Write three functions:
    //
    //      Node* push_front(Node* head, int value)   // returns the new head
    //      void  print_list(const Node* head)
    //      void  free_list(Node* head)
    //
    //  Build a list of 40, 30, 20, 10 by pushing 10, 20, 30, 40 onto an initially
    //  null head, print it, then free every node.
    //
    //      list     : 40 -> 30 -> 20 -> 10 -> null
    //
    //  The trap in free_list, and it catches everybody once:
    //
    //      delete head;
    //      head = head->next;    // reading a node you already deleted!
    //
    //  Save `next` in a local BEFORE the delete. Run it under the sanitizers with
    //  the wrong order once, deliberately, and read the report.

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 4: meet the sanitizers
    // -------------------------------------------------------------------------
    //  Uncomment each of these in turn, run, then re-comment. Two of them abort
    //  with a detailed report; one of them says nothing at all. Knowing which is
    //  which is the point of the exercise.
    //
    //      // int* leaked = new int[100];   // leak
    //      // leaked[0] = 1;
    //
    //      // int* dangling = new int(5);
    //      // delete dangling;
    //      // std::cout << *dangling;       // use-after-free
    //
    //      // int* twice = new int(5);
    //      // delete twice;
    //      // delete twice;                 // double free

    // TODO

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT
// -----------------------------------------------------------------------------
//    local = 7, *heap = 42
//    after delete, heap is null
//
//    squares  : 0 1 4 9 16 25
//    grown    : 0 1 4 9 16 25 0 0 0
//    list     : 40 -> 30 -> 20 -> 10 -> null
//    list freed
