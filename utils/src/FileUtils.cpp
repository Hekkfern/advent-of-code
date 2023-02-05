#include "FileUtils.hpp"

#include "StringUtils.hpp"
#include <fstream>

namespace utils::FileUtils {

std::optional<std::string> readFirstLine(const std::string& filename)
{
    std::ifstream fileStream{ filename };
    if (!fileStream.is_open()) {
        return std::nullopt;
    }

    std::string line;
    std::getline(fileStream, line);
    return line;
}

std::optional<std::string> readWholeLine(const std::string& filename)
{
    const auto lines = readListOfStrings(filename);
    if (!lines) {
        return std::nullopt;
    }

    std::string content{ utils::StringUtils::join(*lines, "\n") };
    return content;
}

std::optional<std::vector<std::string>> readListOfStrings(
    const std::string& filename)
{
    std::ifstream fileStream{ filename };
    if (!fileStream.is_open()) {
        return std::nullopt;
    }

    std::vector<std::string> outList;
    std::string line;

    while (std::getline(fileStream, line)) {
        outList.emplace_back(line);
    }

    return outList;
}

std::optional<std::vector<int64_t>> readListOfNumbers(
    const std::string& filename)
{
    std::ifstream fileStream{ filename };
    if (!fileStream.is_open()) {
        return std::nullopt;
    }

    std::vector<int64_t> outList;
    std::string line;

    while (std::getline(fileStream, line)) {
        outList.emplace_back(utils::StringUtils::toNumber<int64_t>(line));
    }

    return outList;
}

std::optional<std::vector<std::vector<int64_t>>> readGroupsOfNumbers(
    const std::string& filename)
{
    std::ifstream fileStream{ filename };
    if (!fileStream.is_open()) {
        return std::nullopt;
    }

    std::vector<std::vector<int64_t>> outList;
    std::string line;

    while (std::getline(fileStream, line)) {
        if (utils::StringUtils::trim(line).empty()) {
            outList.emplace_back();
        } else {
            outList.back().emplace_back(
                utils::StringUtils::toNumber<int64_t>(line));
        }
    }

    return outList;
}

std::optional<std::vector<std::vector<uint8_t>>> readMatrixOfDigits(
    const std::string& filename)
{
    std::ifstream fileStream{ filename };
    if (!fileStream.is_open()) {
        return std::nullopt;
    }

    std::vector<std::vector<uint8_t>> outList;
    std::string line;

    while (std::getline(fileStream, line)) {
        std::vector<uint8_t> row;
        row.reserve(line.size());
        for (const char c : line) {
            row.emplace_back(c - '0');
        }
        outList.push_back(std::move(row));
    }

    return outList;
}

} // namespace utils::FileUtils
