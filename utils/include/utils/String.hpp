#pragma once

#include "Concepts.hpp"
#include <concepts>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace utils::string {

/**
 * @brief      Checks if the selected string contains the provided substring.
 *
 * @param[in]  str    The string where to look for.
 * @param[in]  match  The substring to find.
 *
 * @return     True if the substring was found. False, otherwise.
 */
[[nodiscard]] bool contains(const std::string& str, const std::string& match);
/**
 * @brief      Removes all the spaces and tabs from both sides of a string.
 *
 * @param[in]  s     The string to modify.
 *
 * @return     String without spaces or tabs.
 */
[[nodiscard]] std::string trim(const std::string& s);
/**
 * @brief      Converts a string to a number.
 *
 * @param[in]  str   The string to convert to.
 *
 * @tparam     T     Type of the resulting number.
 *
 * @return     Converted number.
 */
template <NumericType T>
[[nodiscard]] T toNumber(const std::string& str)
{
    std::stringstream ss{str};
    T num;
    ss >> num;
    return num;
}
/**
 * @brief      Converts a string to a number.
 *
 * @param[in]  str   The string to convert to.
 *
 * @return     Converted number.
 */
template <>
[[nodiscard]] inline uint8_t toNumber(const std::string& str)
{
    return static_cast<uint8_t>(std::stoi(str));
}
/**
 * @brief      Converts a string to a number.
 *
 * @param[in]  str   The string to convert to.
 *
 * @return     Converted number.
 */
template <>
[[nodiscard]] inline int8_t toNumber(const std::string& str)
{
    return static_cast<int8_t>(std::stoi(str));
}
/**
 * @brief      Joins a list of strings and puts a delimiting string between
 *             them.
 *
 * @param[in]  strings  The list of strings to join.
 * @param[in]  delim    The delimiter.
 *
 * @return     Resulting string.
 */
[[nodiscard]] std::string join(const std::vector<std::string>& strings, std::string delim);
/**
 * @brief      ?????
 *
 * @param[in]  input  The input
 *
 * @return     ????
 */
[[nodiscard]] std::string convertFrom(const std::vector<std::vector<char>>& input);
/**
 * @brief      Splits a string into multiple strings, based on the provided
 *             string as separator.
 *
 * @param[in]  str        The string to split.
 * @param[in]  separator  The separator.
 *
 * @return     Resulting list of strings.
 */
[[nodiscard]] std::vector<std::string>
split(std::string_view str, std::string_view separator = " ");

} // namespace utils::string
