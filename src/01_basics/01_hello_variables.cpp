// =============================================================================
//  01_basics / 01_hello_variables.cpp
//  Lesson: program structure, #include, main(), variables, std::cout
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/01_basics/01_hello_variables.cpp -o hello_variables
//    ./hello_variables
//
//  (Or use the helper script in this repo: ./run src/01_basics/01_hello_variables.cpp)
//
// -----------------------------------------------------------------------------
//  LESSON
// -----------------------------------------------------------------------------
//  Every C++ program is built from the same few pieces:
//
//    #include <iostream>   <- pull in code someone else wrote (here: printing)
//    int main() { ... }    <- the ONE function the program starts running in
//    return 0;             <- "finished, no errors" (optional in main)
//
//  A variable is a named box that holds a value of one specific type.
//  You must say the type when you create it. The common primitive types:
//
//    int     whole numbers                 int age = 21;
//    double  numbers with a decimal point  double price = 4.99;
//    char    a single character            char grade = 'A';
//    bool    true or false                 bool is_ready = true;
//
//  std::cout is the "character output" stream. You push values into it with <<.
//  '\n' means "new line". You can chain as many << as you like:
//
//    std::cout << "age: " << age << '\n';
//
//  Note the std:: prefix: cout lives in the standard library's namespace.
//
// -----------------------------------------------------------------------------
//  EXAMPLE (this part already works -- read it, then run the program)
// -----------------------------------------------------------------------------

#include <iostream>

int main() {
    int year = 2026;
    double pi = 3.14159;
    char initial = 'B';
    bool learning_cpp = true;

    std::cout << "--- example ---\n";
    std::cout << "year: " << year << '\n';
    std::cout << "pi: " << pi << '\n';
    std::cout << "initial: " << initial << '\n';
    // A bool prints as 1 (true) or 0 (false) by default.
    std::cout << "learning_cpp: " << learning_cpp << '\n';

    std::cout << "--- your turn ---\n";

    // -------------------------------------------------------------------------
    //  YOUR TASK
    // -------------------------------------------------------------------------
    //  1. Declare a variable `name` of type std::string holding your name.
    //     (std::string needs one more #include at the top of the file -- add it.)
    //  2. Declare an int `age` holding your age.
    //  3. Declare a double `height_m` holding your height in metres.
    //  4. Print all three, one per line, in this exact format:
    //
    //         name: Ben
    //         age: 21
    //         height_m: 1.78
    //
    //  5. Then compute and print how old you will be in 10 years, like:
    //
    //         in 10 years: 31
    //
    //     Do the arithmetic in the program (age + 10), do not type 31 yourself.

    // TODO: declare your variables here
    std::string name = "ben";
    int age = 27;
    double height_m = 1.27;
    int tenYearsAge = age + 10;

    // TODO: print them here
    std::cout << "name: " << name << '\n';
    std::cout << "age: " << age << '\n';
    std::cout << "height_m: " << height_m << '\n';
    std::cout << "in 10 years: " << tenYearsAge << '\n';

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT (with your own values substituted)
// -----------------------------------------------------------------------------
//    --- example ---
//    year: 2026
//    pi: 3.14159
//    initial: B
//    learning_cpp: 1
//    --- your turn ---
//    name: Ben
//    age: 21
//    height_m: 1.78
//    in 10 years: 31
