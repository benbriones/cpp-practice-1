// =============================================================================
//  05_oop / 04_design_your_own.cpp
//  Lesson: designing a class from a description  (no starter code -- that is
//          the exercise)
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/05_oop/04_design_your_own.cpp -o design_your_own
//    ./design_your_own
//
// -----------------------------------------------------------------------------
//  HOW TO DESIGN A SMALL CLASS
// -----------------------------------------------------------------------------
//  Everything so far handed you the class and asked you to fill it in. This
//  time the design is the work. A checklist that will carry you a long way:
//
//    1. WHAT DOES IT KNOW?      -> the private member variables
//    2. WHAT CAN IT DO?         -> the public member functions
//    3. WHAT MUST ALWAYS BE TRUE? -> the invariants your functions must protect
//    4. HOW IS ONE CREATED?     -> the constructor(s), so no object is half-built
//
//  Two rules of thumb from the last three files:
//    - data private by default; make something public only when you must
//    - every function that does not modify the object gets a trailing const
//
// -----------------------------------------------------------------------------
//  YOUR TASK 1: class Person
// -----------------------------------------------------------------------------
//  Design and write a Person class. Requirements:
//
//    KNOWS:  a name (std::string) and an age (int)
//    CAN:
//      - be constructed from a name and an age
//      - report its name and its age
//      - have_birthday()      -> age goes up by one
//      - is_adult() const     -> true when age is 18 or more
//      - greet() const        -> prints "Hi, I'm <name> and I'm <age>."
//
//    MUST ALWAYS BE TRUE: the age is never negative. Decide how the constructor
//    handles being given -5, and write a comment saying what you chose and why.
//    (Clamping to 0 is a reasonable choice here. Throwing an exception is
//    another -- you will meet that in section 06.)
//
//  Then in main(): create two Person objects, greet with both, give one a
//  birthday, and print whether each is an adult.
//
// -----------------------------------------------------------------------------
//  YOUR TASK 2: a class of your own choosing
// -----------------------------------------------------------------------------
//  Pick ONE and design it yourself, from scratch, applying the same checklist.
//  Write the four checklist answers as a comment above the class BEFORE you
//  write any code -- deciding on paper first is the actual skill here.
//
//    - class Book       : title, author, pages, and a current page you can turn
//                         forward (never past the last page) with a
//                         percent_read() function
//    - class Playlist   : a fixed-size array of song titles plus a count, with
//                         add() (refusing when full), remove_last(), size(),
//                         and print_all()
//    - class Thermostat : a current temperature and a target, with
//                         set_target() clamped to a sensible range (say 10-30),
//                         is_heating() and is_cooling()
//    - class Stopwatch  : elapsed seconds, with start(), stop(), tick(),
//                         reset(), and a formatted print as MM:SS
//
//  Exercise it properly in main(): create objects, call every function, and
//  deliberately try the invalid cases (turn past the last page, add to a full
//  playlist, set the thermostat to 99) to prove your class refuses them.
//
// -----------------------------------------------------------------------------
//  YOUR TASK 3 (stretch): give it a base class
// -----------------------------------------------------------------------------
//  Make Person the base of a Student class that adds a school name and a
//  student id, with its own greet-style function. Remember which access level
//  the members Student needs must have.

#include <iostream>
#include <string>

// TODO: write your Person class here (above main, so main can use it)

// TODO: write your second class here

int main() {
    // TODO: create objects and exercise every member function you wrote

    std::cout << "TODO: design your classes, then delete this line\n";

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT
// -----------------------------------------------------------------------------
//  There is no fixed expected output for this file -- it is your design. Aim
//  for something like:
//
//    Hi, I'm Ada and I'm 36.
//    Hi, I'm Sam and I'm 17.
//    Sam has a birthday -> 18
//    Ada adult? 1
//    Sam adult? 1
//
//    "The Pragmatic Programmer" by Hunt & Thomas, 352 pages
//    read to page 88 -> 25% read
//    turning past the last page was refused
//
//  If your class can be pushed into a nonsense state from main(), the design is
//  not finished yet. Go back and close the hole.
