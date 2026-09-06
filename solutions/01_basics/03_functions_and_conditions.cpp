// Solution to src/01_basics/03_functions_and_conditions.cpp
// Lesson: functions, parameters, return values, if / else if / else

#include <iostream>
#include <string>

int larger_of(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

// Returns the description rather than printing it: the caller decides what to
// do with the answer, which makes the function reusable.
std::string describe_number(int n) {
    if (n > 0) {
        return "positive";
    } else if (n < 0) {
        return "negative";
    } else {
        return "zero";
    }
}

double calculate(double a, double b, char op) {
    if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else if (op == '*') {
        return a * b;
    } else if (op == '/') {
        if (b == 0.0) {
            std::cout << "cannot divide by zero\n";
            return 0.0;
        }
        return a / b;
    } else {
        std::cout << "unknown operator: " << op << '\n';
        return 0.0;
    }
}

int main() {
    std::cout << "larger_of(3, 9) = " << larger_of(3, 9) << '\n';

    std::cout << "describe_number(7)  -> " << describe_number(7) << '\n';
    std::cout << "describe_number(-4) -> " << describe_number(-4) << '\n';
    std::cout << "describe_number(0)  -> " << describe_number(0) << '\n';

    std::cout << "calculate(6, 3, '+') = " << calculate(6, 3, '+') << '\n';
    std::cout << "calculate(6, 3, '-') = " << calculate(6, 3, '-') << '\n';
    std::cout << "calculate(6, 3, '*') = " << calculate(6, 3, '*') << '\n';
    std::cout << "calculate(6, 3, '/') = " << calculate(6, 3, '/') << '\n';
    std::cout << "calculate(6, 0, '/') = " << calculate(6, 0, '/') << '\n';

    // Task 3: drive the calculator from user input.
    double a = 0.0;
    double b = 0.0;
    char op = '+';
    std::cout << "Enter: a op b (e.g. 4 * 5): ";
    if (std::cin >> a >> op >> b) {
        std::cout << "= " << calculate(a, b, op) << '\n';
    } else {
        std::cout << "could not read that\n";
    }

    return 0;
}
