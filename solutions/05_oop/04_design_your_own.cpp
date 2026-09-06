// Reference solution for src/05_oop/04_design_your_own.cpp
//
// This exercise asked you to DESIGN, so there is no single right answer. This
// is one reasonable version -- compare the decisions, not the exact code.

#include <iostream>
#include <string>

// Person
//   KNOWS: a name and an age
//   CAN:   report both, have a birthday, say whether it is an adult, greet
//   ALWAYS TRUE: age is never negative
//   CREATED: from a name and an age
class Person {
public:
    Person(const std::string& name, int age) : name_(name), age_(age < 0 ? 0 : age) {}
    // Choice made: a negative age is clamped to 0 rather than rejected, so the
    // constructor always succeeds and callers never have to handle a failure.
    // The cost is that Person(-5) silently becomes 0 instead of telling anyone.
    // In 06_file_io_exceptions you will see the alternative: throw, and refuse
    // to create the object at all. Neither is wrong -- but pick one on purpose.

    const std::string& name() const { return name_; }
    int age() const { return age_; }

    void have_birthday() { ++age_; }

    bool is_adult() const { return age_ >= 18; }

    void greet() const { std::cout << "Hi, I'm " << name_ << " and I'm " << age_ << ".\n"; }

protected:
    // protected rather than private, so Student (task 3) can use them.
    std::string name_;
    int age_;
};

// Book
//   KNOWS: title, author, page count, current page
//   CAN:   turn a page, report progress
//   ALWAYS TRUE: 0 <= current page <= pages, and pages is at least 1
//   CREATED: from title, author and page count
class Book {
public:
    Book(const std::string& title, const std::string& author, int pages)
        : title_(title), author_(author), pages_(pages > 0 ? pages : 1), current_page_(0) {}

    // Refuses to go past the last page: the invariant is enforced here, so no
    // caller can break it.
    bool turn_to(int page) {
        if (page < 0 || page > pages_) {
            return false;
        }
        current_page_ = page;
        return true;
    }

    double percent_read() const { return 100.0 * current_page_ / pages_; }

    void describe() const {
        std::cout << '"' << title_ << "\" by " << author_ << ", " << pages_ << " pages\n";
    }

private:
    std::string title_;
    std::string author_;
    int pages_;
    int current_page_;
};

// Task 3: Student is a Person with a school and an id.
class Student : public Person {
public:
    Student(const std::string& name, int age, const std::string& school, int id)
        : Person(name, age), school_(school), id_(id) {}

    void introduce() const {
        std::cout << "I'm " << name_ << ", student #" << id_ << " at " << school_ << ".\n";
    }

private:
    std::string school_;
    int id_;
};

int main() {
    Person ada("Ada", 36);
    Person sam("Sam", 17);

    ada.greet();
    sam.greet();

    sam.have_birthday();
    std::cout << "Sam has a birthday -> " << sam.age() << '\n';
    std::cout << "Ada adult? " << ada.is_adult() << '\n';
    std::cout << "Sam adult? " << sam.is_adult() << "\n\n";

    Book pp("The Pragmatic Programmer", "Hunt & Thomas", 352);
    pp.describe();
    pp.turn_to(88);
    std::cout << "read to page 88 -> " << pp.percent_read() << "% read\n";

    // Deliberately try the invalid case to prove the class refuses it.
    if (!pp.turn_to(9999)) {
        std::cout << "turning past the last page was refused\n";
    }
    std::cout << '\n';

    Student maya("Maya", 20, "Central High", 4471);
    maya.greet();      // inherited from Person
    maya.introduce();  // its own

    return 0;
}
