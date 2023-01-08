include(${CMAKE_SOURCE_DIR}/cmake/aoc_puzzles.cmake)

cmake_minimum_required(VERSION 3.20)

# aoc_2022_2_solutions
set(_LIB_NAME "aoc_2022_2_solutions")
add_library(${_LIB_NAME} STATIC solutions.cpp solutions.hpp rps.h rps.cpp)
setup_puzzle(${_LIB_NAME})
target_link_libraries(${_LIB_NAME} PRIVATE aoc_utils)

# aoc_2022_2
set(_EXEC_NAME "aoc_2022_2")
add_executable(${_EXEC_NAME} main.cpp)
setup_puzzle(${_EXEC_NAME})
target_link_libraries(${_EXEC_NAME} PRIVATE ${_LIB_NAME} PRIVATE aoc_utils)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
               ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)