// Solution to src/03_loops/04_number_guessing.cpp
// Lesson: a do-while loop driving a real interactive program

#include <iostream>
#include <random>

int main() {
    constexpr int kMaxGuesses = 7;

    // The random recipe. Swap in a fixed value while testing your branches.
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<int> dist(1, 100);
    const int secret = dist(gen);

    std::cout << "I am thinking of a number between 1 and 100. You get " << kMaxGuesses
              << " guesses.\n";

    int attempts = 0;
    bool won = false;

    do {
        std::cout << "guess " << attempts + 1 << '/' << kMaxGuesses << ": ";

        int guess = 0;
        if (!(std::cin >> guess)) {
            if (std::cin.eof()) {
                std::cout << "\ninput closed -- the number was " << secret << '\n';
                return 0;  // the stream will never recover; do not loop forever
            }
            // Not a number: clear the error and throw the bad line away.
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "that is not a number, try again\n";
            continue;  // a bad line does not cost an attempt
        }

        if (guess < 1 || guess > 100) {
            std::cout << "out of range -- pick something between 1 and 100\n";
            continue;
        }

        ++attempts;

        if (guess < secret) {
            std::cout << "too low\n";
        } else if (guess > secret) {
            std::cout << "too high\n";
        } else {
            won = true;
        }
    } while (!won && attempts < kMaxGuesses);

    if (won) {
        std::cout << "correct! it took you " << attempts << " guesses\n";
    } else {
        std::cout << "out of guesses -- it was " << secret << '\n';
    }

    return 0;
}
