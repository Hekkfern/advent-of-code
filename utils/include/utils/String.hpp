#pragma once

#include "Concepts.hpp"
#include <charconv>
#include <concepts>
#include <optional>
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
[[nodiscard]] bool contains(std::string_view str, std::string_view match);
/**
 * \brief 
 * \param s 
 * \return 
 */
[[nodiscard]] std::string ltrim(std::string_view s);
/**
 * \brief 
 * \param s 
 * \return 
 */
[[nodiscard]] std::string rtrim(std::string_view s);
/**
 * @brief      Removes all the spaces and tabs from both sides of a string.
 *
 * @param[in]  s     The string to modify.
 *
 * @return     String without spaces or tabs.
 */
[[nodiscard]] std::string trim(std::string_view s);
/**
 * @brief      Converts a string to a number.
 *
 * @param[in]  sv   The string to convert to.
 *
 * @tparam     T     Type of the resulting number.
 *
 * @return     Converted number.
 */
template <NumericType T>
[[nodiscard]] std::optional<T> toNumber(std::string_view sv)
{
    T value;
    auto [ptr, ec]{std::from_chars(sv.data(), sv.data() + sv.size(), value)};
    if (ec != std::errc{}) {
        return {};
    }
    return value;
}
/**
 * @brief      Joins a list of strings and puts a delimiting string between
 *             them.
 *
 * @param[in]  strings  The list of strings to join.
 * @param[in]  delimiter    The delimiter.
 *
 * @return     Resulting string.
 */
[[nodiscard]] std::string
join(std::vector<std::string> const& strings, std::string_view delimiter = ",");
/**
 * @brief      ?????
 *
 * @param[in]  input  The input
 *
 * @return     ????
 */
[[nodiscard]] std::string
convertFrom(std::vector<std::vector<char>> const& input);
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
