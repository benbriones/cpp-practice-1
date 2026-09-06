// Solution to src/06_file_io_exceptions/02_reading_files.cpp
// Lesson: std::ifstream -- reading value by value and line by line
// Run from the repository root so the relative paths resolve.

#include <fstream>
#include <iostream>
#include <string>

int main() {
    const std::string path = "data/names.txt";

    std::ifstream in(path);
    if (!in) {
        std::cerr << "could not open " << path << '\n';
        std::cerr << "(are you running this from the repository root?)\n";
        return 1;
    }

    std::cout << "--- " << path << " line by line ---\n";
    std::string line;
    int line_number = 0;
    while (std::getline(in, line)) {
        ++line_number;
        std::cout << line_number << ": " << line << '\n';
    }
    std::cout << "read " << line_number << " lines\n\n";

    // Task 1: count, sum, average and largest all from ONE pass.
    const std::string numbers_path = "data/numbers.txt";
    std::ifstream numbers(numbers_path);
    if (!numbers) {
        std::cerr << "could not open " << numbers_path << '\n';
        return 1;
    }

    int count = 0;
    int sum = 0;
    int largest = 0;
    int value = 0;
    while (numbers >> value) {  // ends at end of file, or on the first bad token
        if (count == 0 || value > largest) {
            largest = value;
        }
        sum += value;
        ++count;
    }

    if (count == 0) {
        std::cout << numbers_path << " contained no numbers\n";
    } else {
        std::cout << "count   : " << count << '\n';
        std::cout << "sum     : " << sum << '\n';
        std::cout << "average : " << static_cast<double>(sum) / count << '\n';
        std::cout << "largest : " << largest << '\n';
    }

    // Task 2: an expected failure -- report it and carry on.
    const std::string missing_path = "data/does_not_exist.txt";
    std::ifstream missing(missing_path);
    if (!missing) {
        std::cout << missing_path << ": no such file (that is the expected result here)\n";
    }

    // Task 3: mixed data, stopped early by one bad line.
    const std::string scores_path = "data/scores.txt";
    std::ifstream scores(scores_path);
    if (!scores) {
        std::cerr << "could not open " << scores_path << '\n';
        return 1;
    }

    std::string name;
    int score = 0;
    int entries = 0;
    int score_total = 0;
    // The >> that expects an int fails on "not-a-number", the stream goes into
    // a failed state, and the loop ends. That is the stream protecting you from
    // silently using garbage.
    while (scores >> name >> score) {
        std::cout << name << ' ' << score << '\n';
        score_total += score;
        ++entries;
    }
    std::cout << "read " << entries << " valid entries, then hit bad data\n";
    if (entries > 0) {
        std::cout << "average score: " << static_cast<double>(score_total) / entries << '\n';
    }

    return 0;
}
