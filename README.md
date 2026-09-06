# C++ practice

## Two workflows

**Single file (for snippets, exercises, algorithm practice):**

```sh
./run scratch/hello.cpp          # compile + run
./run scratch/hello.cpp foo bar  # extra args go to your program
```

**Multi-file project (CMake):**

```sh
cmake --build build     # rebuild
./build/practice        # run
```

Reconfigure only if you add source files to `CMakeLists.txt`:

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
```

## What's turned on

- **C++23** (`std::print`, `std::ranges`, etc.)
- **Warnings:** `-Wall -Wextra -Wpedantic -Wshadow -Wconversion`
- **Sanitizers** (debug builds): AddressSanitizer + UBSan. Out-of-bounds reads,
  use-after-free, and signed overflow abort with a stack trace and line number
  instead of silently corrupting memory. This is the single most useful thing
  when learning C++ — leave it on.

## Editor

VS Code with `clangd` (autocomplete, errors, format-on-save via `.clang-format`)
and `CodeLLDB` (F5 to debug with breakpoints).

`compile_commands.json` is symlinked from `build/` — that's how clangd knows your
flags. If autocomplete goes stale after adding files, rerun the cmake configure
command above.
