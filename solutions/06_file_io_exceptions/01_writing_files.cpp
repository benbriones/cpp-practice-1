// Solution to src/06_file_io_exceptions/01_writing_files.cpp
// Lesson: std::ofstream and always checking that a file opened
// Run from the repository root so the relative paths resolve.

#include <fstream>
#include <ios>
#include <iostream>
#include <string>

// Task 3: report the failure to the CALLER instead of printing from in here.
// A helper that decides how to complain is a helper you cannot reuse.
bool save_numbers(const std::string& path, const int values[], int count) {
    std::ofstream out(path);
    if (!out) {
        return false;
    }
    for (int i = 0; i < count; ++i) {
        out << values[i] << '\n';
    }
    return true;
}

int main() {
    const std::string path = "data/greeting_out.txt";

    std::ofstream out(path);
    if (!out) {
        std::cerr << "could not open " << path << " for writing\n";
        std::cerr << "(are you running this from the repository root?)\n";
        return 1;
    }

    out << "Hello from C++!\n";
    out << "The answer is " << 42 << '\n';
    out.close();

    std::cout << "wrote " << path << '\n';

    // Task 1
    constexpr int kNameCount = 5;
    const std::string names[kNameCount] = {"Ada", "Alan", "Grace", "Bjarne", "Katherine"};
    const std::string names_path = "data/names_out.txt";

    std::ofstream names_out(names_path);
    if (!names_out) {
        std::cerr << "could not open " << names_path << '\n';
        return 1;
    }
    for (int i = 0; i < kNameCount; ++i) {
        names_out << i + 1 << ". " << names[i] << '\n';
    }
    names_out.close();
    std::cout << "wrote " << kNameCount << " names to " << names_path << '\n';

    // Task 2: std::ios::app appends instead of truncating.
    //
    // ANSWER TO THE PREDICTION: the file has 6 lines after every run, not 12.
    // The plain open above truncates the file back to empty each time, and only
    // then does the append add its line. Two runs, same six lines.
    std::ofstream appended(names_path, std::ios::app);
    if (!appended) {
        std::cerr << "could not reopen " << names_path << " for appending\n";
        return 1;
    }
    appended << "6. (added later)\n";
    appended.close();
    std::cout << "appended 1 line\n";

    // Task 3
    constexpr int kSquareCount = 5;
    int squares[kSquareCount] = {1, 4, 9, 16, 25};

    const std::string good_path = "data/squares_out.txt";
    const std::string bad_path = "no_such_dir/squares_out.txt";

    std::cout << "save to " << good_path << "        -> "
              << (save_numbers(good_path, squares, kSquareCount) ? "ok" : "FAILED") << '\n';

    // This is the whole reason the "did it open?" check exists: the directory
    // does not exist, so nothing can be written, and without the check the
    // program would happily report success.
    std::cout << "save to " << bad_path << " -> "
              << (save_numbers(bad_path, squares, kSquareCount) ? "ok" : "FAILED (as expected)")
              << '\n';

    return 0;
}
