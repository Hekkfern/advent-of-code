#pragma once

#include <concepts>

template <typename T>
concept NumericType
    = requires(T param) {
          requires std::is_integral_v<T> || std::is_floating_point_v<T>;
          requires !std::is_same_v<bool, T>;
          requires std::is_arithmetic_v<decltype(param + 1)>;
          requires !std::is_pointer_v<T>;
      };