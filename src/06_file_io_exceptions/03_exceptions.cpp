// =============================================================================
//  06_file_io_exceptions / 03_exceptions.cpp
//  Lesson: throw, try, catch, std::exception  (introductory)
// =============================================================================
//
//  BUILD AND RUN  (from the repository root)
//    g++ -std=c++23 -Wall -Wextra src/06_file_io_exceptions/03_exceptions.cpp -o exceptions
//    ./exceptions
//
// -----------------------------------------------------------------------------
//  LESSON 1: when returning false is not enough
// -----------------------------------------------------------------------------
//  So far, failures were reported by RETURNING something: false, -1, nullptr.
//  That works well, but it has two weaknesses: the caller can ignore the return
//  value, and a constructor has no return value to use at all.
//
//  An EXCEPTION is the other tool. You THROW an object describing what went
//  wrong; the normal flow stops immediately and control jumps to the nearest
//  matching CATCH block, however many function calls up that happens to be.
//
//        int safe_divide(int a, int b) {
//            if (b == 0) {
//                throw std::invalid_argument("division by zero");
//            }
//            return a / b;                 // never reached when b == 0
//        }
//
//        try {
//            std::cout << safe_divide(10, 0);   // throws
//            std::cout << "this line never runs";
//        } catch (const std::invalid_argument& e) {
//            std::cout << "caught: " << e.what() << '\n';
//        }
//
//  e.what() gives the message you threw. Catch BY CONST REFERENCE
//  (const std::exception&) -- catching by value copies and can slice the object.
//
// -----------------------------------------------------------------------------
//  LESSON 2: the standard exception types
// -----------------------------------------------------------------------------
//  From <stdexcept>, all deriving from std::exception (in <exception>):
//
//        std::invalid_argument   a caller handed you nonsense
//        std::out_of_range       an index or value outside the allowed range
//        std::runtime_error      something failed while running (file, network)
//        std::logic_error        a bug in the program's own logic
//
//  Because they all derive from std::exception, one catch can handle them all:
//
//        catch (const std::exception& e) { ... }   // catches any of the above
//
//  Order matters: catch blocks are tried top to bottom, so list the SPECIFIC
//  types first and the general std::exception last. Put it first and the
//  specific handlers below it can never run.
//
//  A try can have several catch blocks:
//
//        try { ... }
//        catch (const std::out_of_range& e)  { ... }   // specific
//        catch (const std::exception& e)     { ... }   // everything else
//
// -----------------------------------------------------------------------------
//  LESSON 3: when to use which
// -----------------------------------------------------------------------------
//  Rough guidance while you are learning:
//    - EXPECTED, routine outcomes (a user typo, a search that finds nothing)
//      -> return a bool / -1 / nullptr as you have been doing
//    - EXCEPTIONAL, "I cannot possibly continue" situations
//      -> throw
//
//  Exceptions are not free and they are not for control flow. But when a
//  constructor is handed impossible arguments, throwing is exactly right.
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written)
// -----------------------------------------------------------------------------

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

int main() {
    try {
        std::cout << "10 / 2 = " << checked_divide(10, 2) << '\n';
        std::cout << "10 / 0 = " << checked_divide(10, 0) << '\n';
        std::cout << "you will never see this line\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "caught invalid_argument: " << e.what() << '\n';
    }
    std::cout << "the program carries on normally\n\n";

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: element_at
    // -------------------------------------------------------------------------
    //  Write above main():
    //
    //      int element_at(const int values[], int count, int index)
    //
    //  Throw std::out_of_range when index is negative or >= count; otherwise
    //  return the element. Include the bad index in the message.
    //
    //  Call it inside a try block with a valid index and then an invalid one:
    //
    //      element_at(data, 5, 2)  -> 30
    //      caught out_of_range: index 9 is outside 0..4
    //
    //  Compare this with just reading data[9] directly: that is undefined
    //  behaviour and might quietly return garbage. The throw turns a silent
    //  disaster into a loud, catchable, debuggable event.

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: a function that opens a file
    // -------------------------------------------------------------------------
    //  Write:
    //
    //      int sum_file(const std::string& path)
    //
    //  It opens the file, sums the ints in it, and returns the total. But:
    //    - if the file will not open, throw std::runtime_error naming the path
    //    - if the file opens but contains no numbers at all, throw
    //      std::runtime_error with a different message
    //
    //  Call it three times inside try/catch blocks:
    //      sum_file("data/numbers.txt")          -> 314
    //      sum_file("data/does_not_exist.txt")   -> caught: cannot open ...
    //      sum_file("data/empty_out.txt")        -> caught: no numbers in ...
    //
    //  (Create that empty file first with an ofstream, or from your shell with
    //   `touch data/empty_out.txt`.)
    //
    //  Notice how much cleaner the caller reads than checking a bool after
    //  every single call -- and notice that the caller CANNOT forget to handle
    //  the failure, because an uncaught exception terminates the program.

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: a constructor that refuses bad input
    // -------------------------------------------------------------------------
    //  In 05_oop you clamped a bad age to 0. Here is the other option.
    //
    //  Write a small class:
    //
    //      class Temperature {
    //      public:
    //          Temperature(double celsius);   // throw std::out_of_range below
    //          double celsius() const;        // absolute zero (-273.15)
    //          double fahrenheit() const;
    //      private:
    //          double celsius_;
    //      };
    //
    //  Build one valid Temperature and print both scales. Then try to build
    //  Temperature(-500) inside a try block and catch the failure:
    //
    //      20C = 68F
    //      caught: -500 is below absolute zero
    //
    //  The important idea: because the constructor threw, no half-valid
    //  Temperature object ever came into existence. An object either satisfies
    //  its invariants or it does not exist at all.
    //
    //  Finally, wrap all three of your tasks in ONE outer try block with a
    //  single  catch (const std::exception& e)  at the end, to see that one
    //  handler can catch every kind above.

    // TODO

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT
// -----------------------------------------------------------------------------
//    10 / 2 = 5
//    10 / 0 = caught invalid_argument: division by zero
//    the program carries on normally
//
//    element_at(data, 5, 2) = 30
//    caught out_of_range: index 9 is outside 0..4
//    sum_file(data/numbers.txt) = 314
//    caught: cannot open data/does_not_exist.txt
//    caught: no numbers in data/empty_out.txt
//    20C = 68F
//    caught: -500 is below absolute zero
