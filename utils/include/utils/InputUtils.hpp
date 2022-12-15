#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace utils::InputUtils {

/**
 * @brief
 *
 * @param[in] filename
 * @return std::vector<std::string>
 */
std::vector<std::string> readListOfStrings(const std::string& filename);
/**
 * @brief
 *
 * @param[in] filename
 * @return std::vector<int64_t>
 */
std::vector<int64_t> readListOfNumbers(const std::string& filename);
/**
 * @brief
 *
 * @param[in] filename
 * @return std::vector<std::vector<int64_t>>
 */
std::vector<std::vector<int64_t>> readGroupsOfNumbers(
    const std::string& filename);

} // namespace utils::InputUtils
