include(${CMAKE_SOURCE_DIR}/cmake/aoc_puzzles.cmake)

cmake_minimum_required(VERSION 3.22)

find_package(range-v3 CONFIG REQUIRED)

# aoc_2023_19_solutions
set(_LIB_NAME "aoc_2023_19_solutions")
set(SOURCES_PART1
    part1/Part.cpp
    part1/Part.h
    part1/Rule.cpp
    part1/Rule.h
    part1/Workflow.cpp
    part1/Workflow.h
    part1/System.cpp
    part1/System.h)
set(SOURCES_PART2
    part2/PartRange.cpp
    part2/PartRange.h
    part2/Rule.cpp
    part2/Rule.h
    part2/Workflow.cpp
    part2/Workflow.h
    part2/System.cpp
    part2/System.h)
add_library(${_LIB_NAME} STATIC solutions.cpp solutions.hpp ${SOURCES_PART1}
                                ${SOURCES_PART2})
setup_puzzle(${_LIB_NAME})
target_link_libraries(${_LIB_NAME} PRIVATE aoc_utils)
target_link_libraries(${_LIB_NAME} PRIVATE range-v3)

source_group("part1" FILES ${SOURCES_PART1})
source_group("part2" FILES ${SOURCES_PART2})

# aoc_2023_19
if(GENERATE_PROJECTS STREQUAL "ALL" OR GENERATE_PROJECTS STREQUAL "EXES")
  set(_EXEC_NAME "aoc_2023_19")
  add_executable(${_EXEC_NAME} main.cpp)
  setup_puzzle(${_EXEC_NAME})
  target_link_libraries(${_EXEC_NAME} PRIVATE ${_LIB_NAME})
  target_link_libraries(${_EXEC_NAME} PRIVATE aoc_utils)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
               ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)
