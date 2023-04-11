#pragma once

#include "Concepts.hpp"
#include <concepts>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace utils::string {

/**
 * @brief
 *
 * @param[in] str
 *
 * @param[in] match
 *
 * @return
 */
[[nodiscard]] bool contains(const std::string& str, const std::string& match);
/**
 * @brief
 *
 * @param[in] s
 *
 * @return
 */
[[nodiscard]] std::string trim(const std::string& s);

template <NumericType T>
[[nodiscard]] T toNumber(const std::string& str)
{
    std::stringstream ss{str};
    T num;
    ss >> num;
    return num;
}

template <>
[[nodiscard]] inline uint8_t toNumber(const std::string& str)
{
    return static_cast<uint8_t>(std::stoi(str));
}

template <>
[[nodiscard]] inline int8_t toNumber(const std::string& str)
{
    return static_cast<int8_t>(std::stoi(str));
}

[[nodiscard]] std::string join(const std::vector<std::string>& strings, std::string delim);

/**
 * @brief a
 *
 * @param[in] input
 *
 * @return
 */
[[nodiscard]] std::string convertFrom(const std::vector<std::vector<char>>& input);

[[nodiscard]] std::vector<std::string>
split(std::string_view str, std::string_view separator = " ");

} // namespace utils::string
