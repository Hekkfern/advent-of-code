include(../../../cmake/compiler_flags.cmake)
include(../../../cmake/cpp_standard.cmake)

cmake_minimum_required(VERSION 3.20)

project("aoc_2022_02" LANGUAGES CXX VERSION 1.0.0 DESCRIPTION "AoC 2022 Puzzle 02")

add_executable(aoc_2022_02 main.cpp)

set_cpp_standard(aoc_2022_02)
set_compiler_flags(aoc_2022_02)
set_vectorization_flags(aoc_2022_02)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)
