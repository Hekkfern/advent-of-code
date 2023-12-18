cmake_minimum_required(VERSION 3.20)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/File1.txt
               ${CMAKE_CURRENT_BINARY_DIR}/File1.txt COPYONLY)
