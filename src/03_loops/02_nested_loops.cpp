// =============================================================================
//  03_loops / 02_nested_loops.cpp
//  Lesson: a loop inside a loop, and lining output up in columns
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/03_loops/02_nested_loops.cpp -o nested_loops
//    ./nested_loops
//
// -----------------------------------------------------------------------------
//  LESSON
// -----------------------------------------------------------------------------
//  A nested loop is just a loop whose body happens to contain another loop.
//  The INNER loop runs completely, from start to finish, on every single pass
//  of the outer loop.
//
//        for (int row = 1; row <= 3; ++row) {        // runs 3 times
//            for (int col = 1; col <= 4; ++col) {    // runs 4 times per row
//                std::cout << row << col << ' ';
//            }
//            std::cout << '\n';                      // end of the row
//        }
//
//        11 12 13 14
//        21 22 23 24
//        31 32 33 34
//
//  Total passes through the inner body: 3 * 4 = 12.
//
//  The thing beginners forget: the newline belongs to the OUTER loop. Put it
//  inside the inner loop and every value lands on its own line.
//
//  LINING THINGS UP. Numbers have different widths, so columns go crooked.
//  std::setw(n) from <iomanip> pads the NEXT value out to n characters:
//
//        std::cout << std::setw(4) << 7 << std::setw(4) << 100;
//        //  "   7 100"
//
//  setw affects only the very next thing printed, so you repeat it each time.
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written)
// -----------------------------------------------------------------------------

#include <iomanip>
#include <iostream>

int main() {
    std::cout << "row/col grid:\n";
    for (int row = 1; row <= 3; ++row) {
        for (int col = 1; col <= 4; ++col) {
            std::cout << row << col << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: multiplication table
    // -------------------------------------------------------------------------
    //  Print a 1..9 times table using two nested loops and std::setw(4):
    //
    //         1   2   3   4   5   6   7   8   9
    //         2   4   6   8  10  12  14  16  18
    //         3   6   9  12  15  18  21  24  27
    //         ...
    //         9  18  27  36  45  54  63  72  81

    // TODO: the multiplication table

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: a triangle
    // -------------------------------------------------------------------------
    //  Print a left-aligned triangle of stars, 5 rows tall:
    //
    //      *
    //      **
    //      ***
    //      ****
    //      *****
    //
    //  The trick: the inner loop's LIMIT depends on the outer loop's counter.
    //  Row 1 prints 1 star, row 2 prints 2 stars... so the inner condition
    //  mentions the outer variable.

    // TODO: the triangle

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: a right-aligned triangle (harder)
    // -------------------------------------------------------------------------
    //  Same 5 rows, pushed to the right with spaces:
    //
    //          *
    //         **
    //        ***
    //       ****
    //      *****
    //
    //  Each row needs TWO inner loops one after the other: first print the
    //  spaces, then print the stars. Work out on paper how many spaces row `r`
    //  needs when the triangle is 5 tall, before you write any code.

    // TODO: the right-aligned triangle

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT
// -----------------------------------------------------------------------------
//    row/col grid:
//    11 12 13 14
//    21 22 23 24
//    31 32 33 34
//
//    multiplication table:
//       1   2   3   4   5   6   7   8   9
//       2   4   6   8  10  12  14  16  18
//       3   6   9  12  15  18  21  24  27
//       4   8  12  16  20  24  28  32  36
//       5  10  15  20  25  30  35  40  45
//       6  12  18  24  30  36  42  48  54
//       7  14  21  28  35  42  49  56  63
//       8  16  24  32  40  48  56  64  72
//       9  18  27  36  45  54  63  72  81
//
//    triangle:
//    *
//    **
//    ***
//    ****
//    *****
//
//    right-aligned:
//        *
//       **
//      ***
//     ****
//    *****
