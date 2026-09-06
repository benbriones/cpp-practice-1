// Solution to src/02_arrays_strings/02_array_stats.cpp
// Lesson: accumulating over an array, passing arrays to functions, averages

#include <iostream>

int sum_of(const int values[], int count) {
    int sum = 0;
    for (int i = 0; i < count; ++i) {
        sum += values[i];
    }
    return sum;
}

double average_of(const int values[], int count) {
    if (count <= 0) {
        return 0.0;  // the average of nothing: pick something and document it
    }
    // static_cast turns the integer division into a real one.
    return static_cast<double>(sum_of(values, count)) / count;
}

int smallest_of(const int values[], int count) {
    if (count <= 0) {
        return 0;
    }
    int smallest = values[0];
    for (int i = 1; i < count; ++i) {
        if (values[i] < smallest) {
            smallest = values[i];
        }
    }
    return smallest;
}

int count_above(const int values[], int count, int threshold) {
    int n = 0;
    for (int i = 0; i < count; ++i) {
        if (values[i] > threshold) {
            ++n;
        }
    }
    return n;
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

    // Task 4: compute the average ONCE, then reuse it.
    double average = average_of(temps, kSize);

    // The average is 21.25 but count_above takes an int. Truncating to 21 means
    // "strictly greater than 21", which still excludes 21 itself -- correct
    // here. Saying the cast out loud is the point: no silent conversion.
    int above = count_above(temps, kSize, static_cast<int>(average));

    std::cout << "above average (" << average << "): " << above << " of " << kSize << '\n';

    return 0;
}
