// Solution to src/01_basics/01_hello_variables.cpp
// Lesson: program structure, variables, std::cout

#include <iostream>
#include <string>  // needed for std::string

int main() {
    int year = 2026;
    double pi = 3.14159;
    char initial = 'B';
    bool learning_cpp = true;

    std::cout << "--- example ---\n";
    std::cout << "year: " << year << '\n';
    std::cout << "pi: " << pi << '\n';
    std::cout << "initial: " << initial << '\n';
    std::cout << "learning_cpp: " << learning_cpp << '\n';

    std::cout << "--- your turn ---\n";

    // Task: declare and print name, age and height.
    std::string name = "Ben";
    int age = 21;
    double height_m = 1.78;

    std::cout << "name: " << name << '\n';
    std::cout << "age: " << age << '\n';
    std::cout << "height_m: " << height_m << '\n';

    // The arithmetic happens in the program, not in your head.
    std::cout << "in 10 years: " << age + 10 << '\n';

    return 0;
}
