cmake_minimum_required(VERSION 3.20)
project(practice CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Emit compile_commands.json so clangd gives you autocomplete + errors in the editor.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(practice src/main.cpp)

target_compile_options(practice PRIVATE
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion
)

# Debug builds get address + UB sanitizers: catches out-of-bounds, use-after-free,
# signed overflow, etc. at runtime instead of silently corrupting memory.
target_compile_options(practice PRIVATE
    $<$<CONFIG:Debug>:-g -O0 -fsanitize=address,undefined -fno-omit-frame-pointer>
)
target_link_options(practice PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address,undefined>
)
