include_guard(GLOBAL)

macro(set_cppcheck)
  find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
  if(CMAKE_CXX_CPPCHECK)
    message(STATUS "cppcheck found in the system.")
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
