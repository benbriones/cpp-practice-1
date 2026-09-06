// Solution to src/05_oop/03_inheritance.cpp
// Lesson: basic inheritance

#include <iostream>
#include <string>

class Animal {
public:
    Animal(const std::string& name, int age) : name_(name), age_(age) {}

    const std::string& name() const { return name_; }
    int age() const { return age_; }

    void eat() const { std::cout << name_ << " is eating.\n"; }

    void describe() const { std::cout << name_ << " is " << age_ << " years old.\n"; }

    // Task 2. NOT const: it modifies age_. Marking it const would not compile,
    // which is exactly what const is for -- the compiler checks your promise.
    // Written once here, and every derived class gets it for free.
    void have_birthday() {
        ++age_;
        std::cout << name_ << " is now " << age_ << "!\n";
    }

protected:
    std::string name_;
    int age_;
};

class Dog : public Animal {
public:
    Dog(const std::string& name, int age, const std::string& breed)
        : Animal(name, age), breed_(breed) {}

    const std::string& breed() const { return breed_; }

    void bark() const { std::cout << name_ << " says woof!\n"; }

private:
    std::string breed_;
};

// Task 1: Cat needs almost no code -- describe() and eat() are inherited.
class Cat : public Animal {
public:
    Cat(const std::string& name, int age, bool indoor) : Animal(name, age), indoor_(indoor) {}

    bool is_indoor() const { return indoor_; }

    void meow() const { std::cout << name_ << " says meow!\n"; }

private:
    bool indoor_;
};

// Task 3: a Puppy is a Dog, which is an Animal. It gets everything from both.
class Puppy : public Dog {
public:
    Puppy(const std::string& name, int age, const std::string& breed) : Dog(name, age, breed) {}

    void play() const { std::cout << name_ << " is chasing its tail!\n"; }
};

int main() {
    Animal generic("Some animal", 3);
    generic.describe();
    generic.eat();

    Dog rex("Rex", 5, "Border Collie");
    rex.describe();
    rex.eat();
    rex.bark();
    std::cout << rex.name() << " is a " << rex.breed() << "\n\n";

    // Task 1
    Cat whiskers("Whiskers", 2, true);
    whiskers.describe();
    whiskers.eat();
    whiskers.meow();
    std::cout << "indoor cat? " << whiskers.is_indoor() << '\n';

    // Task 2: one function, working for every derived class.
    rex.have_birthday();
    whiskers.have_birthday();

    // Task 3
    Puppy bolt("Bolt", 1, "Beagle");
    bolt.describe();  // from Animal
    bolt.bark();      // from Dog
    bolt.play();      // its own

    return 0;
}
