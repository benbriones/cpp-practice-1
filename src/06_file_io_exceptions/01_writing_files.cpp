// =============================================================================
//  06_file_io_exceptions / 01_writing_files.cpp
//  Lesson: <fstream>, std::ofstream, and always checking that a file opened
// =============================================================================
//
//  BUILD AND RUN  (run it from the repository root, so the relative paths work)
//    g++ -std=c++23 -Wall -Wextra src/06_file_io_exceptions/01_writing_files.cpp -o write_files
//    ./write_files
//
// -----------------------------------------------------------------------------
//  LESSON
// -----------------------------------------------------------------------------
//  <fstream> gives you file streams. They behave exactly like std::cout and
//  std::cin -- same << and >> operators -- they just point at a file:
//
//        std::ofstream out("notes.txt");     // o = output = WRITING
//        out << "hello\n";
//
//        std::ifstream in("notes.txt");      // i = input  = READING (next file)
//
//  Opening a file can FAIL: a bad path, a missing directory, no permission.
//  A stream that failed to open is false in a condition, so ALWAYS check:
//
//        std::ofstream out(path);
//        if (!out) {
//            std::cerr << "could not open " << path << '\n';
//            return 1;                  // non-zero from main means "failed"
//        }
//
//  Skipping that check is the number one file-I/O bug: every write silently
//  does nothing and the program cheerfully reports success.
//
//  std::cerr is the error stream. Error messages go there, results go to cout.
//
//  CLOSING. The stream closes itself when it goes out of scope, which is one of
//  the nicest things about C++. You can call out.close() early if you want to
//  read the file back in the same program.
//
//  OVERWRITE vs APPEND:
//        std::ofstream out(path);                        // truncates: wipes it
//        std::ofstream out(path, std::ios::app);         // appends to the end
//
//  RELATIVE PATHS are resolved from wherever you RUN the program, not from
//  where the source file lives. Run these from the repo root and "data/x.txt"
//  means <repo>/data/x.txt.
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written -- run it, then open data/greeting_out.txt)
// -----------------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <string>

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

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: write the names
    // -------------------------------------------------------------------------
    //  You have this array:
    //
    //      const std::string names[5] = {"Ada", "Alan", "Grace", "Bjarne", "Katherine"};
    //
    //  Write them to "data/names_out.txt", ONE PER LINE, numbered:
    //
    //      1. Ada
    //      2. Alan
    //      3. Grace
    //      4. Bjarne
    //      5. Katherine
    //
    //  Check the stream opened before writing anything. Then print a summary to
    //  the console:   wrote 5 names to data/names_out.txt
    //
    //  Verify it worked from your shell:  cat data/names_out.txt

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: append, do not overwrite
    // -------------------------------------------------------------------------
    //  Open the SAME file again, this time in append mode, and add one more
    //  line: "6. (added later)". Run the program twice and look at the file.
    //
    //  Predict first: after two runs, how many lines are in the file, and why?
    //  (Think about which of your two opens truncates.)
    //
    //  YOUR PREDICTION:

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: a save function
    // -------------------------------------------------------------------------
    //  Write, above main():
    //
    //      bool save_numbers(const std::string& path, const int values[], int count)
    //
    //  It writes one number per line and returns false if the file could not be
    //  opened -- letting the CALLER decide what to do about the failure, rather
    //  than printing an error from deep inside a helper.
    //
    //  Test it twice:
    //    - with "data/squares_out.txt"                 -> should return true
    //    - with "no_such_dir/squares_out.txt"          -> should return false
    //
    //  Print which one succeeded. That second call is the whole reason the
    //  "did it open?" check exists.

    // TODO

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT (console)
// -----------------------------------------------------------------------------
//    wrote data/greeting_out.txt
//    wrote 5 names to data/names_out.txt
//    appended 1 line
//    save to data/squares_out.txt        -> ok
//    save to no_such_dir/squares_out.txt -> FAILED (as expected)
//
//  And data/names_out.txt should contain the numbered list.
