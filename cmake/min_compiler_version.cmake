include_guard(GLOBAL)

macro(check_min_compiler_vesion)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 11)
      message(
        FATAL_ERROR
          "Insufficient compiler version. GCC version must be at least 11")
    endif()
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    if(MSVC_VERSION LESS 1930)
      message(
        FATAL_ERROR
          "Insufficient compiler version. MSVC version must be at least 143")
    endif()
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13)
      message(
        FATAL_ERROR
          "Insufficient compiler version. Clang version must be at least 13")
    endif()
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 14)
      message(
        FATAL_ERROR
          "Insufficient compiler version. AppleClang version must be at least 14"
      )
    endif()
  else()
    message(WARNING "Unsupported compiler! Use this project at your own risk")
  endif()
endmacro()
