cmake_minimum_required(VERSION 3.23)
project(aoc_2021_01)

set(CMAKE_CXX_STANDARD 17)

add_executable(aoc_2021_01 main.cpp)

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Werror -Wpedantic)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.csv ${CMAKE_CURRENT_BINARY_DIR}/input.csv COPYONLY)
