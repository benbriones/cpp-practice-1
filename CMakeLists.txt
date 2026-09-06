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

# -----------------------------------------------------------------------------
# Practice exercises (src/01_basics/... and solutions/...)
#
# Every exercise file is a standalone program with its own main(), so each one
# gets its own target. They are EXCLUDE_FROM_ALL, which means:
#
#   cmake --build build                     still builds only `practice`
#   cmake --build build --target ex_04_pointers_01_addresses_and_pointers
#                                           builds one exercise
#
# They still land in compile_commands.json, so clangd gives you autocomplete and
# live errors while you edit them. Most of the time you will not need CMake at
# all here -- ./run src/04_pointers/01_addresses_and_pointers.cpp is quicker.
# -----------------------------------------------------------------------------

function(add_practice_target prefix source)
    # src/04_pointers/01_addresses_and_pointers.cpp -> ex_04_pointers_01_addresses_and_pointers
    file(RELATIVE_PATH rel "${CMAKE_CURRENT_SOURCE_DIR}" "${source}")
    get_filename_component(dir "${rel}" DIRECTORY)
    get_filename_component(stem "${rel}" NAME_WE)
    get_filename_component(topic "${dir}" NAME)
    set(target "${prefix}_${topic}_${stem}")

    add_executable(${target} EXCLUDE_FROM_ALL "${source}")
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    target_compile_options(${target} PRIVATE
        -Wall -Wextra -Wpedantic -Wshadow -Wconversion
        $<$<CONFIG:Debug>:-g -O0 -fsanitize=address,undefined -fno-omit-frame-pointer>
    )
    target_link_options(${target} PRIVATE
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>
    )
endfunction()

file(GLOB_RECURSE practice_exercises CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/0*/*.cpp")
foreach(source ${practice_exercises})
    add_practice_target(ex "${source}")
endforeach()

file(GLOB_RECURSE practice_solutions CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/solutions/0*/*.cpp")
foreach(source ${practice_solutions})
    add_practice_target(sol "${source}")
endforeach()

# Convenience: build every solution at once to check they all still compile.
add_custom_target(solutions)
foreach(source ${practice_solutions})
    file(RELATIVE_PATH rel "${CMAKE_CURRENT_SOURCE_DIR}" "${source}")
    get_filename_component(dir "${rel}" DIRECTORY)
    get_filename_component(stem "${rel}" NAME_WE)
    get_filename_component(topic "${dir}" NAME)
    add_dependencies(solutions "sol_${topic}_${stem}")
endforeach()
