#include "InputUtils.hpp"

#include "StringUtils.hpp"
#include <fstream>

namespace utils::InputUtils {

std::vector<std::string> readListOfStrings(const std::string& filename)
{
    std::ifstream stream{ filename };
    std::vector<std::string> outList;
    std::string line;

    while (std::getline(stream, line)) {
        outList.emplace_back(std::move(line));
    }

    return outList;
}

std::vector<int64_t> readListOfNumbers(const std::string& filename)
{
    std::ifstream stream{ filename };
    std::vector<int64_t> outList;
    std::string line;

    while (std::getline(stream, line)) {
        outList.emplace_back(utils::StringUtils::toNumber<int64_t>(line));
    }

    return outList;
}

std::vector<std::vector<int64_t>> readGroupsOfNumbers(
    const std::string& filename)
{
    std::ifstream stream{ filename };
    std::vector<std::vector<int64_t>> outList;
    std::string line;

    while (std::getline(stream, line)) {
        if (utils::StringUtils::trim(line).empty()) {
            outList.emplace_back();
        } else {
            outList.back().emplace_back(
                utils::StringUtils::toNumber<int64_t>(line));
        }
    }

    return outList;
}
} // namespace utils::InputUtils
