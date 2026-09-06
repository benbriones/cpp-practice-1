// Solution to src/05_oop/02_constructors_bank_account.cpp
// Lesson: constructors, initialiser lists, encapsulation that enforces rules

#include <iostream>
#include <string>

class BankAccount {
public:
    BankAccount(const std::string& owner, double starting_balance)
        : owner_(owner), balance_(starting_balance > 0.0 ? starting_balance : 0.0) {}

    // Task 2: a delegating constructor. It calls the other one rather than
    // repeating the rules, so the "never negative" check lives in one place.
    BankAccount(const std::string& owner) : BankAccount(owner, 0.0) {}

    const std::string& owner() const { return owner_; }
    double balance() const { return balance_; }

    bool deposit(double amount) {
        if (amount <= 0.0) {
            return false;
        }
        balance_ += amount;
        return true;
    }

    // Task 1: refuse anything that would break the invariant, and change
    // nothing when refusing.
    bool withdraw(double amount) {
        if (amount <= 0.0) {
            return false;
        }
        if (amount > balance_) {
            return false;  // no overdrafts
        }
        balance_ -= amount;
        return true;
    }

    void print() const { std::cout << owner_ << ": " << balance_ << '\n'; }

private:
    std::string owner_;
    double balance_;
};

// Task 3. The & means these are the caller's real accounts, not copies.
// Withdraw FIRST and give up if it fails -- otherwise money is created from
// nothing, which is exactly the kind of bug encapsulation exists to prevent.
bool transfer(BankAccount& from, BankAccount& to, double amount) {
    if (!from.withdraw(amount)) {
        return false;
    }
    return to.deposit(amount);
}

int main() {
    BankAccount acct("Ada", 100.0);
    acct.print();

    acct.deposit(50.0);
    acct.print();

    std::cout << "deposit(-10) allowed? " << acct.deposit(-10.0) << '\n';
    acct.print();
    std::cout << '\n';

    // Task 1
    std::cout << "withdraw(30)  -> " << acct.withdraw(30.0) << ", balance " << acct.balance()
              << '\n';
    std::cout << "withdraw(500) -> " << acct.withdraw(500.0) << ", balance " << acct.balance()
              << '\n';
    std::cout << "withdraw(-5)  -> " << acct.withdraw(-5.0) << ", balance " << acct.balance()
              << '\n';

    // Task 2
    BankAccount grace("Grace");
    grace.print();

    // Task 3
    std::cout << "transfer 20 Ada -> Grace: " << transfer(acct, grace, 20.0) << '\n';
    acct.print();
    grace.print();

    std::cout << "transfer 999 Ada -> Grace: " << transfer(acct, grace, 999.0) << '\n';
    acct.print();
    grace.print();

    return 0;
}
