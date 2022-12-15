#pragma once

#include <string>

namespace utils::StringUtils {

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

} // namespace utils::StringUtils
