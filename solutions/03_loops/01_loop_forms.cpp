// Solution to src/03_loops/01_loop_forms.cpp
// Lesson: for, while, do-while

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
        std::cout << k << ' ';
        ++k;
    } while (k < 3);
    std::cout << '\n';

    // Task 1: the same job written both ways.
    std::cout << "fives : ";
    for (int i = 5; i <= 50; i += 5) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    std::cout << "fives : ";
    int five = 5;
    while (five <= 50) {
        std::cout << five << ' ';
        five += 5;
    }
    std::cout << '\n';

    // Task 2: fizzbuzz.
    // The 15 test MUST come first. If you test 3 first, every multiple of 15
    // matches "fizz" and the "fizzbuzz" branch can never be reached.
    int interesting = 0;
    for (int i = 1; i <= 100; ++i) {
        if (i % 15 == 0) {
            std::cout << i << ": fizzbuzz\n";
            ++interesting;
        } else if (i % 3 == 0) {
            std::cout << i << ": fizz\n";
            ++interesting;
        } else if (i % 5 == 0) {
            std::cout << i << ": buzz\n";
            ++interesting;
        }
        // no else: uninteresting numbers print nothing
    }
    std::cout << "interesting numbers: " << interesting << '\n';

    // Task 3: keep adding until the total passes 100.
    int total = 0;
    int next = 1;
    while (total <= 100) {
        total += next;
        ++next;
    }
    // next was already stepped past the last number added, so subtract one.
    std::cout << "sum " << total << " after adding " << next - 1 << " numbers\n";

    return 0;
}
