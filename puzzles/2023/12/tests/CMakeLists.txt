include(${CMAKE_SOURCE_DIR}/cmake/aoc_puzzles.cmake)

cmake_minimum_required(VERSION 3.22)

find_package(Catch2 3 CONFIG REQUIRED)

# aoc_2023_12_tests
set(_EXEC_NAME "aoc_2023_12_tests")
add_executable(${_EXEC_NAME} unittests.cpp)
setup_test(${_EXEC_NAME})
target_link_libraries(
  ${_EXEC_NAME}
  PRIVATE aoc_2023_12_solutions
  PRIVATE aoc_utils
  PRIVATE Catch2::Catch2WithMain)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../sources/input.txt
               ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input1_test.txt
               ${CMAKE_CURRENT_BINARY_DIR}/input1_test.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/solution1_test.txt
               ${CMAKE_CURRENT_BINARY_DIR}/solution1_test.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/solution1.txt
               ${CMAKE_CURRENT_BINARY_DIR}/solution1.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input2_test.txt
               ${CMAKE_CURRENT_BINARY_DIR}/input2_test.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/solution2_test.txt
               ${CMAKE_CURRENT_BINARY_DIR}/solution2_test.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/solution2.txt
               ${CMAKE_CURRENT_BINARY_DIR}/solution2.txt COPYONLY)
