# C++ practice

A self-paced C++ course in [src/](src/), plus the original two-workflow scaffold
for scratch work.

## Quick start

```sh
./run src/01_basics/01_hello_variables.cpp     # compile + run one exercise
```

Start at [src/01_basics/01_hello_variables.cpp](src/01_basics/01_hello_variables.cpp)
and work down the list below. Each file explains its topic at the top, gives you
a task with `TODO` markers, and tells you the output to aim for.

---

## The course

Do them in this order. Each file assumes the ones before it.

### 1. [src/01_basics/](src/01_basics/) — program structure and control flow

`#include`, `main`, variables, primitive types, `std::cout`, `std::cin`,
functions, parameters, return values, `if` / `else if` / `else`.

| File | What you practise |
| --- | --- |
| [01_hello_variables.cpp](src/01_basics/01_hello_variables.cpp) | The shape of a program; declaring and printing variables |
| [02_temperature_converter.cpp](src/01_basics/02_temperature_converter.cpp) | Reading input; the integer-division trap |
| [03_functions_and_conditions.cpp](src/01_basics/03_functions_and_conditions.cpp) | Writing functions; branching; a small calculator |

### 2. [src/02_arrays_strings/](src/02_arrays_strings/) — fixed-size arrays and `std::string`

Indexing, reading and modifying elements, iterating, string length and
manipulation. No `std::vector` or other STL containers yet — those come later.

| File | What you practise |
| --- | --- |
| [01_array_basics.cpp](src/02_arrays_strings/01_array_basics.cpp) | Indexing from zero; modifying in place; finding the largest |
| [02_array_stats.cpp](src/02_arrays_strings/02_array_stats.cpp) | Accumulating; passing arrays to functions; averages and `static_cast` |
| [03_string_basics.cpp](src/02_arrays_strings/03_string_basics.cpp) | `std::string`, length, per-character loops, counting vowels, reversing |

### 3. [src/03_loops/](src/03_loops/) — for, while, do-while

Loop counters, nested loops, and loops driving arrays.

| File | What you practise |
| --- | --- |
| [01_loop_forms.cpp](src/03_loops/01_loop_forms.cpp) | All three loop forms; `%`; ordering `if` branches correctly |
| [02_nested_loops.cpp](src/03_loops/02_nested_loops.cpp) | A loop inside a loop; multiplication table; star triangles |
| [03_loops_and_arrays.cpp](src/03_loops/03_loops_and_arrays.cpp) | Accumulate, search, transform, reverse in place |
| [04_number_guessing.cpp](src/03_loops/04_number_guessing.cpp) | A mini project: `do-while`, random numbers, surviving bad input |

### 4. [src/04_pointers/](src/04_pointers/) — addresses and pointers

The longest section, taught in small steps: addresses, `&`, declaring pointers,
`nullptr`, dereferencing with `*`, modifying through a pointer, and passing
pointers to functions. No pointer arithmetic, `new`/`delete`, or smart pointers
yet.

| File | What you practise |
| --- | --- |
| [01_addresses_and_pointers.cpp](src/04_pointers/01_addresses_and_pointers.cpp) | `x` vs `&x` vs `p` vs `*p`; declaring a pointer; `sizeof` |
| [02_dereferencing.cpp](src/04_pointers/02_dereferencing.cpp) | Reading *and writing* through a pointer; `p = &y` vs `*p = 5` |
| [03_nullptr_safety.cpp](src/04_pointers/03_nullptr_safety.cpp) | Why `*p` on a null pointer is unsafe; guard clauses; null as "not found" |
| [04_pointers_in_functions.cpp](src/04_pointers/04_pointers_in_functions.cpp) | Pass-by-value vs pass-the-address; swap; out parameters |

### 5. [src/05_oop/](src/05_oop/) — classes and objects

`public` / `private`, member variables and functions, constructors,
encapsulation, and basic inheritance. No polymorphism, templates, or design
patterns yet.

| File | What you practise |
| --- | --- |
| [01_class_basics.cpp](src/05_oop/01_class_basics.cpp) | Your first class; why data is private; `const` member functions |
| [02_constructors_bank_account.cpp](src/05_oop/02_constructors_bank_account.cpp) | Constructors, initialiser lists, and rules a class enforces |
| [03_inheritance.cpp](src/05_oop/03_inheritance.cpp) | `Animal` → `Dog` → `Puppy`; `protected`; building the base class |
| [04_design_your_own.cpp](src/05_oop/04_design_your_own.cpp) | **No starter code** — you design the classes yourself |

### 6. [src/06_file_io_exceptions/](src/06_file_io_exceptions/) — files and exceptions

`<fstream>`, `std::ifstream`, `std::ofstream`, checking that a file opened, and
introductory `try` / `catch` / `throw` with `std::exception`.

| File | What you practise |
| --- | --- |
| [01_writing_files.cpp](src/06_file_io_exceptions/01_writing_files.cpp) | Writing files; append vs truncate; always checking the open succeeded |
| [02_reading_files.cpp](src/06_file_io_exceptions/02_reading_files.cpp) | `while (in >> x)` and `getline`; missing files; malformed data |
| [03_exceptions.cpp](src/06_file_io_exceptions/03_exceptions.cpp) | `throw`, `try`, `catch`, the standard exception types, throwing constructors |

These read from [data/](data/), which holds small committed input files. **Run
them from the repository root** so the relative paths resolve. Anything they
write is named `*_out.txt` and is gitignored.

---

## Compiling and running

Three ways, in order of how often you will want them.

**1. The `./run` script (easiest).** Compiles one file with warnings and
sanitizers turned on, then runs it:

```sh
./run src/04_pointers/01_addresses_and_pointers.cpp
./run src/03_loops/04_number_guessing.cpp        # interactive ones work too
```

**2. Plain `g++`.** Exactly what the header comment in each file shows:

```sh
g++ -std=c++23 -Wall -Wextra src/04_pointers/01_addresses_and_pointers.cpp -o ptr_basics
./ptr_basics
```

Adding `-fsanitize=address,undefined -g` is well worth it while learning — it
turns silent memory bugs into a clear report naming the exact line.

**3. CMake.** Each exercise and solution is also a CMake target, so `clangd`
gives you autocomplete and live errors in the editor. They are excluded from the
default build, so `cmake --build build` still just builds the `practice` target:

```sh
cmake --build build --target ex_04_pointers_01_addresses_and_pointers
./build/bin/ex_04_pointers_01_addresses_and_pointers

cmake --build build --target solutions    # check every solution still compiles
```

Target names are `ex_<topic>_<file>` for exercises and `sol_<topic>_<file>` for
solutions. If you add a file and the editor does not notice, reconfigure:

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
```

### A note on warnings

An unfinished exercise may warn about **unused parameters** — the TODO stubs
declare parameters they do not use yet. That is expected, and the warnings
disappear as you fill the functions in. Any *other* warning is worth reading.

---

## Solutions

[solutions/](solutions/) mirrors `src/` exactly and contains a worked version of
every exercise, with comments explaining the decisions rather than just the code.

Nothing in `src/` links to or includes anything in `solutions/`, so you will not
stumble into an answer by accident. Try the exercise first — including getting
it wrong and reading the compiler error. That part is the actual learning.

---

## The original scaffold

Still here and unchanged:

**Multi-file project (CMake):**

```sh
cmake --build build     # rebuild
./build/practice        # run
```

Reconfigure only if you add source files to `CMakeLists.txt`:

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
```

**Scratch work:** drop a file in [scratch/](scratch/) and `./run scratch/foo.cpp`.

### What's turned on

- **C++23** (`std::print`, `std::ranges`, etc.)
- **Warnings:** `-Wall -Wextra -Wpedantic -Wshadow -Wconversion`
- **Sanitizers** (debug builds): AddressSanitizer + UBSan. Out-of-bounds reads,
  use-after-free, and signed overflow abort with a stack trace and line number
  instead of silently corrupting memory. This is the single most useful thing
  when learning C++ — leave it on.

### Editor

VS Code with `clangd` (autocomplete, errors, format-on-save via `.clang-format`)
and `CodeLLDB` (F5 to debug with breakpoints).

`compile_commands.json` is symlinked from `build/` — that's how clangd knows your
flags. If autocomplete goes stale after adding files, rerun the cmake configure
command above.
