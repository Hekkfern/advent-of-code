macro(set_cpp_standard target_name)
  # C++20 standard
  set_target_properties(
    ${target_name}
    PROPERTIES CXX_STANDARD 20
               CXX_STANDARD_REQUIRED ON
               CXX_EXTENSIONS OFF)
endmacro()
