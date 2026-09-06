// Solution to src/01_basics/02_temperature_converter.cpp
// Lesson: std::cin, arithmetic, integer vs. double division

#include <iostream>

int main() {
    std::cout << "9 / 5     = " << 9 / 5 << "   <- integer division, .8 is lost\n";
    std::cout << "9.0 / 5.0 = " << 9.0 / 5.0 << " <- what we actually want\n\n";

    // Celsius -> Fahrenheit
    double celsius = 0.0;
    std::cout << "Enter a temperature in Celsius: ";
    std::cin >> celsius;

    // 9.0 / 5.0, not 9 / 5 -- otherwise the fraction is thrown away.
    double fahrenheit = celsius * 9.0 / 5.0 + 32.0;
    std::cout << celsius << "C = " << fahrenheit << "F\n";

    if (celsius <= 0.0) {
        std::cout << "That is freezing!\n";
    }

    // Fahrenheit -> Celsius
    double f_in = 0.0;
    std::cout << "Enter a temperature in Fahrenheit: ";
    std::cin >> f_in;

    double c_out = (f_in - 32.0) * 5.0 / 9.0;
    std::cout << f_in << "F = " << c_out << "C\n";

    return 0;
}
