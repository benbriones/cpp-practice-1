// =============================================================================
//  07_pointers_advanced / 02_references.cpp
//  Lesson: references -- the other way to hand a function your variable
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/07_pointers_advanced/02_references.cpp -o refs
//    ./refs
//
// -----------------------------------------------------------------------------
//  LESSON 1: a reference is a second NAME for one object
// -----------------------------------------------------------------------------
//        int score = 10;
//        int& alias = score;     // alias is not a new box -- it IS score
//        alias = 42;
//        std::cout << score;     // 42
//
//              score / alias
//              +--------+
//              |   42   |       one box, two names
//              +--------+
//
//  Compare with a pointer, which really is a second box holding an address:
//
//              score            p
//              +--------+       +---------------+
//              |   42   | <---- | address of x  |
//              +--------+       +---------------+
//
// -----------------------------------------------------------------------------
//  LESSON 2: what a reference cannot do
// -----------------------------------------------------------------------------
//        int& r;             // error: must be initialised, always
//        int& r = nullptr;   // error: there is no null reference
//        r = other;          // NOT re-pointing -- this assigns to the original!
//
//  That last one is the important one. A reference can never be re-seated. Once
//  `r` names `score`, every use of `r` for the rest of its life means `score`.
//
//  So the trade is:
//
//        int*                            int&
//        - may be null                   - always refers to something
//        - may be re-pointed             - bound once, for good
//        - arithmetic (p + 1)            - no arithmetic
//        - caller writes &x  (visible)   - caller writes x   (invisible)
//        - must be checked before use    - safe to use immediately
//
// -----------------------------------------------------------------------------
//  LESSON 3: which one to use
// -----------------------------------------------------------------------------
//  The working rule for everyday code:
//
//    - the function must modify the caller's object -> take T&
//    - the function only reads a large object       -> take const T&
//    - the function only reads a small one (int, char, bool, double) -> take T
//    - the argument is genuinely OPTIONAL           -> take T*, nullptr = absent
//    - the function takes over ownership of heap memory -> smart pointer (file 06)
//
//  `const std::string& text` is the workhorse of C++ APIs: no copy is made, and
//  the const means the caller can pass anything, including a literal, knowing it
//  will not be modified.
//
//  The cost of references is honesty at the call site. `grow(score)` gives no
//  hint that score may change, while `grow(&score)` does. That is why some
//  codebases (Google's, notably) still prefer pointers for out parameters. Both
//  conventions are defensible; be consistent within one project.
//
// -----------------------------------------------------------------------------
//  LESSON 4: the dangling reference
// -----------------------------------------------------------------------------
//        int& broken() {
//            int local = 5;
//            return local;     // local dies at the brace; the reference is junk
//        }
//
//  Exactly the same bug as returning a pointer to a local, wearing a nicer suit.
//  Returning a reference is fine ONLY when the object outlives the call --
//  typically because it belongs to the caller in the first place.
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written)
// -----------------------------------------------------------------------------

#include <iostream>
#include <string>

int main() {
    int score = 10;
    int& alias = score;
    alias = 42;
    std::cout << "score = " << score << " (written through alias)\n";
    std::cout << "&score = " << static_cast<const void*>(&score)
              << ", &alias = " << static_cast<const void*>(&alias)
              << "  <- the same object\n\n";

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: swap again
    // -------------------------------------------------------------------------
    //  In 04_pointers you wrote  void swap_ints(int* a, int* b).
    //  Write the reference version:
    //
    //      void swap_refs(int& a, int& b)
    //
    //  Then compare the two, line by line. Which parts of the pointer version
    //  disappeared entirely -- and specifically, which check is now impossible
    //  to forget because it is impossible to need?

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: returning a reference
    // -------------------------------------------------------------------------
    //  Write:
    //
    //      int& largest(int values[], int count)
    //
    //  It returns a reference to the largest element -- not a copy of it. That
    //  makes the call itself assignable:
    //
    //      int data[5] = {19, 4, 27, 8, 12};
    //      std::cout << largest(data, 5);   // 27
    //      largest(data, 5) = 0;            // zeroes the 27 in the array
    //
    //  Print the array afterwards to prove it changed. Then explain to yourself
    //  why this is safe while `return local;` from Lesson 4 is not.

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: const& to read, & to write
    // -------------------------------------------------------------------------
    //  Write two functions over the same std::string:
    //
    //      int  count_char(const std::string& text, char target)
    //      void shout(std::string& text)
    //
    //  count_char only reads, so it takes const& -- no copy, no modification.
    //  shout uppercases every letter in place and appends '!', so it takes a
    //  plain &. Inside shout, loop with  for (char& c : text)  -- note the & --
    //  or you will be modifying copies of the characters.
    //
    //  Try:  std::string message = "reference semantics";
    //        'e' appears 5 times
    //        REFERENCE SEMANTICS!
    //
    //  Then try passing a string literal to each. One compiles, one does not.
    //  The error message is worth reading in full.

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 4: when a pointer is still the right answer
    // -------------------------------------------------------------------------
    //  Write:
    //
    //      void describe(const std::string& text, int* out_length, int* out_vowels)
    //
    //  Each out parameter is optional: if it is nullptr, skip that computation
    //  entirely. Call it twice --
    //
    //      describe(title, &length, &vowels);    // both
    //      describe(title, nullptr, &vowels);    // "just the vowels, thanks"
    //
    //  -- with  const std::string title = "pointers and references";
    //
    //  This is the case references cannot cover: there is no such thing as a
    //  missing reference, so "the caller does not want this one" has to be a
    //  pointer (or, in modern C++, std::optional).

    // TODO

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT   (addresses will differ, but the two will match each other)
// -----------------------------------------------------------------------------
//    score = 42 (written through alias)
//    &score = 0x16f9ee660, &alias = 0x16f9ee660  <- the same object
//
//    after swap_refs(x, y): x = 2, y = 1
//    largest = 27
//    after largest(data, 5) = 0: 19 4 0 8 12
//    'e' appears 5 times
//    after shout : REFERENCE SEMANTICS!
//    length = 23, vowels = 8
//    vowels only = 8
