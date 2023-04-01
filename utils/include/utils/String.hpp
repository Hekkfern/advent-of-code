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
bool contains(const std::string& str, const std::string& match);
/**
 * @brief
 *
 * @param[in] s
 *
 * @return
 */
std::string trim(const std::string& s);

template <NumericType T>
T toNumber(const std::string& str)
{
    std::stringstream ss{str};
    T num;
    ss >> num;
    return num;
}

template <>
inline uint8_t toNumber(const std::string& str)
{
    return static_cast<uint8_t>(std::stoi(str));
}

template <>
inline int8_t toNumber(const std::string& str)
{
    return static_cast<int8_t>(std::stoi(str));
}

std::string join(const std::vector<std::string>& strings, std::string delim);

/**
 * @brief a
 *
 * @param[in] input
 *
 * @return
 */
std::string convertFrom(const std::vector<std::vector<char>>& input);

std::vector<std::string>
split(std::string_view str, std::string_view separator = " ");

} // namespace utils::string
