# CMakeList.txt : Top-level CMake project file, do global configuration and
# include sub-projects here.

cmake_minimum_required(VERSION 3.20)

project(AdventOfCode)

option(SANITIZE "Enable selected sanitizer in build" OFF)

include(cmake/sanitizer.cmake)
if(SANITIZE)
  enable_sanitizer(${SANITIZE})
endif()

# Include sub-projects.
add_subdirectory(puzzles)
add_subdirectory(utils)
