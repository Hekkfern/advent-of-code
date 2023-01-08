include(${CMAKE_SOURCE_DIR}/cmake/compiler_flags.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/cpp_standard.cmake)

macro(setup_puzzle target_name)
    set_cpp_standard(${target_name})
    set_compiler_flags(${target_name})
    set_vectorization_flags(${target_name})
endmacro()
