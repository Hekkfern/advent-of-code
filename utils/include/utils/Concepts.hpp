#pragma once

#include <concepts>

template <typename T>
concept NumericType
    = requires(T param) {
          requires std::integral<T> || std::floating_point<T>;
          requires !std::is_same_v<bool, T>;
          requires std::is_arithmetic_v<decltype(param + 1)>;
          requires !std::is_pointer_v<T>;
      };

template <typename T>
concept UnsignedNumericType
    = requires(T param) {
          requires std::unsigned_integral<T>;
          requires !std::is_same_v<bool, T>;
          requires std::is_arithmetic_v<decltype(param + 1)>;
          requires !std::is_pointer_v<T>;
      };
