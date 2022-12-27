include(${CMAKE_CURRENT_LIST_DIR}/../cmake/compiler_flags.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../cmake/cpp_standard.cmake)

cmake_minimum_required(VERSION 3.20)

add_library(${PROJECT_NAME} STATIC)

set_cpp_standard(${PROJECT_NAME})
set_compiler_flags(${PROJECT_NAME})
set_vectorization_flags(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        src/ContainerUtils.cpp
        src/InputUtils.cpp
        src/AocUtils.cpp
        src/StringUtils.cpp
        src/TimeUtils.cpp
)

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
