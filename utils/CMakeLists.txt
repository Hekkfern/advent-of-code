include(${CMAKE_SOURCE_DIR}/cmake/compiler_flags.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/cpp_standard.cmake)

cmake_minimum_required(VERSION 3.20)

find_package(range-v3 CONFIG REQUIRED)

# aoc_utils
set(_LIB_NAME "aoc_utils")
add_library(${_LIB_NAME} STATIC)
set_cpp_standard(${_LIB_NAME})
set_compiler_flags(${_LIB_NAME})
set_vectorization_flags(${_LIB_NAME})
target_sources(
        ${_LIB_NAME}
        PRIVATE
        src/File.cpp
        src/AoC.cpp
        src/String.cpp
        src/Time.cpp
        src/geometry2d/Position2D.cpp
        src/geometry2d/Vector2D.cpp)
target_include_directories(
        ${_LIB_NAME}
        PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/utils>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/utils/geometry2d>
        $<INSTALL_INTERFACE:include/utils> $<INSTALL_INTERFACE:src>
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
target_link_libraries(${_LIB_NAME} PRIVATE range-v3)

if(GENERATE_PROJECTS STREQUAL "ALL" OR GENERATE_PROJECTS STREQUAL "UNITTESTS")
  add_subdirectory(tests)
endif()
