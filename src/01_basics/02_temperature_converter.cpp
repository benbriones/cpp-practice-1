// =============================================================================
//  01_basics / 02_temperature_converter.cpp
//  Lesson: reading input with std::cin, arithmetic, integer vs. double division
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/01_basics/02_temperature_converter.cpp -o temp_convert
//    ./temp_convert
//
// -----------------------------------------------------------------------------
//  LESSON
// -----------------------------------------------------------------------------
//  std::cin is the input stream. It reads what the user types and stores it in
//  a variable. The arrow points the other way from cout -- values flow INTO
//  your variable:
//
//    int n = 0;
//    std::cin >> n;      // waits for the user to type a number and press Enter
//
//  Always print a prompt first, otherwise the program just sits there silently.
//
//  THE BIG BEGINNER TRAP: integer division.
//
//    int a = 5, b = 2;
//    std::cout << a / b;             // prints 2, NOT 2.5 -- the .5 is thrown away
//    std::cout << 5.0 / 2;           // prints 2.5 -- one side is a double, so
//                                    // the whole calculation is done in doubles
//
//  When a formula has fractions in it (like 9/5 below), write the numbers as
//  doubles: 9.0 / 5.0. If you write 9 / 5 you get 1 and your answers are wrong.
//
//  Formulas you need:
//    fahrenheit = celsius * 9.0 / 5.0 + 32.0
//    celsius    = (fahrenheit - 32.0) * 5.0 / 9.0
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written -- run it, then do your task below)
// -----------------------------------------------------------------------------

#include <iostream>

int main() {
    // A tiny demo of the integer-division trap so you can see it with your eyes.
    std::cout << "9 / 5     = " << 9 / 5 << "   <- integer division, .8 is lost\n";
    std::cout << "9.0 / 5.0 = " << 9.0 / 5.0 << " <- what we actually want\n\n";

    // -------------------------------------------------------------------------
    //  YOUR TASK
    // -------------------------------------------------------------------------
    //  1. Declare a double variable `celsius`.
    //  2. Print the prompt:  Enter a temperature in Celsius:
    //     (end it with a space, not a newline, so the user types on the same line)
    //  3. Read a value into `celsius` using std::cin.
    //  4. Compute the Fahrenheit value into a double called `fahrenheit`.
    //  5. Print:   <celsius>C = <fahrenheit>F
    //  6. Now do the reverse: read a Fahrenheit value and print the Celsius value.
    //
    //  Bonus once that works: print "That is freezing!" only when the Celsius
    //  value is at or below 0. (You will meet `if` properly in the next file --
    //  it looks like:  if (celsius <= 0.0) { ... } )

    // TODO: declare celsius, prompt, and read it with std::cin

    // TODO: compute fahrenheit and print the result

    // TODO: do the same in reverse (Fahrenheit -> Celsius)

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT (user input shown after the prompts)
// -----------------------------------------------------------------------------
//    9 / 5     = 1   <- integer division, .8 is lost
//    9.0 / 5.0 = 1.8 <- what we actually want
//
//    Enter a temperature in Celsius: 100
//    100C = 212F
//    Enter a temperature in Fahrenheit: 32
//    32F = 0C
//
//  If your first conversion prints 100C = 132F, you hit the integer-division
//  trap: you wrote 9 / 5 instead of 9.0 / 5.0.
