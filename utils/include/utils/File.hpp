#pragma once

#include <cstdint>
#include <filesystem>
#include <functional>
#include <optional>
#include <string>
#include <vector>

namespace utils::file {

/**
 * @brief      Reads only the first line of a file.
 *
 * @param[in]  filePath  The filename.
 *
 * @return     A string with the content of the first line, or std::nullopt.
 */
[[nodiscard]] std::optional<std::string>
readFirstLine(std::filesystem::path const& filePath);
/**
 * @brief      Reads the whole file and converts its content to generate a
 *             single string.
 *
 * @param[in]  filePath  The filename.
 *
 * @return     A string with all the lines joined with "\n" characters.
 */
[[nodiscard]] std::optional<std::string>
readWholeFile(std::filesystem::path const& filePath);
/**
 * @brief      Reads a list of strings separated by new lines, from a file.
 *
 * @param[in]  filePath  The filename.
 *
 * @return     List of string, where each string contains the content of one
 *             line in the file.
 */
[[nodiscard]] std::optional<std::vector<std::string>>
readListOfStrings(std::filesystem::path const& filePath);
/**
 * @brief      Reads a list of numbers separated by new lines, from a file.
 *
 * @param[in]  filePath  The filename.
 *
 * @return     List of numbers, where each numbers corresponds to the content of
 *             one line in the file.
 */
[[nodiscard]] std::optional<std::vector<int64_t>>
readListOfNumbers(std::filesystem::path const& filePath);
/**
 * @brief      Reads groups of numbers, separated by empty lines, from a file.
 *
 * @param[in]  filePath  The filename.
 *
 * @return     List of groups of numbers. Each group contains a list of numbers.
 */
[[nodiscard]] std::optional<std::vector<std::vector<int64_t>>>
readGroupsOfNumbers(std::filesystem::path const& filePath);
/**
 * @brief      Reads a list of numbers, where each character of a line is a
 *             independent digit.
 *
 * @param[in]  filePath  The filename.
 *
 * @return     List of list of digits.
 */
[[nodiscard]] std::optional<std::vector<std::vector<uint8_t>>>
readMatrixOfDigits(std::filesystem::path const& filePath);
/**
 * @brief      Reads a matrix of characters.
 *
 * @param[in]  filePath  The filename.
 *
 * @return     Matrix of characters.
 */
[[nodiscard]] std::optional<std::vector<std::vector<char>>>
readMatrixOfChars(std::filesystem::path const& filePath);
/**
 * @brief      Reads a text file and executes the selected action in each line.
 *
 * @param[in]  filePath  The filename.
 * @param[in]  action    Code to be executed for every line.
 *
 * @return     True if the file exists and can be opened. False, otherwise.
 */
bool parseAndIterate(
    std::filesystem::path const& filePath,
    std::function<void(std::string_view line)> const& action);
/**
 * @brief      Reads a text file and executes the selected action in each line.
 *
 * @param[in]  filePath  The filename.
 * @param[in]  action    Code to be executed for every line.
 *
 * @return     True if the file exists and can be opened. False, otherwise.
 */
bool parseAndIterateWithIndex(
    std::filesystem::path const& filePath,
    std::function<void(size_t index, std::string_view line)> const& action);

} // namespace utils::file
