// =============================================================================
//  06_file_io_exceptions / 02_reading_files.cpp
//  Lesson: std::ifstream -- reading a file value by value and line by line
// =============================================================================
//
//  BUILD AND RUN  (from the repository root)
//    g++ -std=c++23 -Wall -Wextra src/06_file_io_exceptions/02_reading_files.cpp -o read_files
//    ./read_files
//
//  This exercise reads data/numbers.txt and data/names.txt, which already exist
//  in this repository.
//
// -----------------------------------------------------------------------------
//  LESSON
// -----------------------------------------------------------------------------
//  std::ifstream reads. Same open-and-check ritual as writing:
//
//        std::ifstream in("data/numbers.txt");
//        if (!in) {
//            std::cerr << "could not open the file\n";
//            return 1;
//        }
//
//  TWO WAYS TO READ, and picking the right one matters:
//
//  1. VALUE BY VALUE with >> . Whitespace (spaces, tabs, newlines) is skipped
//     automatically, so this reads numbers no matter how they are laid out:
//
//        int n = 0;
//        while (in >> n) {          // the loop ends when a read fails
//            sum += n;
//        }
//
//     Why does `while (in >> n)` work as a condition? The stream converts to
//     false once a read fails -- either at end of file or on bad input. This is
//     THE standard C++ reading loop; recognise it on sight.
//
//  2. LINE BY LINE with std::getline. Use it when lines matter, or when a line
//     contains spaces you want to keep:
//
//        std::string line;
//        while (std::getline(in, line)) {
//            std::cout << line << '\n';
//        }
//
//  Do not write `while (!in.eof())`. It checks end-of-file BEFORE the read has
//  happened, so the last item gets processed twice. Put the read itself in the
//  condition, as above.
//
//  Mixing >> and getline needs care: >> leaves the newline sitting in the
//  stream, so a getline straight afterwards returns an empty line. If you hit
//  that, in.ignore() past the newline first.
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written)
// -----------------------------------------------------------------------------

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

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: sum the numbers
    // -------------------------------------------------------------------------
    //  Open "data/numbers.txt" (check it opened!) and read it value by value
    //  with the `while (in >> n)` loop. Report:
    //
    //      count   : 8
    //      sum     : 314
    //      average : 39.25
    //      largest : 89
    //
    //  All four come out of ONE pass over the file -- do not open it four times.
    //  Watch out for integer division in the average, and think about what to
    //  print if the file turns out to be empty.

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: a missing file
    // -------------------------------------------------------------------------
    //  Try to open "data/does_not_exist.txt" and print a clear message rather
    //  than crashing or silently reading nothing:
    //
    //      data/does_not_exist.txt: no such file (that is the expected result here)
    //
    //  Do NOT return early -- this failure is expected, so report it and keep
    //  going to task 3.

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: mixed data
    // -------------------------------------------------------------------------
    //  "data/scores.txt" holds a name and a score per line:
    //
    //      Ada 95
    //      Alan 88
    //      ...
    //
    //  Read it with  while (in >> name >> score)  and print each pair, then the
    //  average score.
    //
    //  One line of that file is deliberately broken: `oops not-a-number`.
    //  Run it and see what happens -- the >> that expects an int fails, the
    //  stream goes into a failed state, and your loop stops early. That is not
    //  a bug in your code; it is the stream protecting you.
    //
    //  Report how many lines you managed to read before stopping:
    //
    //      read 3 valid entries, then hit bad data
    //
    //  Recovering from that (clear() and skipping the bad line) is exactly what
    //  the next file is about.

    // TODO

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT
// -----------------------------------------------------------------------------
//    --- data/names.txt line by line ---
//    1: Ada Lovelace
//    2: Alan Turing
//    3: Grace Hopper
//    4: Bjarne Stroustrup
//    5: Katherine Johnson
//    read 5 lines
//
//    count   : 8
//    sum     : 314
//    average : 39.25
//    largest : 89
//    data/does_not_exist.txt: no such file (that is the expected result here)
//    Ada 95
//    Alan 88
//    Grace 91
//    read 3 valid entries, then hit bad data
//    average score: 91.3333
