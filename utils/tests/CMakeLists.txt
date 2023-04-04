include(${CMAKE_SOURCE_DIR}/cmake/compiler_flags.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/cpp_standard.cmake)

cmake_minimum_required(VERSION 3.20)

find_package(Catch2 3 CONFIG REQUIRED)

# aoc_utils_tests
set(_EXEC_NAME "aoc_utils_tests")
set(_TESTFILES
        IntervalTests.cpp
        MultiIntervalTests.cpp
        StringTests.cpp)
set(_TESTFILES_GEOMETRY2D
        geometry2d/BoundingBox2DTests.cpp
        geometry2d/Direction2DTests.cpp
        geometry2d/Point2DTests.cpp
        geometry2d/Rectangle2DTests.cpp
        geometry2d/SquareDiamond2DTests.cpp
        geometry2d/Vector2DTests.cpp)
set(_TESTFILES_GRAPH
        graph/GraphTests.cpp
        graph/VertexTests.cpp)
add_executable(
        ${_EXEC_NAME}
        ${_TESTFILES} ${_TESTFILES_GEOMETRY2D} ${_TESTFILES_GRAPH})
set_cpp_standard(${_EXEC_NAME})
set_compiler_flags(${_EXEC_NAME})
set_vectorization_flags(${_EXEC_NAME})
include(CTest)
include(Catch)
catch_discover_tests(${_EXEC_NAME})
target_link_libraries(${_EXEC_NAME} PRIVATE aoc_utils)
target_link_libraries(${_EXEC_NAME} PRIVATE Catch2::Catch2WithMain)
