// Solution to src/02_arrays_strings/03_string_basics.cpp
// Lesson: std::string, length, indexing, iterating, simple manipulation

#include <cctype>
#include <iostream>
#include <string>

// Task 3 asked for this: the vowel loop was needed twice, so it became a
// function. `const std::string&` means "look at the caller's string, do not
// copy it, do not modify it".
int count_vowels(const std::string& text) {
    int vowels = 0;
    for (char c : text) {
        // tolower takes an int; the unsigned char cast is the standard safe way.
        char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u') {
            ++vowels;
        }
    }
    return vowels;
}

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

    // Task 1
    std::cout << "vowels        : " << count_vowels(word) << '\n';

    // Task 2: count UP but index from the back, which avoids the unsigned
    // countdown trap entirely.
    std::string reversed;
    for (std::size_t i = 0; i < word.length(); ++i) {
        reversed += word[word.length() - 1 - i];
    }
    std::cout << "reversed      : " << reversed << '\n';

    // Task 3: getline reads the whole line, spaces included.
    std::cout << "Enter a sentence: ";
    std::string line;
    if (std::getline(std::cin, line)) {
        std::cout << "that line has " << line.length() << " characters and "
                  << count_vowels(line) << " vowels\n";
    }

    return 0;
}
