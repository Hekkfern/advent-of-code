cmake_minimum_required(VERSION 3.20)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/EmptyFile.txt
               ${CMAKE_CURRENT_BINARY_DIR}/EmptyFile.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/FileWithTextLines.txt
               ${CMAKE_CURRENT_BINARY_DIR}/FileWithTextLines.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/FileWithNumberLines.txt
               ${CMAKE_CURRENT_BINARY_DIR}/FileWithNumberLines.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/FileWithGroupedNumbers.txt
               ${CMAKE_CURRENT_BINARY_DIR}/FileWithGroupedNumbers.txt COPYONLY)
