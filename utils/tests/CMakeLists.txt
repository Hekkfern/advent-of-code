include(${CMAKE_SOURCE_DIR}/cmake/compiler_flags.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/cpp_standard.cmake)

cmake_minimum_required(VERSION 3.20)

find_package(Catch2 3 CONFIG REQUIRED)

# aoc_utils_tests
set(_EXEC_NAME "aoc_utils_tests")
set(_TESTFILES StringTests.cpp MathTests.cpp FileTests.cpp
               DynamicProgrammingTests.cpp
               CombinationsTests.cpp)
set(_TESTFILES_INTERVAL interval/IntervalTests.cpp
                        interval/IntervalSetTests.cpp)
set(_TESTFILES_GEOMETRY2D
    geometry2d/Coord2DTests.cpp
    geometry2d/BoundingBox2DTests.cpp
    geometry2d/Direction2DTests.cpp
    geometry2d/Point2DTests.cpp
    geometry2d/Rectangle2DTests.cpp
    geometry2d/SquareDiamond2DTests.cpp
    geometry2d/Vector2DTests.cpp
    geometry2d/Operations2DTests.cpp
    geometry2d/Line2DTests.cpp)
set(_TESTFILES_GEOMETRY3D
    geometry3d/Point3DTests.cpp geometry3d/Vector3DTests.cpp
    geometry3d/Operations3DTests.cpp)
set(_TESTFILES_GRAPH graph/GraphTests.cpp graph/VertexTests.cpp
                     graph/AlgorithmsTests.cpp)
add_executable(
  ${_EXEC_NAME} ${_TESTFILES} ${_TESTFILES_INTERVAL} ${_TESTFILES_GEOMETRY2D}
                ${_TESTFILES_GEOMETRY3D} ${_TESTFILES_GRAPH})
set_cpp_standard(${_EXEC_NAME})
set_compiler_flags(${_EXEC_NAME})
set_vectorization_flags(${_EXEC_NAME})
include(CTest)
include(Catch)
catch_discover_tests(${_EXEC_NAME})
target_link_libraries(${_EXEC_NAME} PRIVATE aoc_utils)
target_link_libraries(${_EXEC_NAME} PRIVATE Catch2::Catch2WithMain)

source_group("Source Files" FILES ${_TESTFILES})
source_group("Source Files/interval" FILES ${_TESTFILES_INTERVAL})
source_group("Source Files/geometry2d" FILES ${_TESTFILES_GEOMETRY2D})
source_group("Source Files/geometry3d" FILES ${_TESTFILES_GEOMETRY3D})
source_group("Source Files/graph" FILES ${_TESTFILES_GRAPH})

add_subdirectory(test_assets)
