cmake_minimum_required(VERSION 3.20)

project("aoc_2021_01" LANGUAGES CXX VERSION 1.0.0 DESCRIPTION "AoC 2021 Puzzle 01 solution.")

# C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compile binary
add_executable(aoc_2021_01)

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)

# setting compiler flags
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -pedantic-errors -Werror -Wconversion)
endif()
