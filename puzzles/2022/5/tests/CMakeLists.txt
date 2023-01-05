include(${CMAKE_SOURCE_DIR}/cmake/compiler_flags.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/cpp_standard.cmake)

cmake_minimum_required(VERSION 3.20)

find_package(Catch2 3 CONFIG REQUIRED)

# aoc_2022_5_tests
set(_EXEC_NAME "aoc_2022_5_tests")
add_executable(${_EXEC_NAME} unittests.cpp)
set_cpp_standard(${_EXEC_NAME})
set_compiler_flags(${_EXEC_NAME})
set_vectorization_flags(${_EXEC_NAME})
target_link_libraries(${_EXEC_NAME} PRIVATE aoc_2022_5_solutions PRIVATE aoc_utils PRIVATE Catch2::Catch2WithMain)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../sources/input.txt
        ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_test.txt
        ${CMAKE_CURRENT_BINARY_DIR}/input_test.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/solution1_test.txt
        ${CMAKE_CURRENT_BINARY_DIR}/solution1_test.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/solution1.txt
        ${CMAKE_CURRENT_BINARY_DIR}/solution1.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/solution2_test.txt
        ${CMAKE_CURRENT_BINARY_DIR}/solution2_test.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/solution2.txt
        ${CMAKE_CURRENT_BINARY_DIR}/solution2.txt COPYONLY)