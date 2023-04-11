#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace utils::file {

/**
 * @brief      Reads only the first line of a file.
 *
 * @param[in]  filename  The filename.
 *
 * @return     A string with the content of the first line, or std::nullopt.
 */
[[nodiscard]] std::optional<std::string> readFirstLine(const std::string& filename);
/**
 * @brief      Reads the whole file and converts its content to generate a
 *             single string.
 *
 * @param[in]  filename  The filename.
 *
 * @return     A string with all the lines joined with "\n" characters.
 */
[[nodiscard]] std::optional<std::string> readWholeLine(const std::string& filename);
/**
 * @brief      Reads a list of strings separated by new lines, from a file.
 *
 * @param[in]  filename  The filename.
 *
 * @return     List of string, where each string contains the content of one
 *             line in the file.
 */
[[nodiscard]] std::optional<std::vector<std::string>> readListOfStrings(
    const std::string& filename);
/**
 * @brief      Reads a list of numbers separated by new lines, from a file.
 *
 * @param[in]  filename  The filename.
 *
 * @return     List of numbers, where each numbers corresponds to the content of
 *             one line in the file.
 */
[[nodiscard]] std::optional<std::vector<int64_t>> readListOfNumbers(
    const std::string& filename);
/**
 * @brief      Reads groups of numbers, separated by empty lines, from a file.
 *
 * @param[in]  filename  The filename.
 *
 * @return     List of groups of numbers. Each group contains a list of numbers.
 */
[[nodiscard]] std::optional<std::vector<std::vector<int64_t>>> readGroupsOfNumbers(
    const std::string& filename);
/**
 * @brief      Reads a list of numbers, where each character of a line is a
 *             independent digit.
 *
 * @param[in]  filename  The filename.
 *
 * @return     List of list of digits.
 */
[[nodiscard]] std::optional<std::vector<std::vector<uint8_t>>> readMatrixOfDigits(
    const std::string& filename);

} // namespace utils::file
