// Solution to src/04_pointers/01_addresses_and_pointers.cpp
// Lesson: memory addresses, the & operator, declaring a pointer

#include <iostream>

int main() {
    int x = 10;
    int* p = &x;

    std::cout << "x      = " << x << "        <- the value\n";
    std::cout << "&x     = " << &x << "  <- the address of x\n";
    std::cout << "p      = " << p << "  <- the same address, stored in p\n";
    std::cout << "&p     = " << &p << "  <- p is a variable too, so it has its own address\n";
    std::cout << "p == &x ? " << (p == &x) << "  (1 means true)\n\n";

    // Task 1: the pointer type must match what it points at.
    double price = 19.99;
    double* ptr = &price;  // NOT int* -- the types have to agree

    std::cout << "price  = " << price << '\n';
    std::cout << "&price = " << &price << '\n';
    std::cout << "ptr    = " << ptr << '\n';
    std::cout << "ptr == &price ? " << (ptr == &price) << "\n\n";

    // Task 2
    int a = 1;
    int b = 2;
    int* q = &a;
    std::cout << "q -> a : " << q << '\n';

    q = &b;  // point q somewhere else
    std::cout << "q -> b : " << q << "\n\n";

    // ANSWER TO THE PREDICTION: no, `a` did not change. Re-pointing q only
    // overwrites the address stored inside q. Nothing was written THROUGH q, so
    // neither a nor b was touched. Changing where you are looking is not the
    // same as changing what you are looking at.
    std::cout << "a is still " << a << ", b is still " << b << "\n\n";

    // Task 3: every pointer is the same size, because every address is.
    std::cout << "sizeof(int)     = " << sizeof(int) << "   sizeof(int*)    = " << sizeof(int*)
              << '\n';
    std::cout << "sizeof(double)  = " << sizeof(double)
              << "   sizeof(double*) = " << sizeof(double*) << '\n';
    std::cout << "sizeof(char)    = " << sizeof(char) << "   sizeof(char*)   = " << sizeof(char*)
              << '\n';

    return 0;
}
