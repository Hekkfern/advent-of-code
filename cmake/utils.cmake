macro(set_compiler_flags)
    # setting compiler flags
    if (MSVC)
        # warning level 4 and all warnings as errors
        add_compile_options(/W4 /WX)
    else()
        # lots of warnings and all warnings as errors
        add_compile_options(-Wall -Wextra -pedantic -pedantic-errors -Werror -Wconversion)
    endif()
    target_compile_options(
        ${PROJECT_NAME}
        PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:
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
            -Wconversion>
    )
endmacro()

macro(set_cpp_standard)
    # C++20 standard
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED True)
    set(CMAKE_CXX_EXTENSIONS OFF)
endmacro()

macro(set_ccache)
    find_program(CCACHE_PROGRAM ccache)
    if(CCACHE_PROGRAM)
        set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    endif()
endmacro()
