cmake_minimum_required(VERSION 3.20)

if(GENERATE_YEARS STREQUAL "" OR "2021" IN_LIST GENERATE_YEARS)
  add_subdirectory(2021)
endif()
if(GENERATE_YEARS STREQUAL "" OR "2022" IN_LIST GENERATE_YEARS)
  add_subdirectory(2022)
endif()
