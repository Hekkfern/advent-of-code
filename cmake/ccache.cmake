# NOTE: This global property should be set as early as possible, ideally before
# even the project() command is called, since project() performs checking on the
# compilers to be used.
macro(set_ccache)
  find_program(CCACHE_PROGRAM ccache)
  if(CCACHE_PROGRAM)
    message(STATUS "ccache found in the system.")
    # configure ccache
    set(ccacheEnv CCACHE_BASEDIR=${CMAKE_BINARY_DIR})
    # set ccache
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CMAKE_COMMAND} -E env ${ccacheEnv}
                                    ${CCACHE_PROGRAM})
  endif()
endmacro()
