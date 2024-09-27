include(${CMAKE_SOURCE_DIR}/cmake/aoc_puzzles.cmake)

cmake_minimum_required(VERSION 3.22)

find_package(range-v3 CONFIG REQUIRED)

# aoc_2023_17_solutions
set(_LIB_NAME "aoc_2023_17_solutions")
add_library(${_LIB_NAME} STATIC solutions.cpp solutions.hpp State.cpp State.h
        Node.h)
setup_puzzle(${_LIB_NAME})
target_link_libraries(${_LIB_NAME} PRIVATE aoc_utils)
target_link_libraries(${_LIB_NAME} PRIVATE range-v3)

# aoc_2023_17
if(GENERATE_PROJECTS STREQUAL "ALL" OR GENERATE_PROJECTS STREQUAL "EXES")
  set(_EXEC_NAME "aoc_2023_17")
  add_executable(${_EXEC_NAME} main.cpp)
  setup_puzzle(${_EXEC_NAME})
  target_link_libraries(${_EXEC_NAME} PRIVATE ${_LIB_NAME})
  target_link_libraries(${_EXEC_NAME} PRIVATE aoc_utils)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
               ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)
