include(${CMAKE_SOURCE_DIR}/cmake/aoc_puzzles.cmake)

cmake_minimum_required(VERSION 3.20)

find_package(range-v3 CONFIG REQUIRED)

# aoc_2022_7_solutions
set(_LIB_NAME "aoc_2022_7_solutions")
add_library(
  ${_LIB_NAME} STATIC
  solutions.cpp
  solutions.hpp
  IDirectory.h
  IFile.h
  Directory.cpp
  Directory.h
  File.cpp
  File.h
  DirectoryTree.cpp
  DirectoryTree.h)
setup_puzzle(${_LIB_NAME})
target_link_libraries(${_LIB_NAME} PRIVATE aoc_utils)
target_link_libraries(${_LIB_NAME} PRIVATE range-v3)

# aoc_2022_7
if(GENERATE_PROJECTS STREQUAL "ALL" OR GENERATE_PROJECTS STREQUAL "EXES")
  set(_EXEC_NAME "aoc_2022_7")
  add_executable(${_EXEC_NAME} main.cpp)
  setup_puzzle(${_EXEC_NAME})
  target_link_libraries(${_EXEC_NAME} PRIVATE ${_LIB_NAME})
  target_link_libraries(${_EXEC_NAME} PRIVATE aoc_utils)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
               ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)
