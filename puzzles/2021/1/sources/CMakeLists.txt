include(${CMAKE_SOURCE_DIR}/cmake/compiler_flags.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/cpp_standard.cmake)

cmake_minimum_required(VERSION 3.20)

# aoc_2021_01_solutions
set(_LIB_NAME "aoc_2021_1_solutions")
add_library(${_LIB_NAME} STATIC solutions.cpp solutions.hpp)
set_cpp_standard(${_LIB_NAME})
set_compiler_flags(${_LIB_NAME})
set_vectorization_flags(${_LIB_NAME})
target_link_libraries(${_LIB_NAME} PRIVATE aoc_utils)

# aoc_2021_01
set(_EXEC_NAME "aoc_2021_1")
add_executable(${_EXEC_NAME} main.cpp)
set_cpp_standard(${_EXEC_NAME})
set_compiler_flags(${_EXEC_NAME})
set_vectorization_flags(${_EXEC_NAME})
target_link_libraries(${_EXEC_NAME} PRIVATE ${_LIB_NAME} PRIVATE aoc_utils)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
               ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)
