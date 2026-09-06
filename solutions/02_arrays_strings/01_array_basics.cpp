// Solution to src/02_arrays_strings/01_array_basics.cpp
// Lesson: fixed-size arrays, indexing, reading and modifying elements

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

    // Task 1: one line per element, with its index.
    for (int i = 0; i < kSize; ++i) {
        std::cout << "scores[" << i << "] = " << scores[i] << '\n';
    }

    // Task 2: modify in place. scores[i] on the left of = writes to the array.
    for (int i = 0; i < kSize; ++i) {
        scores[i] += 5;
    }
    scores[kSize - 1] = 100;

    std::cout << "after bonus   : ";
    for (int i = 0; i < kSize; ++i) {
        std::cout << scores[i] << ' ';
    }
    std::cout << '\n';

    // Task 3: largest value, by hand.
    // Start by assuming element 0 wins, then look for anything better.
    int largest = scores[0];
    int largest_index = 0;
    for (int i = 1; i < kSize; ++i) {
        if (scores[i] > largest) {
            largest = scores[i];
            largest_index = i;
        }
    }
    std::cout << "largest = " << largest << " (at index " << largest_index << ")\n";

    return 0;
}
