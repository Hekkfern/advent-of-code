include(${CMAKE_SOURCE_DIR}/cmake/compiler_flags.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/cpp_standard.cmake)

cmake_minimum_required(VERSION 3.20)

find_package(Catch2 3 CONFIG REQUIRED)

# aoc_2021_01_tests
set(_EXEC_NAME "aoc_2021_01_tests")
add_executable(${_EXEC_NAME} unittests.cpp)
set_cpp_standard(${_EXEC_NAME})
set_compiler_flags(${_EXEC_NAME})
set_vectorization_flags(${_EXEC_NAME})
target_link_libraries(${_EXEC_NAME} PRIVATE aoc_2021_01_solutions PRIVATE Catch2::Catch2WithMain)
