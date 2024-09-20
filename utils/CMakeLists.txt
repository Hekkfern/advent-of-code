include(${CMAKE_SOURCE_DIR}/cmake/compiler_flags.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/cpp_standard.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/coverage.cmake)

cmake_minimum_required(VERSION 3.22)

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
    include/utils/Concepts.hpp
    include/utils/Math.hpp
    include/utils/Combinations.hpp
    src/DynamicProgramming.cpp
    include/utils/DynamicProgramming.hpp
    include/utils/Hash.hpp)
set(_SOURCES_UTILS_ALGORITHMS include/utils/algorithms/ClampedCountIf.hpp
                              include/utils/algorithms/SteppedIota.hpp)
set(_SOURCES_UTILS_INTERVAL include/utils/interval/Interval.hpp
                            include/utils/interval/IntervalSet.hpp)
set(_SOURCES_UTILS_CACHE
    include/utils/cache/Memoization.hpp include/utils/cache/LRUCache.hpp
    include/utils/cache/LoopCache.hpp include/utils/cache/InfiniteCache.hpp)
set(_SOURCES_UTILS_GEOMETRY2D
    include/utils/geometry2d/Direction2D.hpp
    include/utils/geometry2d/Point2D.hpp
    include/utils/geometry2d/Vector2D.hpp
    include/utils/geometry2d/Rectangle2D.hpp
    include/utils/geometry2d/BoundingBox2D.hpp
    include/utils/geometry2d/SquareDiamond2D.hpp
    include/utils/geometry2d/IShape2D.hpp
    include/utils/geometry2d/Operations2D.hpp
    include/utils/geometry2d/Coordinate2D.hpp
    include/utils/geometry2d/Grid2D.hpp
    include/utils/geometry2d/PositionStatus.h)
set(_SOURCES_UTILS_GEOMETRY3D
    include/utils/geometry3d/Point3D.hpp include/utils/geometry3d/Vector3D.hpp
    include/utils/geometry3d/Coord3D.hpp
    include/utils/geometry3d/Operations3D.hpp)
set(_SOURCES_UTILS_GRAPH
    include/utils/graph/Graph.hpp include/utils/graph/Vertex.hpp
    include/utils/graph/Algorithms.hpp)
set(_SOURCES_UTILS_EXTENSIONS include/utils/extensions/ContainerExtensions.hpp)
add_library(
  ${_LIB_NAME} STATIC
  ${_SOURCES_UTILS}
  ${_SOURCES_UTILS_ALGORITHMS}
  ${_SOURCES_UTILS_INTERVAL}
  ${_SOURCES_UTILS_CACHE}
  ${_SOURCES_UTILS_GEOMETRY2D}
  ${_SOURCES_UTILS_GEOMETRY3D}
  ${_SOURCES_UTILS_GRAPH}
  ${_SOURCES_UTILS_EXTENSIONS})
set_cpp_standard(${_LIB_NAME})
set_compiler_flags(${_LIB_NAME})
set_vectorization_flags(${_LIB_NAME})
if (ENABLE_COVERAGE)
  set_coverage(${_LIB_NAME})
endif (ENABLE_COVERAGE)
target_include_directories(
  ${_LIB_NAME}
  PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
          $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/utils>
          $<INSTALL_INTERFACE:include/utils> $<INSTALL_INTERFACE:src>
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>)
target_link_libraries(${_LIB_NAME} PRIVATE range-v3)

source_group("Source Files" FILES ${_SOURCES_UTILS})
source_group("Source Files/algorithms" FILES ${_SOURCES_UTILS_ALGORITHMS})
source_group("Source Files/cache" FILES ${_SOURCES_UTILS_CACHE})
source_group("Source Files/interval" FILES ${_SOURCES_UTILS_INTERVAL})
source_group("Source Files/geometry2d" FILES ${_SOURCES_UTILS_GEOMETRY2D})
source_group("Source Files/geometry3d" FILES ${_SOURCES_UTILS_GEOMETRY3D})
source_group("Source Files/graph" FILES ${_SOURCES_UTILS_GRAPH})
source_group("Source Files/extensions" FILES ${_SOURCES_UTILS_EXTENSIONS})

if(GENERATE_PROJECTS STREQUAL "ALL" OR GENERATE_PROJECTS STREQUAL "UNITTESTS")
  add_subdirectory(tests)
endif()
