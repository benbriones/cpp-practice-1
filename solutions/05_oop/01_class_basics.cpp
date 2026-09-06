// Solution to src/05_oop/01_class_basics.cpp
// Lesson: classes, objects, public vs private, member variables and functions

#include <iostream>

class Rectangle {
public:
    void set_size(double w, double h) {
        width_ = w;
        height_ = h;
    }

    // Task 1a: getters. Read-only, so const.
    double width() const { return width_; }
    double height() const { return height_; }

    double area() const { return width_ * height_; }
    double perimeter() const { return 2.0 * (width_ + height_); }

    // Task 1b
    bool is_square() const { return width_ == height_; }

    // Task 1c: NOT const -- it modifies the object.
    void scale(double factor) {
        width_ *= factor;
        height_ *= factor;
    }

    void describe() const {
        std::cout << width_ << " x " << height_ << "  area " << area() << "  perimeter "
                  << perimeter() << '\n';
    }

private:
    double width_ = 0.0;
    double height_ = 0.0;
};

// Task 2. count_ is private so nothing outside can put the counter into a state
// increment()/reset() could never produce -- no negative counts, no surprise
// jumps. The class controls its own data, which is the whole idea.
class Counter {
public:
    void increment() { ++count_; }
    void reset() { count_ = 0; }
    int value() const { return count_; }

private:
    int count_ = 0;
};

int main() {
    Rectangle a;
    a.set_size(3.0, 4.0);
    a.describe();

    Rectangle b;
    b.set_size(10.0, 2.5);
    b.describe();

    // Task 1
    Rectangle square;
    square.set_size(5.0, 5.0);
    std::cout << square.width() << " x " << square.height() << " is_square? " << square.is_square()
              << '\n';
    square.scale(2.0);
    square.describe();

    // Task 2
    Counter c;
    for (int i = 0; i < 3; ++i) {
        c.increment();
    }
    std::cout << "counter after 3 increments: " << c.value() << '\n';
    c.reset();
    std::cout << "counter after reset: " << c.value() << '\n';

    // Task 3: a class is a type, so arrays of them work like any other array.
    constexpr int kCount = 3;
    Rectangle shapes[kCount];
    for (int i = 0; i < kCount; ++i) {
        shapes[i].set_size(i + 1.0, 2.0);  // 1x2, 2x2, 3x2
    }

    double total = 0.0;
    for (int i = 0; i < kCount; ++i) {
        total += shapes[i].area();
    }
    std::cout << "total area of 3 shapes: " << total << '\n';

    return 0;
}
