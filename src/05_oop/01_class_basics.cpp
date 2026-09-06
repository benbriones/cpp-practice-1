// =============================================================================
//  05_oop / 01_class_basics.cpp
//  Lesson: classes, objects, public vs private, member variables and functions
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/05_oop/01_class_basics.cpp -o class_basics
//    ./class_basics
//
// -----------------------------------------------------------------------------
//  LESSON
// -----------------------------------------------------------------------------
//  A class is a new TYPE you invent: some data bundled with the functions that
//  work on it. An OBJECT is one particular thing of that type.
//
//        class Rectangle {           <- the blueprint (written once)
//        public:
//            void set_size(double w, double h);   <- member functions
//            double area() const;
//
//        private:
//            double width_ = 0.0;                 <- member variables (fields)
//            double height_ = 0.0;
//        };                          <- do not forget this semicolon!
//
//        Rectangle r;                <- an object (as many as you like)
//        r.set_size(3, 4);           <- call a member function with a dot
//        std::cout << r.area();      <- 12
//
//  PUBLIC vs PRIVATE -- the heart of it:
//
//        public:   anyone outside the class may use these
//        private:  only the class's own member functions may touch these
//
//  Members are private by default in a class. Making the DATA private and
//  offering a small set of public functions is called ENCAPSULATION: outside
//  code cannot put the object into a nonsense state, because it can only go
//  through the doors you provided.
//
//  Two conventions used in this course:
//    - a trailing underscore (width_) marks a member variable at a glance
//    - `const` after a member function ("double area() const") promises the
//      function does not modify the object. Mark every read-only function const.
//
//  Defining member functions INSIDE the class is fine for small ones. You can
//  also declare inside and define outside with Rectangle::area, which you will
//  meet when you start splitting code into header files.
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written)
// -----------------------------------------------------------------------------

#include <iostream>
#include <string>

class Rectangle {
public:
    void set_size(double w, double h) {
        width_ = w;
        height_ = h;
    }

    double area() const { return width_ * height_; }

    double perimeter() const { return 2.0 * (width_ + height_); }

    void describe() const {
        std::cout << width_ << " x " << height_ << "  area " << area() << "  perimeter "
                  << perimeter() << '\n';
    }

private:
    double width_ = 0.0;
    double height_ = 0.0;
};

int main() {
    Rectangle a;
    a.set_size(3.0, 4.0);
    a.describe();

    Rectangle b;  // a completely separate object with its own width_ and height_
    b.set_size(10.0, 2.5);
    b.describe();

    // Try uncommenting this line. It will NOT compile:
    //     a.width_ = 100.0;
    // The error says width_ is private -- encapsulation doing its job.

    // -------------------------------------------------------------------------
    //  YOUR TASK 1: add to Rectangle
    // -------------------------------------------------------------------------
    //  Add these member functions to the class above:
    //
    //    a) double width() const   and   double height() const
    //       Plain "getters" that hand back the private values. Read-only, so
    //       they must be const.
    //
    //    b) bool is_square() const
    //       True when width and height are equal.
    //
    //    c) void scale(double factor)
    //       Multiplies both dimensions by factor. NOT const -- it modifies.
    //
    //  Then, down here, make a 5 x 5 rectangle, print is_square(), scale it by
    //  2, and describe() it again.

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: a Counter class
    // -------------------------------------------------------------------------
    //  Write a small class of your own, above main():
    //
    //      class Counter {
    //      public:
    //          void increment();       // add 1
    //          void reset();           // back to 0
    //          int value() const;      // current count
    //      private:
    //          int count_ = 0;
    //      };
    //
    //  Then create one, increment it a few times in a loop, print the value,
    //  reset it, and print again.
    //
    //  Ask yourself: why is count_ private? What could go wrong if outside code
    //  could write  c.count_ = -500;  directly?

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: an array of objects
    // -------------------------------------------------------------------------
    //  A class is a type, so you can make an array of them:
    //
    //      Rectangle shapes[3];
    //
    //  Give each one a different size with a loop, then loop again and print
    //  the total area of all three.

    // TODO

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT
// -----------------------------------------------------------------------------
//    3 x 4  area 12  perimeter 14
//    10 x 2.5  area 25  perimeter 25
//    5 x 5 is_square? 1
//    10 x 10  area 100  perimeter 40
//    counter after 3 increments: 3
//    counter after reset: 0
//    total area of 3 shapes: 12   <- depends on the sizes you picked
