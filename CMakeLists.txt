# CMakeList.txt : Top-level CMake project file, do global configuration and
# include sub-projects here.

cmake_minimum_required(VERSION 3.22)

set(GENERATE_PROJECTS "ALL" CACHE STRING "Select which kind of projects to generate by CMake.")
set_property(CACHE GENERATE_PROJECTS PROPERTY STRINGS "ALL" "EXES" "UNITTESTS")
# Check that value of the parameter is inside "STRINGS" list.
get_property(GENERATE_PROJECTS_STRINGS CACHE GENERATE_PROJECTS PROPERTY STRINGS)
if (NOT GENERATE_PROJECTS IN_LIST GENERATE_PROJECTS_STRINGS)
  message(FATAL_ERROR "Wrong value of the parameter 'GENERATE_PROJECTS'")
endif()

set(GENERATE_YEARS
        ""
        CACHE
        INTERNAL
        "Generate the projects of the selected years. Or left empty to generate them all."
        )

option(USE_CCACHE "Use ccache in the project if it is available" ON)
if (USE_CCACHE)
    include(${CMAKE_SOURCE_DIR}/cmake/ccache.cmake)
    set_ccache()
endif (USE_CCACHE)

option(USE_CPPCHECK "Use cppcheck in the project if it is available" ON)
if (USE_CPPCHECK)
    include(${CMAKE_SOURCE_DIR}/cmake/cppcheck.cmake)
    set_cppcheck()
endif (USE_CPPCHECK)

project(
        AdventOfCode
        VERSION 1.0.0
        DESCRIPTION "Advent Of Code puzzle solutions in C++ language"
        HOMEPAGE_URL "https://github.com/Hekkfern/advent-of-code"
        LANGUAGES CXX)

include(${CMAKE_SOURCE_DIR}/cmake/min_compiler_version.cmake)
check_min_compiler_vesion()

enable_testing()

include(${CMAKE_SOURCE_DIR}/cmake/top_level_project.cmake)
is_top_level_project()

option(SANITIZE "Enable selected sanitizer in build" OFF)

include(${CMAKE_SOURCE_DIR}/cmake/sanitizer.cmake)
if (SANITIZE)
    enable_sanitizer(${SANITIZE})
endif ()

# Include sub-projects.
add_subdirectory(puzzles)
add_subdirectory(utils)
