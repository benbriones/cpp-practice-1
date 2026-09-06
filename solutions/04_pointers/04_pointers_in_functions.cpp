// Solution to src/04_pointers/04_pointers_in_functions.cpp
// Lesson: passing pointers to functions

#include <iostream>

void try_to_double(int n) {
    n = n * 2;  // the copy changes; the caller's variable does not
}

void really_double(int* n) {
    if (n == nullptr) {
        return;
    }
    *n = *n * 2;
}

// Task 1. The temporary is an int, not an int*: we are exchanging the VALUES,
// not the addresses.
//
// The wrong version -- int* tmp = a; a = b; b = tmp; -- swaps the two local
// pointer variables inside the function. They are copies of the caller's
// addresses, they vanish at the closing brace, and the caller's ints are never
// touched. Correct-looking, completely useless.
void swap_ints(int* a, int* b) {
    if (a == nullptr || b == nullptr) {
        return;
    }
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Task 2: two answers out of one pass, delivered through out parameters.
// `values` is const (read only); the out parameters are not. The signature
// documents exactly what this function will and will not touch.
void min_and_max(const int values[], int count, int* out_min, int* out_max) {
    if (count <= 0 || out_min == nullptr || out_max == nullptr) {
        return;
    }
    int smallest = values[0];
    int largest = values[0];
    for (int i = 1; i < count; ++i) {
        if (values[i] < smallest) {
            smallest = values[i];
        }
        if (values[i] > largest) {
            largest = values[i];
        }
    }
    *out_min = smallest;
    *out_max = largest;
}

// Task 3: "return whether it worked, deliver the answer through a pointer".
bool safe_divide(int a, int b, int* out_result) {
    if (b == 0 || out_result == nullptr) {
        return false;
    }
    *out_result = a / b;
    return true;
}

int main() {
    int score = 10;

    try_to_double(score);
    std::cout << "after try_to_double(score)  : " << score << "  <- unchanged\n";

    really_double(&score);
    std::cout << "after really_double(&score) : " << score << "  <- changed\n\n";

    // Task 1
    int x = 1;
    int y = 2;
    std::cout << "before swap: x = " << x << ", y = " << y << '\n';
    swap_ints(&x, &y);
    std::cout << "after swap : x = " << x << ", y = " << y << '\n';

    // Task 2
    constexpr int kSize = 6;
    int data[kSize] = {19, 4, 27, 8, 33, 12};
    int lo = 0;
    int hi = 0;
    min_and_max(data, kSize, &lo, &hi);
    std::cout << "min = " << lo << ", max = " << hi << '\n';

    // Task 3
    int result = 0;
    if (safe_divide(10, 2, &result)) {
        std::cout << "10 / 2 = " << result << '\n';
    }
    if (safe_divide(10, 0, &result)) {
        std::cout << "10 / 0 = " << result << '\n';
    } else {
        std::cout << "10 / 0 -> failed\n";
    }

    return 0;
}
