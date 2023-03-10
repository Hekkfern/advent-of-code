#pragma once

#include <concepts>
#include <sstream>
#include <string>
#include <vector>

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

template <typename T>
    requires std::integral<T> || std::floating_point<T>
T toNumber(const std::string& str)
{
    std::stringstream ss{ str };
    T num;
    ss >> num;
    return num;
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

} // namespace utils::StringUtils
