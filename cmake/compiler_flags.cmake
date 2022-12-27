include(CheckCXXCompilerFlag)

macro(set_compiler_flags target_name)
  # setting compiler flags
  target_compile_options(
    ${target_name}
    PRIVATE $<$<CXX_COMPILER_ID:MSVC>:
            /W4
            /WX>
            $<$<CXX_COMPILER_ID:AppleClang>:
            -Wall
            -Werror
            -Wno-error=deprecated-declarations
            -pedantic-errors
            -Wextra
            -Wunreachable-code-break
            -Wextra-semi
            -Wc++98-compat-extra-semi
            -Wunused-exception-parameter
            -Wsuggest-override
            -Wsuggest-destructor-override
            -Winconsistent-missing-destructor-override
            -Wformat-nonliteral
            -Wimplicit-int-conversion
            -Wsign-conversion
            -Wconstant-conversion
            -Wcast-qual
            -Wheader-hygiene
            -Wmissing-noreturn
            -Wundefined-func-template
            -Wunused-template
            -Wreserved-id-macro
            -Wobjc-interface-ivars>
            $<$<CXX_COMPILER_ID:Clang>:
            -Wall
            -Werror
            -Wno-error=deprecated-declarations
            -pedantic-errors
            -Wextra
            -Wreserved-id-macro>
            $<$<CXX_COMPILER_ID:GNU>:
            -Wall
            -Werror
            -Wno-error=deprecated-declarations
            -pedantic-errors
            -Wextra
            -Wconversion
            -Wshadow
            -Weffc++>)
endmacro()

macro(set_vectorization_flags target_name)
  check_cxx_compiler_flag("-march=native" _march_native_works)
  check_cxx_compiler_flag("-xHost" _xhost_works)
  set(_CXX_FLAGS)
  if(_march_native_works)
    message(
      STATUS
        "Using processor's vector instructions (-march=native compiler flag set)"
    )
    set(_CXX_FLAGS "-march=native")
  elseif(_xhost_works)
    message(
      STATUS "Using processor's vector instructions (-xHost compiler flag set)")
    set(_CXX_FLAGS "-xHost")
  else()
    message(STATUS "No suitable compiler flag found for vectorization")
  endif()
  # setting architectural flags
  target_compile_options(${target_name} PRIVATE ${_CXX_FLAGS})
endmacro()
