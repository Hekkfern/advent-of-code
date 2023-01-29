include_guard(GLOBAL)

macro(set_cppcheck)
  find_program(CPPCHECK_PROGRAM NAMES cppcheck)
  if(CPPCHECK_PROGRAM)
    message(STATUS "cppcheck found in the system.")
    set(CMAKE_CXX_CPPCHECK ${CPPCHECK_PROGRAM})
    list(
      APPEND
      CMAKE_CXX_CPPCHECK
      "--enable=warning"
      "--inconclusive"
      "--force"
      "--inline-suppr"
      "--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt")
  endif()
endmacro()
