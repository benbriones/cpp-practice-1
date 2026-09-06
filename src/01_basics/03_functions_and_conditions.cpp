// =============================================================================
//  01_basics / 03_functions_and_conditions.cpp
//  Lesson: functions, parameters, return values, if / else if / else
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/01_basics/03_functions_and_conditions.cpp -o functions
//    ./functions
//
// -----------------------------------------------------------------------------
//  LESSON
// -----------------------------------------------------------------------------
//  A function is a named piece of code you can run over and over. It has:
//
//        int add(int a, int b) { return a + b; }
//        ^^^     ^^^^^^^^^^^^          ^^^^^^
//     return type   parameters      the value handed back
//
//  Calling it:  int total = add(2, 3);   // total is now 5
//
//  A function whose return type is `void` hands nothing back; it just does
//  something (usually printing).
//
//  IMPORTANT: a function must be declared ABOVE the place where you call it.
//  That is why all the functions in this file live above main().
//
//  Choosing between options uses if / else if / else. The condition must be a
//  bool. The comparison operators are:
//
//        ==  equal            !=  not equal
//        <   less than        <=  less than or equal
//        >   greater than     >=  greater than or equal
//
//  Watch out: `=` assigns, `==` compares. `if (x = 0)` is a classic bug.
//
//        if (score >= 90) {
//            grade = 'A';
//        } else if (score >= 80) {   // only checked when the first was false
//            grade = 'B';
//        } else {                    // when every condition above was false
//            grade = 'F';
//        }
//
//  The branches are checked top to bottom and exactly one of them runs.
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written -- read how it is defined, then called in main)
// -----------------------------------------------------------------------------

#include <iostream>
#include <string>

// Takes two ints, hands back the larger one.
int larger_of(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

// -----------------------------------------------------------------------------
//  YOUR TASK 1: describe_number
// -----------------------------------------------------------------------------
//  Return the string "positive" when n is greater than 0,
//                    "negative" when n is less than 0,
//                    "zero"     otherwise.
//  Use if / else if / else. Do not print anything inside this function --
//  it should RETURN the text so the caller can decide what to do with it.
std::string describe_number(int n) {
    // TODO: replace this placeholder with your three branches
    return "TODO";
}

// -----------------------------------------------------------------------------
//  YOUR TASK 2: calculate
// -----------------------------------------------------------------------------
//  A tiny calculator. `op` is one of the characters '+', '-', '*', '/'.
//  Return the result of applying that operation to a and b.
//
//  Two things to think about:
//    - Compare characters with single quotes: if (op == '+') ...
//    - Dividing by zero is undefined behaviour. When b is 0 and op is '/',
//      print an error message and return 0.0 instead of dividing.
double calculate(double a, double b, char op) {
    // TODO: handle '+', '-', '*', '/', and an unknown operator
    return 0.0;
}

int main() {
    std::cout << "larger_of(3, 9) = " << larger_of(3, 9) << '\n';

    // These calls already work once you fill in the functions above.
    std::cout << "describe_number(7)  -> " << describe_number(7) << '\n';
    std::cout << "describe_number(-4) -> " << describe_number(-4) << '\n';
    std::cout << "describe_number(0)  -> " << describe_number(0) << '\n';

    std::cout << "calculate(6, 3, '+') = " << calculate(6, 3, '+') << '\n';
    std::cout << "calculate(6, 3, '-') = " << calculate(6, 3, '-') << '\n';
    std::cout << "calculate(6, 3, '*') = " << calculate(6, 3, '*') << '\n';
    std::cout << "calculate(6, 3, '/') = " << calculate(6, 3, '/') << '\n';
    std::cout << "calculate(6, 0, '/') = " << calculate(6, 0, '/') << '\n';

    // -------------------------------------------------------------------------
    //  YOUR TASK 3
    // -------------------------------------------------------------------------
    //  Ask the user for two numbers and an operator character, then print the
    //  result using your calculate() function. Something like:
    //
    //      Enter: a op b (e.g. 4 * 5): 4 * 5
    //      = 20
    //
    //  Hint: you can read all three in one go --  std::cin >> a >> op >> b;

    // TODO: read a, op, b from std::cin and print calculate(a, b, op)

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT
// -----------------------------------------------------------------------------
//    larger_of(3, 9) = 9
//    describe_number(7)  -> positive
//    describe_number(-4) -> negative
//    describe_number(0)  -> zero
//    calculate(6, 3, '+') = 9
//    calculate(6, 3, '-') = 3
//    calculate(6, 3, '*') = 18
//    calculate(6, 3, '/') = 2
//    calculate(6, 0, '/') = cannot divide by zero
//    0
//
//  That last bit looks broken but is correct: in one chained statement,
//  std::cout prints "calculate(6, 0, '/') = " FIRST, and only then is
//  calculate() called -- which prints its own error message in the middle of
//  the line. A nice little lesson in evaluation order, for free.
