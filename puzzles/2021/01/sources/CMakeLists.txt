include(${CMAKE_SOURCE_DIR}/cmake/compiler_flags.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/cpp_standard.cmake)

cmake_minimum_required(VERSION 3.20)

# aoc_2021_01_solutions
add_library(aoc_2021_01_solutions STATIC solutions.cpp solutions.hpp)
set_cpp_standard(aoc_2021_01_solutions)
set_compiler_flags(aoc_2021_01_solutions)
set_vectorization_flags(aoc_2021_01_solutions)
target_link_libraries(aoc_2021_01_solutions PRIVATE aoc_utils)

# aoc_2021_01
add_executable(${PROJECT_NAME} main.cpp)
set_cpp_standard(${PROJECT_NAME})
set_compiler_flags(${PROJECT_NAME})
set_vectorization_flags(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE aoc_2021_01_solutions PRIVATE aoc_utils)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
               ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)
