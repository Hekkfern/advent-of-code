#include "String.hpp"

#include <range/v3/all.hpp>

namespace utils::string {

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

std::string join(const std::vector<std::string>& strings, std::string delim)
{
    if (strings.empty()) {
        return {};
    }

    return ranges::accumulate(
        strings.begin() + 1,
        strings.end(),
        strings[0],
        [&delim](const std::string& x, const std::string& y) {
            return x + delim + y;
        });
}

std::string convertFrom(const std::vector<std::vector<char>>& input)
{
    std::vector<std::string> lines;
    for (const auto& item : input) {
        lines.emplace_back(item.begin(), item.end());
    }
    return join(lines, "\n");
}

std::vector<std::string> split(
    const std::string& str,
    const std::string& separator)
{
    std::vector<std::string> resultList;
    size_t begin = 0U;
    size_t end = 0U;
    while ((end = str.find(separator, begin)) != std::string::npos) {
        resultList.push_back(str.substr(begin, end - begin));
        begin = end + separator.size();
    }
    resultList.push_back(str.substr(begin));

    if (separator.empty()) {
        for (auto it = resultList.begin(); it != resultList.end(); ++it) {
            if (it->empty()) {
                resultList.erase(it--);
            }
        }
    }
    return resultList;
}

} // namespace utils::string
