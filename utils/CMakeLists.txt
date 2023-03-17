include(${CMAKE_SOURCE_DIR}/cmake/compiler_flags.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/cpp_standard.cmake)

cmake_minimum_required(VERSION 3.20)

find_package(range-v3 CONFIG REQUIRED)

# aoc_utils
set(_LIB_NAME "aoc_utils")
set(_SOURCES_UTILS
  src/File.cpp
  include/utils/File.hpp
  src/AoC.cpp
  include/utils/AoC.hpp
  src/String.cpp
  include/utils/String.hpp
  src/Time.cpp
  include/utils/Time.hpp
  src/Interval.cpp
  include/utils/Interval.hpp
  src/MultiInterval.cpp
  include/utils/MultiInterval.hpp
)
set(
  _SOURCES_UTILS_GEOMETRY2D
  include/utils/geometry2d/Direction2D.hpp
  src/geometry2d/Point2D.cpp
  include/utils/geometry2d/Point2D.hpp
  src/geometry2d/Vector2D.cpp
  include/utils/geometry2d/Vector2D.hpp
  src/geometry2d/Rectangle2D.cpp
  include/utils/geometry2d/Rectangle2D.hpp
  src/geometry2d/BoundingBox2D.cpp
  include/utils/geometry2d/BoundingBox2D.hpp
)
add_library(
  ${_LIB_NAME} STATIC
  ${_SOURCES_UTILS}
  ${_SOURCES_UTILS_GEOMETRY2D}
)
set_cpp_standard(${_LIB_NAME})
set_compiler_flags(${_LIB_NAME})
set_vectorization_flags(${_LIB_NAME})
target_include_directories(
  ${_LIB_NAME}
  PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
          $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/utils>
          $<INSTALL_INTERFACE:include/utils> $<INSTALL_INTERFACE:src>
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>)
target_link_libraries(${_LIB_NAME} PRIVATE range-v3)

source_group("Source Files" FILES ${_SOURCES_UTILS})
source_group("Source Files/geometry2d" FILES ${_SOURCES_UTILS_GEOMETRY2D})

if(GENERATE_PROJECTS STREQUAL "ALL" OR GENERATE_PROJECTS STREQUAL "UNITTESTS")
  add_subdirectory(tests)
endif()
