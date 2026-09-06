// Solution to src/03_loops/02_nested_loops.cpp
// Lesson: nested loops and lining output up in columns

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

    // Task 1: multiplication table. The newline belongs to the OUTER loop.
    std::cout << "multiplication table:\n";
    for (int row = 1; row <= 9; ++row) {
        for (int col = 1; col <= 9; ++col) {
            std::cout << std::setw(4) << row * col;
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    // Task 2: the inner limit depends on the outer counter.
    std::cout << "triangle:\n";
    for (int row = 1; row <= 5; ++row) {
        for (int star = 1; star <= row; ++star) {
            std::cout << '*';
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    // Task 3: two inner loops per row -- spaces first, then stars.
    // Row r of a 5-tall triangle needs (5 - r) spaces and r stars.
    constexpr int kHeight = 5;
    std::cout << "right-aligned:\n";
    for (int row = 1; row <= kHeight; ++row) {
        for (int space = 0; space < kHeight - row; ++space) {
            std::cout << ' ';
        }
        for (int star = 1; star <= row; ++star) {
            std::cout << '*';
        }
        std::cout << '\n';
    }

    return 0;
}
