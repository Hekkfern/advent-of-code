# NOTE: This global property should be set as early as possible, ideally
#       before even the project() command is called, since project() performs
#       checking on the compilers to be used.
macro(set_ccache)
    find_program(CCACHE_PROGRAM ccache)
    if(CCACHE_PROGRAM)
        set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    endif()
endmacro()
