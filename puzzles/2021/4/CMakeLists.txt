cmake_minimum_required(VERSION 3.20)

add_subdirectory(sources)
if(GENERATE_PROJECTS STREQUAL "ALL" OR GENERATE_PROJECTS STREQUAL "UNITTESTS")
    add_subdirectory(tests)
endif()
