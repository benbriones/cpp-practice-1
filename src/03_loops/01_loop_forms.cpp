// =============================================================================
//  03_loops / 01_loop_forms.cpp
//  Lesson: for, while, do-while -- three shapes of the same idea
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/03_loops/01_loop_forms.cpp -o loop_forms
//    ./loop_forms
//
// -----------------------------------------------------------------------------
//  LESSON
// -----------------------------------------------------------------------------
//  Every loop needs three things: somewhere to START, a condition that says
//  whether to KEEP GOING, and a STEP that makes progress toward stopping.
//  The three loop forms just arrange those parts differently.
//
//  FOR -- all three parts on one line. Use it when you know the count.
//
//        for (int i = 1; i <= 5; ++i) {
//        //   ^^^^^^^^^  ^^^^^^  ^^^
//        //     start    keep?   step
//            std::cout << i;
//        }
//        // prints 12345
//
//  WHILE -- condition only. Use it when you loop until something happens.
//
//        int n = 27;
//        while (n > 1) {
//            n = n / 2;          // the step is up to you; forget it and the
//        }                       // loop never ends
//
//  DO-WHILE -- the body runs FIRST, then the condition is checked. Use it when
//  the body must happen at least once. Note the semicolon after while(...).
//
//        int guess = 0;
//        do {
//            std::cin >> guess;      // always ask at least once
//        } while (guess != 7);
//
//  ++i adds one to i. i += 3 adds three. i-- subtracts one.
//
//  Two extra keywords, useful inside any loop:
//        break;      leave the loop right now
//        continue;   skip the rest of this pass and start the next one
//
//  The modulo operator % gives the REMAINDER of a division, and it is the tool
//  for "is this divisible by":
//        15 % 3  ->  0     (so 15 is divisible by 3)
//        16 % 3  ->  1
//        n % 2 == 0        (n is even)
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written)
// -----------------------------------------------------------------------------

#include <iostream>

int main() {
    std::cout << "for   : ";
    for (int i = 1; i <= 5; ++i) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    std::cout << "while : ";
    int n = 5;
    while (n > 0) {
        std::cout << n << ' ';
        --n;
    }
    std::cout << '\n';

    std::cout << "do    : ";
    int k = 99;
    do {
        std::cout << k << ' ';  // runs once even though 99 > 3 is already false
        ++k;
    } while (k < 3);
    std::cout << '\n';

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: count by fives
    // -------------------------------------------------------------------------
    //  Print every multiple of 5 from 5 to 50 on one line, space separated:
    //      fives : 5 10 15 20 25 30 35 40 45 50
    //  Do it twice -- once with a for loop, once with a while loop -- so you can
    //  see they are the same machinery.

    // TODO: for-loop version
    for (int i = 1; i <= 50; ++i) {
        if (i % 5 == 0) {
            std::cout << i << " ";
        }
    }

    std::cout << "\n";
    // TODO: while-loop version
    int i = 1;
    while (i < 51) {
        if (i % 5 == 0) {
            std::cout << i << " ";
        }
        ++i;
    }

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: the 1 to 100 report
    // -------------------------------------------------------------------------
    //  Loop from 1 through 100 and print ONE line per number, but only for the
    //  numbers that are interesting:
    //
    //      - divisible by 15 -> print  "<n>: fizzbuzz"
    //      - divisible by 3  -> print  "<n>: fizz"
    //      - divisible by 5  -> print  "<n>: buzz"
    //      - anything else   -> print nothing at all
    //
    //  Think carefully about the ORDER of your if / else if branches. 15 is
    //  divisible by 3 as well, so if you test 3 first you will never see
    //  "fizzbuzz". Getting this right is the whole point of the exercise.
    //
    //  Then, at the end, print how many numbers you actually printed:
    //      interesting numbers: 47

    // TODO: the 1..100 loop

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: sum until
    // -------------------------------------------------------------------------
    //  Using a while loop, add up 1 + 2 + 3 + ... and stop as soon as the
    //  running total goes over 100. Print the total and how many numbers it took:
    //      sum 105 after adding 14 numbers

    // TODO: the "sum until" loop

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT (the middle of the fizzbuzz block is trimmed here)
// -----------------------------------------------------------------------------
//    for   : 1 2 3 4 5
//    while : 5 4 3 2 1
//    do    : 99
//    fives : 5 10 15 20 25 30 35 40 45 50
//    fives : 5 10 15 20 25 30 35 40 45 50
//    3: fizz
//    5: buzz
//    6: fizz
//    9: fizz
//    10: buzz
//    12: fizz
//    15: fizzbuzz
//    ...
//    100: buzz
//    interesting numbers: 47
//    sum 105 after adding 14 numbers
