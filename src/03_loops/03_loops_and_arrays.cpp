// =============================================================================
//  03_loops / 03_loops_and_arrays.cpp
//  Lesson: loops as the engine that drives array work
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/03_loops/03_loops_and_arrays.cpp -o loops_arrays
//    ./loops_arrays
//
// -----------------------------------------------------------------------------
//  LESSON
// -----------------------------------------------------------------------------
//  Arrays and loops belong together: the array holds the data, the loop is the
//  only way to reach all of it. A handful of patterns cover most of what you
//  will ever do with them.
//
//  1. ACCUMULATE -- fold every element into one running answer.
//
//        int sum = 0;
//        for (int i = 0; i < n; ++i) sum += a[i];
//
//  2. SEARCH -- stop as soon as you find what you want. A `while` loop is a
//     natural fit, because the stopping condition is not just a counter:
//
//        int i = 0;
//        while (i < n && a[i] != target) {   // && means "and"
//            ++i;
//        }
//        // now: either i == n (not found) or a[i] == target (found at i)
//
//     The order of the two tests matters. `i < n` is checked FIRST, so when i
//     runs off the end the second test is never evaluated -- and you never read
//     out of bounds. This is called short-circuit evaluation.
//
//  3. TRANSFORM -- write a new value into every slot.
//
//        for (int i = 0; i < n; ++i) a[i] = a[i] * 2;
//
//  4. PAIR UP -- walk two indexes toward each other from the ends.
//
//        int left = 0, right = n - 1;
//        while (left < right) { ...; ++left; --right; }
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written)
// -----------------------------------------------------------------------------

#include <iostream>

// Prints an array on one line: [3, 1, 4]
void print_array(const int values[], int count) {
    std::cout << '[';
    for (int i = 0; i < count; ++i) {
        std::cout << values[i];
        if (i < count - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

int main() {
    constexpr int kSize = 7;
    int numbers[kSize] = {4, 8, 15, 16, 23, 42, 8};

    std::cout << "numbers      : ";
    print_array(numbers, kSize);

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: sum and running total
    // -------------------------------------------------------------------------
    //  a) Print the running total as you go:    running      : 4 12 27 43 66 108 116
    //     (print the accumulator on every pass through the loop)
    //  b) Then print the final total:            sum          : 116
    //     (one loop gives you both -- do not walk the array twice)

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: linear search
    // -------------------------------------------------------------------------
    //  Write a function above main():
    //
    //      int index_of(const int values[], int count, int target)
    //
    //  It returns the index of the FIRST element equal to target, or -1 when the
    //  target is not there. Returning -1 for "not found" is a very common C++
    //  convention -- get comfortable with it.
    //
    //  Call it and print:
    //      index_of(15) : 2
    //      index_of(99) : -1
    //
    //  Then use it to answer: does 8 appear more than once? (Hint: you only need
    //  a count here, not an index -- write a second small loop.)

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: reverse in place
    // -------------------------------------------------------------------------
    //  Reverse `numbers` WITHOUT making a second array. Use the two-index
    //  pattern from the lesson: swap the outermost pair, step inward, repeat.
    //
    //  To swap two ints you need a temporary:
    //      int tmp = a; a = b; b = tmp;
    //
    //  Then print:  reversed     : [8, 42, 23, 16, 15, 8, 4]
    //
    //  Think about why the loop must stop when left meets right, and what would
    //  happen if you kept going to the end.

    // TODO

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT
// -----------------------------------------------------------------------------
//    numbers      : [4, 8, 15, 16, 23, 42, 8]
//    running      : 4 12 27 43 66 108 116
//    sum          : 116
//    index_of(15) : 2
//    index_of(99) : -1
//    count of 8   : 2
//    reversed     : [8, 42, 23, 16, 15, 8, 4]
