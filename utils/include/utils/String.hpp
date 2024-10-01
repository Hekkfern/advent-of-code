#pragma once

#include "Concepts.hpp"
#include <charconv>
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
 * @brief      Removes all the white-space and tab characters at the beginning
 *             of the selected string.
 *
 * @param      s     The string to modify.
 *
 * @return     String with all the white-space and tab characters removed at the
 *             beginning.
 */
[[nodiscard]] std::string ltrim(std::string_view s);
/**
 * @brief      Removes all the white-space and tab characters at the end of the
 *             selected string.
 *
 * @param      s     The string to modify.
 *
 * @return     String with all the white-space and tab characters removed at the
 *             end.
 */
[[nodiscard]] std::string rtrim(std::string_view s);
/**
 * @brief      Removes all the space and tab characters from both sides of a
 *             string.
 *
 * @param[in]  s     The string to modify.
 *
 * @return     String without spaces or tabs at both sides.
 */
[[nodiscard]] std::string trim(std::string_view s);
/**
 * @brief      Converts a string to a number.
 *
 * @param[in]  s     The text to convert to.
 *
 * @tparam     T     Type of the resulting number.
 *
 * @return     Converted number.
 *
 * @{
 */
template <NumericType T>
[[nodiscard]] std::optional<T> toNumber(std::string_view s, int base = 10)
{
    T value{};
    auto [ptr, ec]{std::from_chars(s.data(), s.data() + s.size(), value, base)};
    if (ec != std::errc{}) {
        return {};
    }
    return value;
}
template <IntegerType T>
[[nodiscard]] std::optional<T> toNumber(char s)
{
    if (!std::isdigit(s)) {
        return {};
    }
    return static_cast<T>(s - '0');
}
/** }@ */
/**
 * @brief      Joins a list of strings and puts a delimiting string between
 *             them.
 *
 * @param[in]  strings    The list of strings to join.
 * @param[in]  delimiter  The delimiter.
 *
 * @return     Resulting string.
 */
[[nodiscard]] std::string
join(std::vector<std::string> const& strings, std::string_view delimiter = ",");
/**
 * @brief      Joins a list of list of characters.
 *
 * @param[in]  input  List of list of chars.
 *
 * @return     Resulting string.
 */
[[nodiscard]] std::string join(std::vector<std::vector<char>> const& input);
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
/**
 * @brief      Removes all the duplicated space-like characters.
 *
 * @param[in]  str   The string to modify.
 *
 * @return     String without duplicated space-like characters.
 */
[[nodiscard]] std::string remove_excess_whitespace(std::string str);

} // namespace utils::string
