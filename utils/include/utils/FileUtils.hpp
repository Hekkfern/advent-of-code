#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include <optional>

namespace utils::FileUtils {

/**
 * @brief
 *
 * @param[in] filename
 * @return std::vector<std::string>
 */
std::optional<std::string> readFirstLine(const std::string& filename);
/**
 * @brief
 *
 * @param[in] filename
 * @return std::vector<std::string>
 */
std::optional<std::vector<std::string>> readListOfStrings(const std::string& filename);
/**
 * @brief
 *
 * @param[in] filename
 * @return std::vector<int64_t>
 */
std::optional<std::vector<int64_t>> readListOfNumbers(const std::string& filename);
/**
 * @brief
 *
 * @param[in] filename
 * @return std::vector<std::vector<int64_t>>
 */
std::optional<std::vector<std::vector<int64_t>>> readGroupsOfNumbers(
    const std::string& filename);

std::optional<std::vector<std::vector<uint8_t>>> readMatrixOfDigits(
    const std::string& filename);

} // namespace utils::FileUtils
