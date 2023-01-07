macro(check_min_compiler_vesion)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 10)
      message(FATAL_ERROR "Insufficient gcc version")
    endif()
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    if(MSVC_VERSION LESS 1930)
      message(FATAL_ERROR "Insufficient msvc version")
    endif()
  elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.2)
      message(FATAL_ERROR "Clang version must be at least 3.2!")
    endif()
  else()
    message(WARNING "Unsupported compiler version!")
  endif()
endmacro()
