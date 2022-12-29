include(${CMAKE_CURRENT_LIST_DIR}/../../../cmake/compiler_flags.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../../../cmake/cpp_standard.cmake)

cmake_minimum_required(VERSION 3.20)

project(
  "aoc_2021_01"
  LANGUAGES CXX
  VERSION 1.0.0
  DESCRIPTION "AoC 2021 Puzzle 01")

add_executable(${PROJECT_NAME} main.cpp solutions.cpp solutions.hpp)

set_cpp_standard(${PROJECT_NAME})
set_compiler_flags(${PROJECT_NAME})
set_vectorization_flags(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE aoc_utils)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
               ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)
