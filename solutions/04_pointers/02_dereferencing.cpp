// Solution to src/04_pointers/02_dereferencing.cpp
// Lesson: the * operator -- reading and writing through a pointer

#include <iostream>

int main() {
    int x = 10;
    int* p = &x;

    std::cout << "start:  x = " << x << ",  *p = " << *p << '\n';

    *p = 99;
    std::cout << "*p = 99 -> x = " << x << ",  *p = " << *p << '\n';

    x = 7;
    std::cout << "x = 7   -> x = " << x << ",  *p = " << *p << "\n\n";

    // Task 1: predict, then verify.
    int a = 5;
    int b = 20;
    int* q = &a;

    *q = *q + 1;  // reads through q (5), adds 1, writes back through q -> a is 6
    std::cout << "(1) a = " << a << ", b = " << b << '\n';

    q = &b;  // only q changes; a and b are untouched
    std::cout << "(2) a = " << a << ", b = " << b << '\n';

    *q = 0;  // q now points at b, so THIS writes to b
    std::cout << "(3) a = " << a << ", b = " << b << "\n\n";

    // Task 2: change score without naming it again.
    int score = 21;
    int* score_ptr = &score;
    *score_ptr = *score_ptr * 2;
    std::cout << "score = " << score << "\n\n";

    // Task 3: take the address of each element in turn.
    constexpr int kSize = 4;
    int values[kSize] = {2, 4, 6, 8};

    for (int i = 0; i < kSize; ++i) {
        int* elem = &values[i];  // point at element i
        std::cout << "values[" << i << "] lives at " << elem << " and holds " << *elem << '\n';
        *elem += 10;  // and modify the real array element through it
    }

    std::cout << "after +10 : ";
    for (int i = 0; i < kSize; ++i) {
        std::cout << values[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}
