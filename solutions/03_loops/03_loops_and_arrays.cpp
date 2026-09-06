// Solution to src/03_loops/03_loops_and_arrays.cpp
// Lesson: loops as the engine that drives array work

#include <iostream>

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

// Returns the index of the first match, or -1 for "not found".
int index_of(const int values[], int count, int target) {
    int i = 0;
    // `i < count` is tested FIRST, so values[i] is never read out of bounds.
    while (i < count && values[i] != target) {
        ++i;
    }
    return (i < count) ? i : -1;
}

int count_of(const int values[], int count, int target) {
    int found = 0;
    for (int i = 0; i < count; ++i) {
        if (values[i] == target) {
            ++found;
        }
    }
    return found;
}

int main() {
    constexpr int kSize = 7;
    int numbers[kSize] = {4, 8, 15, 16, 23, 42, 8};

    std::cout << "numbers      : ";
    print_array(numbers, kSize);

    // Task 1: one pass gives both the total and the running total.
    int sum = 0;
    std::cout << "running      : ";
    for (int i = 0; i < kSize; ++i) {
        sum += numbers[i];
        std::cout << sum << ' ';
    }
    std::cout << '\n';
    std::cout << "sum          : " << sum << '\n';

    // Task 2
    std::cout << "index_of(15) : " << index_of(numbers, kSize, 15) << '\n';
    std::cout << "index_of(99) : " << index_of(numbers, kSize, 99) << '\n';
    std::cout << "count of 8   : " << count_of(numbers, kSize, 8) << '\n';

    // Task 3: reverse in place with two indexes walking toward each other.
    // They must stop when they meet; carrying on to the end would swap every
    // pair back a second time and leave the array unchanged.
    int left = 0;
    int right = kSize - 1;
    while (left < right) {
        int tmp = numbers[left];
        numbers[left] = numbers[right];
        numbers[right] = tmp;
        ++left;
        --right;
    }

    std::cout << "reversed     : ";
    print_array(numbers, kSize);

    return 0;
}
