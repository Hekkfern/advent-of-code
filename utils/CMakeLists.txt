include(${CMAKE_CURRENT_LIST_DIR}/../cmake/compiler_flags.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../cmake/cpp_standard.cmake)

cmake_minimum_required(VERSION 3.20)

project(
  "aoc_utils"
  LANGUAGES CXX
  VERSION 1.0.0
  DESCRIPTION "AoC utilities")

add_library(aoc_utils STATIC)

set_cpp_standard(aoc_utils)
set_compiler_flags(aoc_utils)
set_vectorization_flags(aoc_utils)

target_sources(aoc_utils
    PRIVATE
        src/ContainerUtils.cpp
        src/FileUtils.cpp
        src/AocUtils.cpp
        src/StringUtils.cpp
        src/TimeUtils.cpp
)

target_include_directories(aoc_utils
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/utils>
        $<INSTALL_INTERFACE:include/utils>
        $<INSTALL_INTERFACE:src>
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
