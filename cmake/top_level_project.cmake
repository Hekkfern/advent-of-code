include_guard(GLOBAL)

macro(is_top_level_project)
  if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds are not supported.")
  endif()
endmacro()
