// =============================================================================
//  04_pointers / 03_nullptr_safety.cpp
//  Lesson: nullptr, why dereferencing it is UNSAFE, and how to guard
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/04_pointers/03_nullptr_safety.cpp -o nullptr_safety
//    ./nullptr_safety
//
// -----------------------------------------------------------------------------
//  LESSON 1: a pointer that points at nothing
// -----------------------------------------------------------------------------
//  Sometimes you need a pointer before you know what it should point at, or you
//  need a way to say "there is no answer". C++ has a special value for that:
//
//        int* p = nullptr;      // p deliberately points at NOTHING
//
//                p
//        +---------------+
//        |    nullptr    | -----> (nowhere at all)
//        +---------------+
//
//  nullptr is FALSE in a condition and any real address is TRUE, so both of
//  these are common and mean the same thing:
//
//        if (p != nullptr) { ... }
//        if (p)            { ... }
//
// -----------------------------------------------------------------------------
//  LESSON 2: NEVER dereference a null pointer
// -----------------------------------------------------------------------------
//  This is the single most important rule in this whole folder:
//
//        int* p = nullptr;
//        std::cout << *p;      // <-- UNSAFE. Undefined behaviour.
//
//  You told the program "go to address 0 and read an int". Nothing lives there.
//  Address 0 is deliberately left unmapped by the operating system so that this
//  mistake is caught, and your program is killed on the spot:
//
//        Segmentation fault
//
//  "Undefined behaviour" means the standard makes NO promise about what
//  happens. On your machine today it crashes. That is the lucky case -- UB can
//  also appear to work, and corrupt something quietly instead. Never rely on it.
//
//  Writing is just as fatal:   *p = 5;   // same crash
//
//  An UNINITIALISED pointer is even worse than a null one:
//
//        int* q;               // holds whatever garbage was in that memory
//        std::cout << *q;      // may crash, may print nonsense, may corrupt
//
//  So: always give a pointer a value. If you have nothing for it yet, give it
//  nullptr -- at least then the failure is loud and immediate.
//
// -----------------------------------------------------------------------------
//  LESSON 3: check before you follow
// -----------------------------------------------------------------------------
//        void print_value(int* p) {
//            if (p == nullptr) {
//                std::cout << "(no value)\n";
//                return;                     // leave early, do NOT dereference
//            }
//            std::cout << *p << '\n';        // safe: we know p is not null here
//        }
//
//  This "guard clause" shape -- check the bad case, return early, then do the
//  real work -- is how careful C++ is written.
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written)
// -----------------------------------------------------------------------------

#include <iostream>

void print_value(int* p) {
    if (p == nullptr) {
        std::cout << "(no value)\n";
        return;
    }
    std::cout << *p << '\n';
}

int main() {
    int x = 42;
    int* good = &x;
    int* empty = nullptr;

    std::cout << "good  -> ";
    print_value(good);
    std::cout << "empty -> ";
    print_value(empty);

    std::cout << "is good null?  " << (good == nullptr) << '\n';
    std::cout << "is empty null? " << (empty == nullptr) << "\n\n";

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: see the crash on purpose (then put it back)
    // -------------------------------------------------------------------------
    //  Uncomment the two lines below, build, and run. Your program should die
    //  with a segmentation fault -- this build has the address sanitizer turned
    //  on, so you will get a loud report naming this exact line.
    //
    //  Read the message. Recognising it will save you hours later.
    //
    //      int* boom = nullptr;
    //      std::cout << *boom << '\n';   // <-- crashes here
    //
    //  Then COMMENT IT BACK OUT so the rest of the file can run, and write in
    //  one sentence below what the error message said:
    //
    //  WHAT I SAW:

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: safe_double
    // -------------------------------------------------------------------------
    //  Write a function above main():
    //
    //      bool safe_double(int* p)
    //
    //  If p is null, do nothing and return false. Otherwise double the value it
    //  points at and return true. Call it with a real pointer and with nullptr
    //  and print both results:
    //
    //      safe_double(&n)     -> true, n is now 20
    //      safe_double(nullptr)-> false

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: "not found" as a null pointer
    // -------------------------------------------------------------------------
    //  This is where null pointers earn their keep. Write:
    //
    //      int* find_first_even(int values[], int count)
    //
    //  It returns the ADDRESS of the first even element (&values[i]), or nullptr
    //  when there is no even element at all.
    //
    //  Call it on both of these:
    //      int a[5] = {7, 3, 8, 5, 4};      // has evens
    //      int b[3] = {1, 3, 5};            // has none
    //
    //  For each: check the returned pointer before using it. When it is not
    //  null, print the value AND set it to 0 through the pointer to prove you
    //  are looking at the real array element, then print the array.
    //
    //      first even in a: 8   -> a is now 7 3 0 5 4
    //      first even in b: none
    //
    //  Notice the parameter is `int values[]` without const this time -- because
    //  the caller is allowed to modify what comes back.

    // TODO

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT
// -----------------------------------------------------------------------------
//    good  -> 42
//    empty -> (no value)
//    is good null?  0
//    is empty null? 1
//
//    safe_double(&n)      -> true, n is now 20
//    safe_double(nullptr) -> false
//    first even in a: 8   -> a is now 7 3 0 5 4
//    first even in b: none
