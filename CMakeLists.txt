# CMakeList.txt : Top-level CMake project file, do global configuration and
# include sub-projects here.

cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE
    "${CMAKE_CURRENT_SOURCE_DIR}/extern/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

option(GENERATE_UNIT_TESTS
       "Generate the unit tests executables of every puzzle." ON)
set(GENERATE_YEARS
    ""
    CACHE
      INTERNAL
      "Generate the projects of the selected years. Or left empty to generate them all."
)

project(
  AdventOfCode
  VERSION 1.0.0
  DESCRIPTION "Advent Of Code puzzle solutions in C++ language"
  LANGUAGES CXX)

option(SANITIZE "Enable selected sanitizer in build" OFF)

include(cmake/sanitizer.cmake)
if(SANITIZE)
  enable_sanitizer(${SANITIZE})
endif()

# Include sub-projects.
add_subdirectory(puzzles)
add_subdirectory(utils)
