// Solution to src/04_pointers/03_nullptr_safety.cpp
// Lesson: nullptr, why dereferencing it is unsafe, and how to guard

#include <iostream>

void print_value(int* p) {
    if (p == nullptr) {
        std::cout << "(no value)\n";
        return;
    }
    std::cout << *p << '\n';
}

// Task 2: guard first, work second. The bool tells the caller what happened.
bool safe_double(int* p) {
    if (p == nullptr) {
        return false;
    }
    *p = *p * 2;
    return true;
}

// Task 3: a null pointer is a perfectly good way to say "there is no answer".
// Not const, because the caller is allowed to modify what comes back.
int* find_first_even(int values[], int count) {
    for (int i = 0; i < count; ++i) {
        if (values[i] % 2 == 0) {
            return &values[i];  // the address of the real element
        }
    }
    return nullptr;  // nothing even in there
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

    // Task 1: WHAT I SAW -- with the address sanitizer on, dereferencing a null
    // pointer reports:
    //     runtime error: load of null pointer of type 'int'
    //     AddressSanitizer: SEGV on unknown address 0x000000000000
    //     The signal is caused by a READ memory access.
    //     Hint: address points to the zero page.
    // ...with the file and line number of the offending dereference.
    // Without sanitizers it is just "Segmentation fault: 11". Either way the
    // program dies immediately -- which is the good outcome, because the
    // alternative kind of undefined behaviour is the silent kind.
    //
    //     int* boom = nullptr;
    //     std::cout << *boom << '\n';   // deliberately left commented out

    // Task 2
    int n = 10;
    std::cout << "safe_double(&n)      -> " << (safe_double(&n) ? "true" : "false") << ", n is now "
              << n << '\n';
    std::cout << "safe_double(nullptr) -> " << (safe_double(nullptr) ? "true" : "false") << '\n';

    // Task 3
    constexpr int kASize = 5;
    int a[kASize] = {7, 3, 8, 5, 4};
    constexpr int kBSize = 3;
    int b[kBSize] = {1, 3, 5};

    int* found = find_first_even(a, kASize);
    if (found != nullptr) {  // CHECK before you follow
        std::cout << "first even in a: " << *found << "   -> a is now ";
        *found = 0;  // writing through the pointer changes the array itself
        for (int i = 0; i < kASize; ++i) {
            std::cout << a[i] << (i < kASize - 1 ? " " : "");
        }
        std::cout << '\n';
    }

    int* none = find_first_even(b, kBSize);
    if (none != nullptr) {
        std::cout << "first even in b: " << *none << '\n';
    } else {
        std::cout << "first even in b: none\n";
    }

    return 0;
}
