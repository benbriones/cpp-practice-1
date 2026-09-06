// =============================================================================
//  04_pointers / 04_pointers_in_functions.cpp
//  Lesson: passing pointers to functions so a function can change your variables
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/04_pointers/04_pointers_in_functions.cpp -o ptr_functions
//    ./ptr_functions
//
// -----------------------------------------------------------------------------
//  LESSON 1: arguments are COPIED
// -----------------------------------------------------------------------------
//  By default C++ passes arguments BY VALUE -- the function gets its own copy,
//  and changing the copy does nothing to your original:
//
//        void try_to_double(int n) {   // n is a COPY
//            n = n * 2;                // only the copy changes
//        }
//
//        int score = 10;
//        try_to_double(score);
//        std::cout << score;           // still 10 !
//
//              score (in main)        n (inside the function)
//              +--------+             +--------+
//              |   10   |   copy -->  |   20   |   <- discarded when it returns
//              +--------+             +--------+
//
//  This surprises everyone once. Then it never surprises you again.
//
// -----------------------------------------------------------------------------
//  LESSON 2: pass the ADDRESS instead
// -----------------------------------------------------------------------------
//  If you hand over the address, the function can reach back into your variable:
//
//        void really_double(int* n) {   // n is a copy of the ADDRESS...
//            *n = *n * 2;               // ...but *n is the ORIGINAL box
//        }
//
//        int score = 10;
//        really_double(&score);         // note the & at the call site
//        std::cout << score;            // 20
//
//              score (in main)        n (inside the function)
//              +--------+             +---------------+
//              |   20   | <---------- | address of    |
//              +--------+             | score         |
//                   ^                 +---------------+
//                   +-- *n reaches all the way back here
//
//  The pointer itself is still copied -- that part has not changed. What is new
//  is that a copy of an address still leads to the same one box.
//
//  Three habits that come with this:
//    - the CALLER writes & at the call site, which is a visible signal that the
//      variable may be modified
//    - the FUNCTION must check for nullptr before dereferencing
//    - if a function only READS, take `const int* p` so the compiler enforces it
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written -- run it and compare the two)
// -----------------------------------------------------------------------------

#include <iostream>

void try_to_double(int n) {
    n = n * 2;  // changes the copy only
}

void really_double(int* n) {
    if (n == nullptr) {
        return;  // always guard before dereferencing
    }
    *n = *n * 2;
}

int main() {
    int score = 10;

    try_to_double(score);
    std::cout << "after try_to_double(score)  : " << score << "  <- unchanged\n";

    really_double(&score);
    std::cout << "after really_double(&score) : " << score << "  <- changed\n\n";

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: swap
    // -------------------------------------------------------------------------
    //  Write:   void swap_ints(int* a, int* b)
    //
    //  It exchanges the two values the pointers point at. Guard against either
    //  one being null. You will need a temporary variable -- think about whether
    //  the temporary should be an int or an int*.
    //
    //      int x = 1, y = 2;
    //      swap_ints(&x, &y);
    //      // x is 2, y is 1
    //
    //  Common wrong answer to think through: what does this do, and why is it
    //  useless to the caller?
    //
    //      int* tmp = a; a = b; b = tmp;

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: returning two things at once
    // -------------------------------------------------------------------------
    //  A function can only return one value -- unless you hand it somewhere to
    //  put the extras. This is called an "out parameter".
    //
    //  Write:   void min_and_max(const int values[], int count, int* out_min, int* out_max)
    //
    //  It walks the array once and writes the smallest into *out_min and the
    //  largest into *out_max. Notice `values` is const (read only) while the two
    //  out parameters are not -- the signature documents exactly what the
    //  function will and will not touch.
    //
    //  Test with: int data[6] = {19, 4, 27, 8, 33, 12};
    //  Print:     min = 4, max = 33

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: reporting success through a pointer
    // -------------------------------------------------------------------------
    //  Integer division by zero crashes. Write a function that refuses to:
    //
    //      bool safe_divide(int a, int b, int* out_result)
    //
    //    - if b is 0, return false and leave *out_result alone
    //    - if out_result is null, return false (nothing to write to)
    //    - otherwise write a / b into *out_result and return true
    //
    //  Call it twice and print:
    //      10 / 2 = 5
    //      10 / 0 -> failed
    //
    //  This pattern -- "return whether it worked, deliver the answer through a
    //  pointer" -- shows up constantly in real C and C++ code.

    // TODO

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT
// -----------------------------------------------------------------------------
//    after try_to_double(score)  : 10  <- unchanged
//    after really_double(&score) : 20  <- changed
//
//    before swap: x = 1, y = 2
//    after swap : x = 2, y = 1
//    min = 4, max = 33
//    10 / 2 = 5
//    10 / 0 -> failed
