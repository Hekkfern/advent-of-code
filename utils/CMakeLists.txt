include(${CMAKE_CURRENT_LIST_DIR}/../cmake/utils.cmake)

cmake_minimum_required(VERSION 3.20)

project("aoc_utils" VERSION 1.0.0 DESCRIPTION "AoC helpful methods to use.")

# C++ standard
set_cpp_standard()

set_ccache()

# Create library
add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/ContainerUtils.cpp
        src/InputUtils.cpp
        src/OutputUtils.cpp
        src/StringUtils.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    DEBUG_POSTFIX "d")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/utils>
        $<INSTALL_INTERFACE:include/utils>
        $<INSTALL_INTERFACE:src>
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# setting compiler flags
set_compiler_flags()
