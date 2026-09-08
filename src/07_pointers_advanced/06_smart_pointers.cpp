// =============================================================================
//  07_pointers_advanced / 06_smart_pointers.cpp
//  Lesson: unique_ptr, shared_ptr, and how modern C++ actually writes this
// =============================================================================
//
//  BUILD AND RUN
//    g++ -std=c++23 -Wall -Wextra src/07_pointers_advanced/06_smart_pointers.cpp -o smart_ptr
//    ./smart_ptr
//
//  In file 05 you wrote a class whose destructor freed one heap array. The
//  standard library ships that idea as a template that works for anything, and
//  costs nothing at runtime compared with the raw pointer.
//
// -----------------------------------------------------------------------------
//  LESSON 1: unique_ptr -- one owner, and the type says so
// -----------------------------------------------------------------------------
//        #include <memory>
//
//        std::unique_ptr<Sensor> p = std::make_unique<Sensor>("intake");
//        p->read();                 // -> and * work exactly as on a raw pointer
//        // no delete, ever -- the destructor does it when p goes out of scope
//
//  Arrays get their own spelling:
//
//        std::unique_ptr<int[]> a = std::make_unique<int[]>(n);
//        a[0] = 1;                  // subscripting works; delete[] is automatic
//
//  Prefer make_unique over `unique_ptr<T>(new T(...))`: shorter, and it never
//  leaves a raw `new` result hanging around unowned.
//
// -----------------------------------------------------------------------------
//  LESSON 2: unique means unique -- so you MOVE it
// -----------------------------------------------------------------------------
//        std::unique_ptr<Sensor> b = a;              // ERROR: copy is deleted
//        std::unique_ptr<Sensor> b = std::move(a);   // OK: ownership transfers
//
//        after the move:   a is null, b owns the Sensor
//
//  The compiler refuses the copy because two unique_ptrs to one object would
//  double-delete it -- the exact bug from file 05, now impossible to write by
//  accident. std::move is you saying "yes, I am giving it away", visibly, at the
//  call site.
//
// -----------------------------------------------------------------------------
//  LESSON 3: who owns, who borrows
// -----------------------------------------------------------------------------
//  This is the rule that makes modern C++ APIs readable:
//
//        std::unique_ptr<T>   parameter -> "I take ownership"  (caller moves)
//        std::shared_ptr<T>   parameter -> "I share ownership"
//        T&  or  const T&     parameter -> "I borrow it for this call"
//        T*                   parameter -> "I borrow it, and it may be absent"
//
//  A raw pointer is no longer a lie once ownership lives elsewhere: it just
//  means "non-owning view". Reach for .get() when you need one:
//
//        print_range(squares.get(), squares.get() + n);   // borrowing
//
//  Never call delete on a .get() result, and never hand a .get() result to
//  something that will take ownership of it.
//
// -----------------------------------------------------------------------------
//  LESSON 4: shared_ptr, and weak_ptr
// -----------------------------------------------------------------------------
//  When a lifetime genuinely cannot be pinned to one owner, shared_ptr keeps a
//  reference count and destroys the object when the last owner lets go:
//
//        auto a = std::make_shared<Sensor>("exhaust");   // use_count 1
//        {
//            auto b = a;                                 // use_count 2
//        }                                               // back to 1
//        a.reset();                                      // 0 -> destroyed
//
//  Two warnings. It is not free (an atomic counter per copy), and shared
//  ownership is often shared confusion -- default to unique_ptr and reach for
//  shared_ptr when you can name the second owner. Also, two shared_ptrs that
//  point at each other never reach zero: that cycle is a leak, and the fix is
//  std::weak_ptr, which observes without counting and hands you a shared_ptr
//  only when you .lock() it and the object is still alive.
//
// -----------------------------------------------------------------------------
//  EXAMPLE (already written -- a class that narrates its own lifetime)
// -----------------------------------------------------------------------------

#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Sensor {
public:
    explicit Sensor(std::string name) : name_(std::move(name)) {
        std::cout << "  [ctor] Sensor " << name_ << '\n';
    }
    ~Sensor() { std::cout << "  [dtor] Sensor " << name_ << '\n'; }

    const std::string& name() const { return name_; }
    void read() const { std::cout << "  " << name_ << " reads 21.5C\n"; }

private:
    std::string name_;
};

int main() {
    // -------------------------------------------------------------------------
    //  YOUR TASK 1: the heap array from file 04, without the bookkeeping
    // -------------------------------------------------------------------------
    //  Rewrite task 1 of 04_dynamic_memory using a smart pointer:
    //
    //      const std::size_t size = 6;
    //      std::unique_ptr<int[]> squares = std::make_unique<int[]>(size);
    //
    //  Fill it with squares, then print it with a BORROWING function:
    //
    //      void print_range(const int* begin, const int* end, const char* label)
    //
    //  called as  print_range(squares.get(), squares.get() + size, "squares  :")
    //
    //  squares  : 0 1 4 9 16 25
    //
    //  Use std::size_t for the loop counter -- unique_ptr<int[]>::operator[]
    //  takes an unsigned index, and -Wconversion will tell you off for mixing.
    //  Then count the delete[]s you had to write. That is the entire lesson.

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 2: ownership moving around
    // -------------------------------------------------------------------------
    //  Write above main():
    //
    //      void inspect(const Sensor& sensor)         // borrows: prints name, calls read()
    //      void adopt(std::unique_ptr<Sensor> sensor) // takes ownership by value
    //
    //  Then, inside a nested scope in main:
    //    - make_unique a Sensor called "intake"
    //    - call inspect(*owned) -- borrowing, ownership unchanged
    //    - try  auto copy = owned;  see the error, comment it back out
    //    - move it into a second unique_ptr and print whether `owned` is now
    //      null (a unique_ptr converts to bool, so `owned ? ... : ...` works)
    //    - adopt(std::move(moved)) and watch the Sensor get destroyed INSIDE
    //      adopt, at its closing brace -- not back in main
    //
    //  Watch where the [dtor] line lands relative to the other output. That
    //  position is the whole point: ownership moved, so the destruction moved.

    // TODO

    // -------------------------------------------------------------------------
    //  YOUR TASK 3: watching a reference count
    // -------------------------------------------------------------------------
    //    - make_shared a Sensor called "exhaust", print first.use_count()
    //    - open a scope, copy the shared_ptr into a second one, print the count
    //    - make a std::weak_ptr from it and print the count again -- unchanged,
    //      because a weak_ptr watches without owning
    //    - .lock() the weak_ptr inside an if, print the count while the lock is
    //      alive (it goes up by one, and back down at the end of the if)
    //    - close the scope, print the count, then first.reset()
    //
    //  Predict every number before you run it. The one that surprises people is
    //  the lock: it hands you a real, counted owner for exactly as long as you
    //  hold it.

    // TODO

    return 0;
}

// -----------------------------------------------------------------------------
//  EXPECTED OUTPUT
// -----------------------------------------------------------------------------
//    squares  : 0 1 4 9 16 25
//
//    -- unique_ptr --
//      [ctor] Sensor intake
//    inspecting intake
//      intake reads 21.5C
//    after the move, owned is null
//    adopted intake, destroying it now
//      [dtor] Sensor intake
//    back in main, nothing left to free
//
//    -- shared_ptr --
//      [ctor] Sensor exhaust
//    use_count = 1
//    inside scope, use_count = 2
//      exhaust reads 21.5C
//    with a weak_ptr watching, use_count = 2
//    weak_ptr locked exhaust, use_count = 3
//    back outside, use_count = 1
//      [dtor] Sensor exhaust
//    after reset, the Sensor is gone
//
// -----------------------------------------------------------------------------
//  GOING FURTHER (optional, and the best single exercise in this section)
// -----------------------------------------------------------------------------
//  Rebuild the linked list from 04_dynamic_memory with
//
//      struct Node {
//          int value;
//          std::unique_ptr<Node> next;
//      };
//
//  push_front becomes a move, print_list borrows with a raw Node*, and free_list
//  disappears entirely -- destroying the head destroys the whole chain.
//
//  Then find the catch: that automatic destruction is RECURSIVE, one stack frame
//  per node, so a list of a million nodes overflows the stack. Real code either
//  keeps an explicit unwinding loop in the destructor or does not use a linked
//  list. "The safe tool has a sharp edge too, in a different place" is a very
//  C++ lesson.
