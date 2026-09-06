// =============================================================================
//  03_loops / 04_number_guessing.cpp
//  Lesson: a do-while loop driving a real interactive program  (mini project)
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/03_loops/04_number_guessing.cpp -o guessing
//    ./guessing
//
// -----------------------------------------------------------------------------
//  LESSON
// -----------------------------------------------------------------------------
//  This one ties together everything so far: input, conditions, functions and a
//  loop that runs an unknown number of times.
//
//  A do-while is right for a menu or a prompt, because you always want to ask
//  at least once before you can possibly know whether to stop:
//
//        int guess = 0;
//        do {
//            std::cout << "guess: ";
//            std::cin >> guess;
//            // ...react to the guess...
//        } while (guess != secret);
//
//  RANDOM NUMBERS (from <random>). You do not need to understand the details
//  yet; treat these three lines as a recipe:
//
//        std::random_device seed;                       // a source of randomness
//        std::mt19937 gen(seed());                      // the generator
//        std::uniform_int_distribution<int> dist(1, 100);  // the range you want
//        int secret = dist(gen);                        // one number in 1..100
//
//  BAD INPUT. If the user types "abc" when you asked for a number, std::cin
//  goes into a failed state and every later read is skipped -- which turns your
//  loop into an infinite one. The standard repair:
//
//        if (!std::cin) {                 // the read failed
//            std::cin.clear();            // clear the error flag
//            std::cin.ignore(10000, '\n');// throw away the rest of the bad line
//        }
//
//  Also handle end-of-input: if the user presses Ctrl-D the stream closes and
//  never recovers, so you must break out rather than loop forever.
//
// -----------------------------------------------------------------------------
//  YOUR TASK -- build the whole game
// -----------------------------------------------------------------------------
//  1. Pick a secret number between 1 and 100 using the recipe above.
//  2. Loop: prompt for a guess, read it, and respond
//         "too low" / "too high" / "correct!"
//     Use a do-while, since you always ask at least once.
//  3. Count the attempts and, when they get it, print:
//         correct! it took you 6 guesses
//  4. Handle bad input as shown above instead of spinning forever.
//  5. Give the player a maximum of 7 guesses. If they run out, reveal the
//     answer:  out of guesses -- it was 42
//
//  While developing, set `secret` to a fixed value like 42 so you can test the
//  branches quickly; switch to the random version once it all works.
//
//  Stretch goals, once the basic game runs:
//    - reject guesses outside 1..100 without spending an attempt
//    - after the game, ask "play again? (y/n)" and wrap everything in an outer
//      loop -- this is where a do-while really earns its keep

#include <iostream>
#include <random>

int main() {
    constexpr int kMaxGuesses = 7;

    // TODO: pick the secret number (start with a fixed 42 while testing)

    // TODO: the guessing loop -- prompt, read, compare, count attempts

    // TODO: after the loop, report the win or reveal the answer

    // These two lines only exist so the file compiles before you start.
    // Delete them once you have written the real thing.
    std::cout << "TODO: write the guessing game (max " << kMaxGuesses << " guesses)\n";

    return 0;
}

// -----------------------------------------------------------------------------
//  EXAMPLE SESSION
// -----------------------------------------------------------------------------
//    I am thinking of a number between 1 and 100. You get 7 guesses.
//    guess 1/7: 50
//    too high
//    guess 2/7: 25
//    too low
//    guess 3/7: 37
//    too low
//    guess 4/7: 43
//    too high
//    guess 5/7: 40
//    too low
//    guess 6/7: 42
//    correct! it took you 6 guesses
