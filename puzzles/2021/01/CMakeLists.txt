include(${CMAKE_CURRENT_LIST_DIR}/../../../cmake/compiler_flags.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../../../cmake/cpp_standard.cmake)

cmake_minimum_required(VERSION 3.20)

project(
  "aoc_2021_01"
  LANGUAGES CXX
  VERSION 1.0.0
  DESCRIPTION "AoC 2021 Puzzle 01")

add_executable(aoc_2021_01 main.cpp solutions.cpp)

set_cpp_standard(aoc_2021_01)
set_compiler_flags(aoc_2021_01)
set_vectorization_flags(aoc_2021_01)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
               ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)
