// =============================================================================
//  02_arrays_strings / 01_array_basics.cpp
//  Lesson: fixed-size arrays, indexing, reading and modifying elements
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/02_arrays_strings/01_array_basics.cpp -o array_basics
//    ./array_basics
//
// -----------------------------------------------------------------------------
//  LESSON
// -----------------------------------------------------------------------------
//  An array is a fixed number of values of the same type, stored side by side.
//
//        int scores[5] = {90, 72, 88, 61, 95};
//            ^^^^^^ ^     ^^^^^^^^^^^^^^^^^^^
//            name  size        initial values
//
//  The size is part of the type and can never change. Elements are numbered
//  from ZERO:
//
//        index:    0    1    2    3    4
//                +----+----+----+----+----+
//        scores  | 90 | 72 | 88 | 61 | 95 |
//                +----+----+----+----+----+
//
//        scores[0]  -> 90      (the first element)
//        scores[4]  -> 95      (the last element -- size 5 means last index 4)
//        scores[5]  -> DANGER: out of bounds, undefined behaviour
//
//  Reading and writing use the same [] syntax:
//
//        int first = scores[0];   // read
//        scores[1] = 100;         // write
//
//  To visit every element, count from 0 while the counter is LESS THAN the size:
//
//        for (int i = 0; i < 5; ++i) {
//            std::cout << scores[i] << ' ';
//        }
//
//  Writing the size as a named constant beats sprinkling `5` everywhere:
//
//        constexpr int kSize = 5;
//        int scores[kSize] = { ... };
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written)
// -----------------------------------------------------------------------------

#include <iostream>

int main() {
    constexpr int kSize = 5;
    int scores[kSize] = {90, 72, 88, 61, 95};

    std::cout << "first element : " << scores[0] << '\n';
    std::cout << "last element  : " << scores[kSize - 1] << '\n';

    std::cout << "all elements  : ";
    for (int i = 0; i < kSize; ++i) {
        std::cout << scores[i] << ' ';
    }
    std::cout << '\n';

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: print each element with its index
    // -------------------------------------------------------------------------
    //  Loop over `scores` and print one line per element, like:
    //      scores[0] = 90
    //      scores[1] = 72
    //      ...

    // TODO: write the loop

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: modify elements
    // -------------------------------------------------------------------------
    //  a) Give every student 5 bonus points (add 5 to every element in place).
    //  b) Then set the last element to exactly 100.
    //  c) Print the whole array again on one line, space separated.

    // TODO: bonus points, then fix the last element, then print

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: find the largest value
    // -------------------------------------------------------------------------
    //  Find the biggest number in the array WITHOUT using any library function.
    //
    //  The standard technique:
    //    - assume the first element is the largest so far
    //    - walk the rest of the array; whenever you find something bigger,
    //      remember it instead
    //
    //  Print:  largest = <value>
    //
    //  Bonus: also remember WHICH index it was found at and print that too.

    // TODO: find and print the largest value

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT
// -----------------------------------------------------------------------------
//    first element : 90
//    last element  : 95
//    all elements  : 90 72 88 61 95
//    scores[0] = 90
//    scores[1] = 72
//    scores[2] = 88
//    scores[3] = 61
//    scores[4] = 95
//    after bonus   : 95 77 93 66 100
//    largest = 100 (at index 4)
