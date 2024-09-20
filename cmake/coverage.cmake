include_guard(GLOBAL)

macro(set_coverage target_name)
    if (NOT (CMAKE_BUILD_TYPE STREQUAL "Debug"))
        message(
                WARNING
                "Code coverage results with an optimised (non-Debug) build may be misleading"
        )
    elseif (NOT (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang"))
        message(
                FATAL_ERROR
                "Code coverage is only support for GCC, Clang, and AppleClang compilers"
        )
    else ()
        # Enable coverage options if supported
        target_compile_options(${target_name} PRIVATE --coverage)
        target_link_libraries(${target_name} PRIVATE --coverage)
        # Custom target for running coverage
        find_program(LCOV_PATH lcov)
        find_program(GENHTML_PATH genhtml)
        if (LCOV_PATH AND GENHTML_PATH)
            add_custom_target(
                    "${target_name}_coverage"
                    COMMAND ${LCOV_PATH} --directory . --zerocounters
                    COMMAND ${LCOV_PATH} --directory . --capture --output-file coverage.info --rc branch_coverage=1
                    COMMAND ${LCOV_PATH} --remove coverage.info '/usr/*' '*/test/*' '*/vcpkg_installed/*'
                    --output-file coverage.info
                    COMMAND ${GENHTML_PATH} coverage.info --output-directory coverage_report
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                    COMMENT "Generating coverage report"
                    VERBATIM)
        else ()
            message(
                    WARNING
                    "lcov and genhtml not found! Install them to enable coverage reporting."
            )
        endif ()
    endif ()
endmacro()
