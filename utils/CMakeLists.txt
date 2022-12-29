include(${CMAKE_CURRENT_LIST_DIR}/../cmake/compiler_flags.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../cmake/cpp_standard.cmake)

cmake_minimum_required(VERSION 3.20)

set(_LIBRARY_NAME "aoc_utils")

project(
  ${_LIBRARY_NAME}
  LANGUAGES CXX
  VERSION 1.0.0
  DESCRIPTION "AoC utilities")

add_library(${_LIBRARY_NAME} STATIC)

set_cpp_standard(${_LIBRARY_NAME})
set_compiler_flags(${_LIBRARY_NAME})
set_vectorization_flags(${_LIBRARY_NAME})

target_sources(
  ${_LIBRARY_NAME}
  PRIVATE src/ContainerUtils.cpp src/FileUtils.cpp src/AocUtils.cpp
          src/StringUtils.cpp src/TimeUtils.cpp)

target_include_directories(
  ${_LIBRARY_NAME}
  PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
          $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/utils>
          $<INSTALL_INTERFACE:include/utils> $<INSTALL_INTERFACE:src>
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>)
