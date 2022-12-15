#include "StringUtils.hpp"

namespace utils::StringUtils {

bool contains(const std::string& str, const std::string& match)
{
    return str.find(match) != std::string::npos;
}

std::string trim(const std::string& s)
{
    auto first = s.find_first_not_of(" \f\n\r\t\v");
    auto last = s.find_last_not_of(" \f\n\r\t\v");
    return (first == std::string::npos) ? "" : s.substr(first, last + 1);
}

} // namespace utils::StringUtils
