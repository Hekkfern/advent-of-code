cmake_minimum_required(VERSION 3.20)

add_subdirectory(sources)
if(GENERATE_UNIT_TESTS)
    add_subdirectory(tests)
endif(GENERATE_UNIT_TESTS)
