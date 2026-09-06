// =============================================================================
//  04_pointers / 02_dereferencing.cpp
//  Lesson: the * operator -- reading and writing through a pointer
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/04_pointers/02_dereferencing.cpp -o deref
//    ./deref
//
// -----------------------------------------------------------------------------
//  LESSON 1: * means "go to that address"
// -----------------------------------------------------------------------------
//  A pointer on its own is just an address -- a house number. DEREFERENCING is
//  walking to the house and looking inside. The operator is *:
//
//        int x = 10;
//        int* p = &x;
//
//        x    -> 10            value
//        &x   -> 0x7ffd1234    address of x
//        p    -> 0x7ffd1234    the address, stored in p
//        *p   -> 10            THE VALUE AT THAT ADDRESS
//
//  Read `*p` out loud as "the thing p points at".
//
//  THE * CHARACTER HAS TWO JOBS. This confuses everyone at first:
//
//        int* p = &x;     // DECLARATION: * is part of the type "pointer to int"
//        std::cout << *p; // EXPRESSION:  * dereferences, giving the value
//
//  Rule of thumb: a * next to a TYPE declares a pointer, a * in front of an
//  existing pointer VARIABLE follows it.
//
// -----------------------------------------------------------------------------
//  LESSON 2: *p is a real place, so you can assign to it
// -----------------------------------------------------------------------------
//  Dereferencing does not just read. Put *p on the LEFT of an = and you write
//  into the original variable:
//
//        int x = 10;
//        int* p = &x;
//        *p = 99;              // reaches through p and changes x
//        std::cout << x;       // prints 99  -- x changed without naming x
//
//  This is the whole point of pointers, and it is why they are powerful and
//  why they are dangerous. Two names now reach the same box:
//
//                p                        x
//        +---------------+        +-----------+
//        |  0x7ffd1234   | -----> |    99     |
//        +---------------+        +-----------+
//                                  ^
//                       *p and x are the SAME box
//
//  Compare carefully:
//        p  = &y;      // change WHICH box p points at (p is reassigned)
//        *p = 5;       // change WHAT IS IN the box (x is modified)
//
//  One character of difference, completely different meaning.
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written)
// -----------------------------------------------------------------------------

#include <iostream>

int main() {
    int x = 10;
    int* p = &x;

    std::cout << "start:  x = " << x << ",  *p = " << *p << '\n';

    *p = 99;  // write through the pointer
    std::cout << "*p = 99 -> x = " << x << ",  *p = " << *p << '\n';

    x = 7;  // write through the variable
    std::cout << "x = 7   -> x = " << x << ",  *p = " << *p << "\n\n";

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: predict, then verify
    // -------------------------------------------------------------------------
    //  Here is a sequence. Write down what you think prints at each step BEFORE
    //  you write any code, then implement it and check.
    //
    int a = 5;
    int b = 20;
    int* q = &a;
    *q = *q + 1;  // (1) what are a and b now?
    std::cout << " a = " << a << ",  b = " << b << '\n';
    q = &b;  // (2) what are a and b now?
    std::cout << " a = " << a << ",  b = " << b << '\n';
    *q = 0;  // (3) what are a and b now?
    std::cout << " a = " << a << ",  b = " << b << '\n';
    //
    //  Print "a = ?, b = ?" after each of the three lines.
    //
    //  YOUR PREDICTIONS:
    //      (1) a = 6  b = 20
    //      (2) a = 6  b = 20
    //      (3) a = 6  b = 0

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: double it through a pointer
    // -------------------------------------------------------------------------
    //  Declare  int score = 21;  and a pointer to it.
    //  WITHOUT mentioning `score` again after the pointer is created, make its
    //  value 42. Then print score to prove it worked.

    // TODO
    int score = 20;
    int* pScore = &score;
    *pScore = *pScore + 22;
    std::cout << score << "\n";

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: a pointer walking an array
    // -------------------------------------------------------------------------
    //  Given  int values[4] = {2, 4, 6, 8};
    //
    //  Loop over the array with an index, and on each pass point a pointer at
    //  the current element (&values[i]) and print through it:
    //
    //      values[0] lives at 0x... and holds 2
    //
    //  Then, using that pointer, add 10 to whatever it points at, and finally
    //  print the whole array to show every element changed.
    //
    //  (We are deliberately NOT using p + 1 style pointer arithmetic yet.
    //   Take the address of each element explicitly with &values[i].)

    // TODO
    int values[4] = {2, 4, 6, 8};
    for (std::size_t i = 0; i < std::size(values); ++i) {
        int* pValue = &values[i];
        std::cout << "values[" << i << "] lives at " << pValue << " and holds " << *pValue << "\n";
        *pValue = *pValue + 10;
    }

    // Print the array values
    std::cout << "after +10: ";

    for (std::size_t i = 0; i < std::size(values); ++i) {
        std::cout << values[i] << " ";
    }

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT (addresses will differ)
// -----------------------------------------------------------------------------
//    start:  x = 10,  *p = 10
//    *p = 99 -> x = 99,  *p = 99
//    x = 7   -> x = 7,  *p = 7
//
//    (1) a = 6, b = 20
//    (2) a = 6, b = 20
//    (3) a = 6, b = 0
//
//    score = 42
//
//    values[0] lives at 0x16b1f2b40 and holds 2
//    values[1] lives at 0x16b1f2b44 and holds 4
//    values[2] lives at 0x16b1f2b48 and holds 6
//    values[3] lives at 0x16b1f2b4c and holds 8
//    after +10 : 12 14 16 18
//
//  Look closely at those four addresses: they go up by 4 each time, because an
//  int is 4 bytes and array elements sit side by side in memory. That is the
//  seed of pointer arithmetic, which comes later.
