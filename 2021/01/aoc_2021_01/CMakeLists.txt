cmake_minimum_required(VERSION 3.23)
project(aoc_2021_01)

set(CMAKE_CXX_STANDARD 17)

add_executable(aoc_2021_01 main.cpp)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.csv ${CMAKE_CURRENT_BINARY_DIR}/input.csv COPYONLY)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()