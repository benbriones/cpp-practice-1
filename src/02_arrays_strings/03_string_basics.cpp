// =============================================================================
//  02_arrays_strings / 03_string_basics.cpp
//  Lesson: std::string, length, indexing, iterating, simple manipulation
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/02_arrays_strings/03_string_basics.cpp -o string_basics
//    ./string_basics
//
// -----------------------------------------------------------------------------
//  LESSON
// -----------------------------------------------------------------------------
//  std::string (from <string>) holds text and knows its own length. Unlike an
//  array it can grow and shrink.
//
//        std::string name = "Ada";
//        name.length()      -> 3        (name.size() is the same thing)
//        name[0]            -> 'A'      a single char, indexed from 0 like arrays
//        name += " L";      -> "Ada L"  append
//        name.empty()       -> false
//
//  A single character uses SINGLE quotes ('A'), a string uses DOUBLE ("A").
//  They are different types and the compiler will tell you off for mixing them.
//
//  TWO WAYS TO VISIT EVERY CHARACTER:
//
//        for (std::size_t i = 0; i < text.length(); ++i) {   // when you need i
//            std::cout << text[i];
//        }
//
//        for (char c : text) {                               // when you do not
//            std::cout << c;
//        }
//
//  Why std::size_t and not int? length() returns an unsigned type, and
//  comparing a signed int against it makes the compiler warn. std::size_t is
//  simply "the type C++ uses for sizes and indexes".
//
//  USEFUL CHARACTER HELPERS (from <cctype>):
//
//        std::tolower('A')   -> 'a'      std::toupper('a') -> 'A'
//        std::isalpha(c)     -> is it a letter?
//        std::isdigit(c)     -> is it 0-9?
//
//  These take an int, so pass characters as std::tolower(static_cast<unsigned char>(c))
//  and cast the result back to char. That looks fussy; it is the standard way to
//  stay correct, and the compiler warnings will remind you.
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written)
// -----------------------------------------------------------------------------

#include <cctype>
#include <iostream>
#include <string>

int main() {
    std::string word = "Programming";

    std::cout << "word          : " << word << '\n';
    std::cout << "length        : " << word.length() << '\n';
    std::cout << "first char    : " << word[0] << '\n';
    std::cout << "last char     : " << word[word.length() - 1] << '\n';

    std::cout << "one per line  : ";
    for (char c : word) {
        std::cout << c << '.';
    }
    std::cout << '\n';

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: count the vowels
    // -------------------------------------------------------------------------
    //  Count how many of a, e, i, o, u appear in `word`, ignoring case, and
    //  print:   vowels        : 3
    //
    //  Hints:
    //    - loop over the characters, keep a counter
    //    - lowercase the character first so 'A' and 'a' are handled by one test
    //    - a chain of ||  ("or") is perfectly fine here:
    //          if (lower == 'a' || lower == 'e' || ...)

    // TODO: count and print the vowels

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: build a reversed copy
    // -------------------------------------------------------------------------
    //  Build a NEW std::string containing `word` backwards, then print it:
    //      reversed      : gnimmargorP
    //
    //  Start with an empty std::string and append one character at a time,
    //  walking the original from the last index down to 0.
    //
    //  Careful: a countdown loop with std::size_t is a classic trap, because an
    //  unsigned value never goes below 0 -- it wraps around to a huge number and
    //  loops forever. Two safe options:
    //      - count UP and prepend, or
    //      - index as  word[word.length() - 1 - i]  while counting up.

    // TODO: build and print the reversed string

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: ask the user
    // -------------------------------------------------------------------------
    //  Read a whole line of text from the user and report its length and vowel
    //  count. Use std::getline(std::cin, line) rather than std::cin >> line,
    //  because >> stops at the first space and you want the entire line.
    //
    //      Enter a sentence: hello there
    //      that line has 11 characters and 4 vowels
    //
    //  If you find yourself copying your vowel-counting loop, that is a sign it
    //  wants to be a function. Write  int count_vowels(const std::string& text)
    //  above main() and call it twice.

    // TODO: read a line and report on it

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT
// -----------------------------------------------------------------------------
//    word          : Programming
//    length        : 11
//    first char    : P
//    last char     : g
//    one per line  : P.r.o.g.r.a.m.m.i.n.g.
//    vowels        : 3
//    reversed      : gnimmargorP
//    Enter a sentence: hello there
//    that line has 11 characters and 4 vowels
