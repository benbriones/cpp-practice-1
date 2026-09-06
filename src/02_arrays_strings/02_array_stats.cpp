// =============================================================================
//  02_arrays_strings / 02_array_stats.cpp
//  Lesson: accumulating over an array, passing arrays to functions, averages
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/02_arrays_strings/02_array_stats.cpp -o array_stats
//    ./array_stats
//
// -----------------------------------------------------------------------------
//  LESSON
// -----------------------------------------------------------------------------
//  ACCUMULATING. Most array work follows the same shape: start with an answer
//  that is true for "nothing seen yet", then fold in one element at a time.
//
//        int sum = 0;                     // sum of no numbers is 0
//        for (int i = 0; i < n; ++i) {
//            sum += values[i];            // sum = sum + values[i]
//        }
//
//  PASSING AN ARRAY TO A FUNCTION. An array does not carry its size around, so
//  you must pass the size as a second parameter:
//
//        int sum_of(const int values[], int count) { ... }
//                   ^^^^^                 ^^^^^
//              const = "I promise not to modify it"
//
//  AVERAGES AND INTEGER DIVISION. sum and count are both ints, so `sum / count`
//  throws away the fraction. Turn one side into a double first:
//
//        double average = static_cast<double>(sum) / count;
//
//  static_cast<double>(x) means "treat x as a double". You will use it a lot.
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written)
// -----------------------------------------------------------------------------

#include <iostream>

// Adds up every element and returns the total.
int sum_of(const int values[], int count) {
    int sum = 0;
    for (int i = 0; i < count; ++i) {
        sum += values[i];
    }
    return sum;
}

// -----------------------------------------------------------------------------
//  YOUR TASK 1: average_of
// -----------------------------------------------------------------------------
//  Return the average of the first `count` elements as a double.
//  You may call sum_of() -- reusing a function you already trust is good style.
//  Careful with integer division, and think about what to return if count is 0.
double average_of(const int values[], int count) {
    // TODO
    return 0.0;
}

// -----------------------------------------------------------------------------
//  YOUR TASK 2: smallest_of
// -----------------------------------------------------------------------------
//  Return the smallest element. Same technique as "largest" in the last file,
//  flipped around: assume the first element wins, then look for anything smaller.
int smallest_of(const int values[], int count) {
    // TODO
    return 0;
}

// -----------------------------------------------------------------------------
//  YOUR TASK 3: count_above
// -----------------------------------------------------------------------------
//  Return how many elements are strictly greater than `threshold`.
//  This is accumulating again -- but the accumulator is a counter, not a sum.
int count_above(const int values[], int count, int threshold) {
    // TODO
    return 0;
}

int main() {
    constexpr int kSize = 8;
    int temps[kSize] = {14, 21, 19, 25, 30, 12, 22, 27};

    std::cout << "readings :";
    for (int i = 0; i < kSize; ++i) {
        std::cout << ' ' << temps[i];
    }
    std::cout << '\n';

    std::cout << "sum      : " << sum_of(temps, kSize) << '\n';
    std::cout << "average  : " << average_of(temps, kSize) << '\n';
    std::cout << "smallest : " << smallest_of(temps, kSize) << '\n';

    // -------------------------------------------------------------------------
    //  YOUR TASK 4
    // -------------------------------------------------------------------------
    //  Print how many readings are above the average, in this format:
    //
    //      above average (21.25): 4 of 8
    //
    //  Compute the average once into a variable, then use it twice -- do not
    //  call average_of() over and over inside a loop.
    //
    //  count_above takes an int threshold but the average is a double. Decide
    //  what you want here and say it explicitly with a static_cast.

    // TODO: print the "above average" line

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT
// -----------------------------------------------------------------------------
//    readings : 14 21 19 25 30 12 22 27
//    sum      : 170
//    average  : 21.25
//    smallest : 12
//    above average (21.25): 4 of 8
