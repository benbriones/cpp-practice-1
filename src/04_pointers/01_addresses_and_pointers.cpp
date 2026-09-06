// =============================================================================
//  04_pointers / 01_addresses_and_pointers.cpp
//  Lesson: memory addresses, the & operator, declaring a pointer
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/04_pointers/01_addresses_and_pointers.cpp -o ptr_basics
//    ./ptr_basics
//
// -----------------------------------------------------------------------------
//  LESSON 1: every variable lives at an address
// -----------------------------------------------------------------------------
//  Memory is one enormous row of numbered boxes. When you write
//
//        int x = 10;
//
//  the computer sets aside a box big enough for an int, puts 10 in it, and
//  remembers where that box is. The box's number is its ADDRESS.
//
//        address:   0x7ffd1234
//                  +-----------+
//            x     |    10     |
//                  +-----------+
//
//  The & operator reads "address of":
//
//        x    -> 10            the VALUE in the box
//        &x   -> 0x7ffd1234    WHERE the box is
//
//  Addresses print as hexadecimal (base 16, digits 0-9 and a-f, prefixed 0x).
//  The exact number is different every run -- never memorise or rely on it.
//
// -----------------------------------------------------------------------------
//  LESSON 2: a pointer is a variable that stores an address
// -----------------------------------------------------------------------------
//        int x = 10;
//        int* p = &x;      // p is "a pointer to int", holding the address of x
//
//  The * in the DECLARATION is part of the type: `int*` = "pointer to int".
//  It is not doing anything to p; it is describing what p is.
//
//                p                        x
//        +---------------+        +-----------+
//        |  0x7ffd1234   | -----> |    10     |
//        +---------------+        +-----------+
//         at 0x7ffd9999            at 0x7ffd1234
//
//  Four expressions, four different meanings -- learn this table by heart:
//
//        x    -> 10             the value of x
//        &x   -> 0x7ffd1234     the address of x
//        p    -> 0x7ffd1234     the address stored in p  (the same one)
//        *p   -> 10             the value at that address (next file)
//
//  So `p == &x` is true, and p is said to "point at" x.
//
//  A pointer's type must match what it points at. `int* p = &some_double;`
//  will not compile, and that is a feature: the type tells the compiler how
//  many bytes to read and how to interpret them.
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written -- run it and compare the printed addresses)
// -----------------------------------------------------------------------------

#include <iostream>

int main() {
    int x = 10;
    int* p = &x;

    std::cout << "x      = " << x << "        <- the value\n";
    std::cout << "&x     = " << &x << "  <- the address of x\n";
    std::cout << "p      = " << p << "  <- the same address, stored in p\n";
    std::cout << "&p     = " << &p << "  <- p is a variable too, so it has its own address\n";
    std::cout << "p == &x ? " << (p == &x) << "  (1 means true)\n\n";

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: your own pointer
    // -------------------------------------------------------------------------
    //  a) Declare  double price = 19.99;
    //  b) Declare a pointer to it. The type is NOT int* -- work out what it is.
    //  c) Print, each on its own line:
    //         price  = 19.99
    //         &price = 0x...
    //         ptr    = 0x...
    //  d) Print whether ptr == &price (it should print 1).

    // TODO
    double price = 19.99;
    double* pPrice = &price;
    std::cout << "price = " << price << "\n";
    std::cout << "&price = " << &price << "\n";
    std::cout << "ptr = " << pPrice << "\n";

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: two variables, one pointer
    // -------------------------------------------------------------------------
    //  a) Declare  int a = 1;  and  int b = 2;
    //  b) Declare  int* q = &a;  and print q.
    //  c) Now point q at b instead (q = &b;) and print q again.
    //
    //  The two printed addresses will be different. Before you run it, predict:
    //  did the value of `a` change when you re-pointed q? Write your answer here
    //  as a comment, then run it and check.
    //
    //  YOUR PREDICTION: value of q will be different adresses.

    // TODO
    int a = 1, b = 2;
    int* q = &a;
    std::cout << q << "\n";

    q = &b;
    std::cout << q << "\n";

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: how big is a pointer?
    // -------------------------------------------------------------------------
    //  sizeof(thing) gives the size in bytes. Print all of these:
    //
    //      sizeof(int)     sizeof(double)    sizeof(char)
    //      sizeof(int*)    sizeof(double*)   sizeof(char*)
    //
    //  The three pointer sizes will all be the same, even though the things they
    //  point at are different sizes. Why? Because a pointer only ever holds an
    //  address, and every address on your machine is the same width.
    //
    //  Note: sizeof yields an unsigned type, so printing it is fine, but if you
    //  ever compare it with an int the compiler will warn you.

    // TODO

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT (your addresses will differ -- that is normal and expected)
// -----------------------------------------------------------------------------
//    x      = 10        <- the value
//    &x     = 0x16d0a2b58  <- the address of x
//    p      = 0x16d0a2b58  <- the same address, stored in p
//    &p     = 0x16d0a2b60  <- p is a variable too, so it has its own address
//    p == &x ? 1  (1 means true)
//
//    price  = 19.99
//    &price = 0x16d0a2b48
//    ptr    = 0x16d0a2b48
//    ptr == &price ? 1
//
//    q -> a : 0x16d0a2b44
//    q -> b : 0x16d0a2b40
//
//    sizeof(int)     = 4   sizeof(int*)    = 8
//    sizeof(double)  = 8   sizeof(double*) = 8
//    sizeof(char)    = 1   sizeof(char*)   = 8
