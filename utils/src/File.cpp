#include "File.hpp"

#include "String.hpp"
#include <fstream>

namespace utils::file {

std::optional<std::string> readFirstLine(std::string const& filename)
{
    std::ifstream fileStream{filename};
    if (!fileStream.is_open()) {
        return std::nullopt;
    }

    std::string line;
    std::getline(fileStream, line);
    return line;
}

std::optional<std::string> readWholeFile(std::string const& filename)
{
    auto const lines = readListOfStrings(filename);
    if (!lines) {
        return std::nullopt;
    }

    std::string content{utils::string::join(*lines, "\n")};
    return content;
}

std::optional<std::vector<std::string>>
readListOfStrings(std::string const& filename)
{
    std::ifstream fileStream{filename};
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

std::optional<std::vector<int64_t>>
readListOfNumbers(std::string const& filename)
{
    std::ifstream fileStream{filename};
    if (!fileStream.is_open()) {
        return std::nullopt;
    }

    std::vector<int64_t> outList;
    std::string line;

    while (std::getline(fileStream, line)) {
        if (auto value{utils::string::toNumber<int64_t>(line)}) {
            outList.emplace_back(*value);
        }
    }

    return outList;
}

std::optional<std::vector<std::vector<int64_t>>>
readGroupsOfNumbers(std::string const& filename)
{
    std::ifstream fileStream{filename};
    if (!fileStream.is_open()) {
        return std::nullopt;
    }

    std::vector<std::vector<int64_t>> outList;
    std::string line;

    while (std::getline(fileStream, line)) {
        if (utils::string::trim(line).empty()) {
            outList.emplace_back();
        } else {
            auto value{utils::string::toNumber<int64_t>(line)};
            if (value) {
                outList.back().emplace_back(*value);
            }
        }
    }

    return outList;
}

std::optional<std::vector<std::vector<uint8_t>>>
readMatrixOfDigits(std::string const& filename)
{
    std::ifstream fileStream{filename};
    if (!fileStream.is_open()) {
        return std::nullopt;
    }

    std::vector<std::vector<uint8_t>> outList;
    std::string line;

    while (std::getline(fileStream, line)) {
        std::vector<uint8_t> row;
        row.reserve(line.size());
        for (char const c : line) {
            row.emplace_back(c - '0');
        }
        outList.push_back(std::move(row));
    }

    return outList;
}

void parseAndIterate(
    std::string const& filename,
    std::function<void(std::string const& line)> const& action)
{
    std::ifstream fileStream{filename};
    if (!fileStream.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(fileStream, line)) {
        action(line);
    }
}

} // namespace utils::file
