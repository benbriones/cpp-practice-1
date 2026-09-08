// =============================================================================
//  07_pointers_advanced / 03_const_correctness.cpp
//  Lesson: const int*, int* const, and signatures that document themselves
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/07_pointers_advanced/03_const_correctness.cpp -o const_ptr
//    ./const_ptr
//
// -----------------------------------------------------------------------------
//  LESSON 1: two things can be const, and they are different things
// -----------------------------------------------------------------------------
//  A pointer involves two objects -- the pointer, and the thing it points at.
//  `const` can lock either, or both:
//
//        const int* p;        // pointer TO const int   -- *p is locked, p moves
//        int* const p;        // const POINTER to int   -- p is locked, *p moves
//        const int* const p;  // both locked
//
//  The trick for reading any declaration: start at the variable name and read
//  RIGHT TO LEFT.
//
//        const int *  p        ->  p is a pointer to an int that is const
//              int * const p   ->  p is a const pointer to an int
//        const int * const p   ->  p is a const pointer to a const int
//
//  (`const int* p` and `int const* p` mean exactly the same thing. The second
//   spelling makes the right-to-left rule work every time; the first is what
//   you will see in most code.)
//
// -----------------------------------------------------------------------------
//  LESSON 2: what each one forbids
// -----------------------------------------------------------------------------
//        int a = 1, b = 2;
//
//        const int* to_const = &a;
//        to_const = &b;        // OK   -- moving the pointer
//        *to_const = 99;       // ERROR -- read-only reference
//
//        int* const const_ptr = &a;
//        *const_ptr = 99;      // OK   -- writing through it
//        const_ptr = &b;       // ERROR -- cannot assign to a const variable
//
//  Note what `const int* p` does NOT mean: it is not a promise that the value
//  never changes. Someone else may hold a non-const pointer to the same int and
//  change it. It is a promise that YOU will not change it through THIS pointer.
//
// -----------------------------------------------------------------------------
//  LESSON 3: why bother
// -----------------------------------------------------------------------------
//  Three payoffs, in increasing order of importance:
//
//    1. The compiler catches accidental writes. Cheap, occasionally life-saving.
//
//    2. The signature becomes documentation that cannot go stale:
//
//           int  count_greater(const int* begin, const int* end, int t);   reads
//           void clamp_all(int* begin, int* end, int lo, int hi);          writes
//
//       You know which is which without opening either body, and the compiler
//       keeps the comment honest.
//
//    3. const objects can only be passed to const-taking functions. So the
//       moment one function is const-correct, its callers must be too. This is
//       why const "spreads" through a codebase -- and why retrofitting it later
//       is painful. Write it const from the start.
//
//  The mirror image of this is `const` member functions from 05_oop: there, the
//  const applies to the object the method is called on.
//
// -----------------------------------------------------------------------------
//  LESSON 4: do not lie
// -----------------------------------------------------------------------------
//  const_cast can strip const away. Writing to an object that was really const
//  after doing so is undefined behaviour, and the payoff is nothing. If you need
//  to modify it, do not take it as const.
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written -- read the commented-out lines carefully)
// -----------------------------------------------------------------------------

#include <iostream>

int main() {
    int a = 1;
    int b = 2;

    const int* to_const = &a;
    to_const = &b;         // OK -- repointing
    // *to_const = 99;     // <- TASK 1: uncomment, read the error, re-comment

    int* const const_ptr = &a;
    *const_ptr = 99;       // OK -- writing through it
    // const_ptr = &b;     // <- TASK 1

    const int* const both = &a;
    // both = &b;          // <- TASK 1
    // *both = 7;          // <- TASK 1

    std::cout << "a = " << a << ", b = " << b << '\n';
    std::cout << "*to_const = " << *to_const << ", *both = " << *both << "\n\n";

    const int frozen = 5;
    const int* ok = &frozen;
    // int* nope = &frozen;   // <- TASK 1
    std::cout << "*ok = " << *ok << "\n\n";

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: break it on purpose
    // -------------------------------------------------------------------------
    //  Uncomment the five marked lines above ONE AT A TIME, compile, and read
    //  the error before re-commenting it. You are training yourself to recognise
    //  these messages -- they are among the most common errors in C++, and they
    //  are much easier to fix when you have seen them deliberately.
    //
    //  Predict the error first, then check. Which one says "read-only variable
    //  is not assignable" and which says "cannot assign to variable with const-
    //  qualified type"?

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: a const-correct reader
    // -------------------------------------------------------------------------
    //  Write above main():
    //
    //      int count_greater(const int* begin, const int* end, int threshold)
    //
    //  It counts the elements strictly greater than threshold. Same half-open
    //  range walk as file 01, but now the pointers are pointers-to-const, so the
    //  compiler will stop you if you slip and write through them.
    //
    //  Test with:  int scores[8] = {58, 91, 74, 12, 100, 67, 45, 88};
    //              above 60 : 5

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: the mutating counterpart
    // -------------------------------------------------------------------------
    //  Write:
    //
    //      void clamp_all(int* begin, int* end, int lo, int hi)
    //
    //  Every element below lo becomes lo; every element above hi becomes hi.
    //  Non-const pointers, because it writes.
    //
    //      clamp_all(scores, scores + 8, 40, 90);
    //      clamped  : 58 90 74 40 90 67 45 88
    //
    //  Then, at the bottom of main, declare
    //
    //      const int frozen_scores[3] = {10, 20, 30};
    //
    //  and call count_greater on it -- fine. Then try calling clamp_all on it,
    //  see the error, and comment it back out. That error is const-correctness
    //  doing its actual job.

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 4: locking both
    // -------------------------------------------------------------------------
    //  Write:
    //
    //      int sum_first_n(const int* const values, int n)
    //
    //  Sum the first n elements. Inside the body, neither `values = ...` nor
    //  `values[0] = ...` will compile -- which is the point: the signature says
    //  "pure input, I touch nothing".
    //
    //      sum of first 4 : 262   (after the clamp above)
    //
    //  Worth noticing: the top-level const here is for the FUNCTION's benefit,
    //  not the caller's. The caller passes a copy of the pointer either way, so
    //  `const int*` and `const int* const` look identical from the outside.

    // TODO

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT
// -----------------------------------------------------------------------------
//    a = 99, b = 2
//    *to_const = 2, *both = 99
//
//    *ok = 5
//
//    above 60 : 5
//    clamped  : 58 90 74 40 90 67 45 88
//    sum of first 4 : 262
//    frozen above 15: 2
