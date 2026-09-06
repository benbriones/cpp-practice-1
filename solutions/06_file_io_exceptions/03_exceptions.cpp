// Solution to src/06_file_io_exceptions/03_exceptions.cpp
// Lesson: throw, try, catch, std::exception
// Run from the repository root so the relative paths resolve.

#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

int checked_divide(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("division by zero");
    }
    return a / b;
}

// Task 1. Reading data[9] directly would be undefined behaviour and might
// quietly hand back garbage. The throw turns a silent disaster into a loud,
// catchable, debuggable event.
int element_at(const int values[], int count, int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("index " + std::to_string(index) + " is outside 0.." +
                                std::to_string(count - 1));
    }
    return values[index];
}

// Task 2. The caller cannot forget to handle these failures: an uncaught
// exception terminates the program.
int sum_file(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("cannot open " + path);
    }

    int sum = 0;
    int value = 0;
    int count = 0;
    while (in >> value) {
        sum += value;
        ++count;
    }

    if (count == 0) {
        throw std::runtime_error("no numbers in " + path);
    }
    return sum;
}

// Task 3. Because the constructor throws, a Temperature below absolute zero
// never comes into existence at all -- there is no half-valid object to
// accidentally use later.
class Temperature {
public:
    explicit Temperature(double celsius) : celsius_(celsius) {
        if (celsius < -273.15) {
            throw std::out_of_range(std::to_string(static_cast<int>(celsius)) +
                                    " is below absolute zero");
        }
    }

    double celsius() const { return celsius_; }
    double fahrenheit() const { return celsius_ * 9.0 / 5.0 + 32.0; }

private:
    double celsius_;
};

int main() {
    try {
        std::cout << "10 / 2 = " << checked_divide(10, 2) << '\n';
        std::cout << "10 / 0 = " << checked_divide(10, 0) << '\n';
        std::cout << "you will never see this line\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "caught invalid_argument: " << e.what() << '\n';
    }
    std::cout << "the program carries on normally\n\n";

    // One outer try with a single catch (const std::exception&) at the end
    // handles out_of_range AND runtime_error, because both derive from it.
    try {
        // Task 1
        constexpr int kSize = 5;
        int data[kSize] = {10, 20, 30, 40, 50};

        std::cout << "element_at(data, 5, 2) = " << element_at(data, kSize, 2) << '\n';

        try {
            std::cout << element_at(data, kSize, 9) << '\n';
        } catch (const std::out_of_range& e) {
            std::cout << "caught out_of_range: " << e.what() << '\n';
        }

        // Task 2
        std::cout << "sum_file(data/numbers.txt) = " << sum_file("data/numbers.txt") << '\n';

        try {
            std::cout << sum_file("data/does_not_exist.txt") << '\n';
        } catch (const std::runtime_error& e) {
            std::cout << "caught: " << e.what() << '\n';
        }

        // Make the empty file, then prove the second failure mode works too.
        std::ofstream make_empty("data/empty_out.txt");
        make_empty.close();

        try {
            std::cout << sum_file("data/empty_out.txt") << '\n';
        } catch (const std::runtime_error& e) {
            std::cout << "caught: " << e.what() << '\n';
        }

        // Task 3
        Temperature warm(20.0);
        std::cout << warm.celsius() << "C = " << warm.fahrenheit() << "F\n";

        Temperature impossible(-500.0);  // throws -- the next line never runs
        std::cout << "never printed: " << impossible.celsius() << '\n';

    } catch (const std::exception& e) {
        // Catch by const reference. Catching by value copies, and can slice a
        // derived exception down to its base.
        std::cout << "caught: " << e.what() << '\n';
    }

    return 0;
}
