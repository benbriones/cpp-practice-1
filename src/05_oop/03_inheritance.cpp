// =============================================================================
//  05_oop / 03_inheritance.cpp
//  Lesson: basic inheritance -- building a new class on top of an existing one
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/05_oop/03_inheritance.cpp -o inheritance
//    ./inheritance
//
// -----------------------------------------------------------------------------
//  LESSON 1: "is a"
// -----------------------------------------------------------------------------
//  Inheritance lets one class reuse another. A Dog IS AN Animal, so Dog can
//  start from everything Animal already has and add its own bits:
//
//        class Animal {                      <- base class
//        public:
//            void eat() const { ... }
//        protected:
//            std::string name_;
//        };
//
//        class Dog : public Animal {         <- derived class
//        public:                ^^^^^^
//            void fetch() const { ... }      <- Dog also has eat()
//        };
//
//        Dog d;
//        d.eat();     // inherited from Animal
//        d.fetch();   // Dog's own
//
//  Read `class Dog : public Animal` as "Dog is a kind of Animal".
//
// -----------------------------------------------------------------------------
//  LESSON 2: protected, and constructing the base
// -----------------------------------------------------------------------------
//  A third access level appears once inheritance is involved:
//
//        public:      everyone
//        protected:   this class AND classes derived from it
//        private:     this class only -- not even derived classes
//
//  So members a derived class needs to touch go in protected, and members that
//  are nobody else's business stay private.
//
//  The base class part must be built first, and the derived constructor says
//  how, in its initialiser list:
//
//        class Animal {
//        public:
//            Animal(const std::string& name) : name_(name) {}
//        protected:
//            std::string name_;
//        };
//
//        class Dog : public Animal {
//        public:
//            Dog(const std::string& name, const std::string& breed)
//                : Animal(name), breed_(breed) {}
//            //  ^^^^^^^^^^^^ build the Animal part first
//        private:
//            std::string breed_;
//        };
//
//  Order of construction: base first, then the derived class's own members.
//
//  (There is much more to inheritance -- virtual functions, polymorphism,
//   abstract classes. Those come later. Right now, just get comfortable with
//   "a derived class gets everything the base had, plus extras".)
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written)
// -----------------------------------------------------------------------------

#include <iostream>
#include <string>

class Animal {
public:
    Animal(const std::string& name, int age) : name_(name), age_(age) {}

    const std::string& name() const { return name_; }
    int age() const { return age_; }

    void eat() const { std::cout << name_ << " is eating.\n"; }

    void describe() const { std::cout << name_ << " is " << age_ << " years old.\n"; }

protected:
    // protected, not private: Dog is allowed to use these directly.
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

int main() {
    Animal generic("Some animal", 3);
    generic.describe();
    generic.eat();

    Dog rex("Rex", 5, "Border Collie");
    rex.describe();  // inherited from Animal
    rex.eat();       // inherited from Animal
    rex.bark();      // Dog's own
    std::cout << rex.name() << " is a " << rex.breed() << "\n\n";

    // Try uncommenting -- it will NOT compile, because Animal has no bark():
    //     generic.bark();
    // Inheritance flows one way: a Dog is an Animal, an Animal is not a Dog.

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: add a Cat
    // -------------------------------------------------------------------------
    //  Write a Cat class deriving from Animal, with:
    //    - a constructor taking name, age, and a bool `indoor`
    //    - a meow() member function printing "<name> says meow!"
    //    - bool is_indoor() const
    //
    //  Create one and call describe(), eat(), meow(), and print is_indoor().
    //  You are writing almost no code here -- describe() and eat() come free.
    //  That reuse is the entire point of inheritance.

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: add behaviour to the base class
    // -------------------------------------------------------------------------
    //  Add to Animal:
    //
    //      void have_birthday()    // adds 1 to age_ and prints
    //                              // "<name> is now <age>!"
    //
    //  Then call it on your Dog AND your Cat. One function written once, working
    //  for every class that derives from Animal.
    //
    //  While you are there: should have_birthday() be const? Work out why not.

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: a deeper chain
    // -------------------------------------------------------------------------
    //  Derive Puppy from Dog (not from Animal):
    //
    //      class Puppy : public Dog { ... };
    //
    //  Give it a constructor that forwards name, age and breed up to Dog, and a
    //  member function play() printing "<name> is chasing its tail!".
    //
    //  A Puppy now has everything from Animal AND everything from Dog. Prove it
    //  by calling describe(), bark(), and play() on one Puppy object.

    // TODO

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT
// -----------------------------------------------------------------------------
//    Some animal is 3 years old.
//    Some animal is eating.
//    Rex is 5 years old.
//    Rex is eating.
//    Rex says woof!
//    Rex is a Border Collie
//
//    Whiskers is 2 years old.
//    Whiskers is eating.
//    Whiskers says meow!
//    indoor cat? 1
//    Rex is now 6!
//    Whiskers is now 3!
//    Bolt is 1 years old.
//    Bolt says woof!
//    Bolt is chasing its tail!
