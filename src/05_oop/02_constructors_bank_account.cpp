// =============================================================================
//  05_oop / 02_constructors_bank_account.cpp
//  Lesson: constructors, initialiser lists, and encapsulation that enforces rules
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/05_oop/02_constructors_bank_account.cpp -o bank_account
//    ./bank_account
//
// -----------------------------------------------------------------------------
//  LESSON 1: constructors
// -----------------------------------------------------------------------------
//  In the last file you had to build an object and THEN set it up:
//
//        Rectangle r;
//        r.set_size(3, 4);      // two steps, and step two is easy to forget
//
//  A CONSTRUCTOR is a special member function that runs automatically when an
//  object is created, so an object is never half-built. It has the same name as
//  the class and no return type:
//
//        class Point {
//        public:
//            Point(int x, int y) : x_(x), y_(y) {}
//            //                  ^^^^^^^^^^^^^^
//            //                  member initialiser list
//        private:
//            int x_;
//            int y_;
//        };
//
//        Point p(3, 4);      // the constructor runs here
//
//  The part after the colon is the MEMBER INITIALISER LIST. It initialises
//  members directly. You could instead assign inside the braces:
//
//        Point(int x, int y) { x_ = x; y_ = y; }     // works, but...
//
//  ...that first default-constructs the members and then overwrites them. The
//  initialiser list is the idiomatic form. Get in the habit now.
//
//  A class can have several constructors as long as the parameters differ:
//
//        Point() : x_(0), y_(0) {}               // default constructor
//        Point(int x, int y) : x_(x), y_(y) {}
//
// -----------------------------------------------------------------------------
//  LESSON 2: encapsulation is about INVARIANTS
// -----------------------------------------------------------------------------
//  A bank balance should never be changed to an arbitrary number by outside
//  code. Keep it private and expose only operations that make sense -- each of
//  which can check the rules first:
//
//        bool deposit(double amount) {
//            if (amount <= 0.0) {
//                return false;          // refuse nonsense
//            }
//            balance_ += amount;
//            return true;
//        }
//
//  The rule "balance is only changed by valid deposits and withdrawals" is an
//  INVARIANT: something the class guarantees is always true. Private data plus
//  checked public functions is how a class keeps its promises.
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written -- read the constructor carefully)
// -----------------------------------------------------------------------------

#include <iostream>
#include <string>

class BankAccount {
public:
    // Constructor: an account cannot exist without an owner, and never starts
    // with a negative balance.
    BankAccount(const std::string& owner, double starting_balance)
        : owner_(owner), balance_(starting_balance > 0.0 ? starting_balance : 0.0) {}

    const std::string& owner() const { return owner_; }
    double balance() const { return balance_; }

    bool deposit(double amount) {
        if (amount <= 0.0) {
            return false;
        }
        balance_ += amount;
        return true;
    }

    void print() const { std::cout << owner_ << ": " << balance_ << '\n'; }

private:
    std::string owner_;
    double balance_;
};

int main() {
    BankAccount acct("Ada", 100.0);
    acct.print();

    acct.deposit(50.0);
    acct.print();

    std::cout << "deposit(-10) allowed? " << acct.deposit(-10.0) << '\n';
    acct.print();
    std::cout << '\n';

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: withdraw
    // -------------------------------------------------------------------------
    //  Add to BankAccount:
    //
    //      bool withdraw(double amount)
    //
    //  Refuse (return false, change nothing) when:
    //      - amount is zero or negative
    //      - amount is greater than the current balance  (no overdrafts)
    //  Otherwise subtract it and return true.
    //
    //  Then test all three cases and print the balance after each:
    //      withdraw(30)  -> 1, balance 120
    //      withdraw(500) -> 0, balance 120
    //      withdraw(-5)  -> 0, balance 120

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: a second constructor
    // -------------------------------------------------------------------------
    //  Add a constructor taking only an owner name, starting the balance at 0.
    //
    //      BankAccount empty("Grace");
    //
    //  Tip: rather than repeating the body, one constructor can call the other:
    //
    //      BankAccount(const std::string& owner) : BankAccount(owner, 0.0) {}
    //
    //  That is a DELEGATING constructor -- the rules live in exactly one place.

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: transfer
    // -------------------------------------------------------------------------
    //  Write a FREE function (not a member) above main():
    //
    //      bool transfer(BankAccount& from, BankAccount& to, double amount)
    //
    //  It withdraws from one account and deposits into the other, returning
    //  whether it worked. Important: if the withdraw fails, do NOT deposit.
    //
    //  The & in `BankAccount& from` means "a reference" -- the real account, not
    //  a copy. It is like a pointer that can never be null and needs no *.
    //  Without the &, you would be modifying copies and the real accounts would
    //  not change (exactly the by-value trap from 04_pointers).
    //
    //  Test both a successful and a failing transfer, printing both accounts.
    //
    //  Then think about: could transfer() have been written if balance_ were
    //  public? Yes -- but it would have been able to skip every rule. That is
    //  the argument for encapsulation in one sentence.

    // TODO

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT
// -----------------------------------------------------------------------------
//    Ada: 100
//    Ada: 150
//    deposit(-10) allowed? 0
//    Ada: 150
//
//    withdraw(30)  -> 1, balance 120
//    withdraw(500) -> 0, balance 120
//    withdraw(-5)  -> 0, balance 120
//    Grace: 0
//    transfer 20 Ada -> Grace: 1
//    Ada: 100
//    Grace: 20
//    transfer 999 Ada -> Grace: 0
//    Ada: 100
//    Grace: 20
