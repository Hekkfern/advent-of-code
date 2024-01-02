#include "File.hpp"

#include "String.hpp"
#include <fstream>

namespace utils::file {

std::optional<std::string> readFirstLine(std::filesystem::path const& filename)
{
    std::ifstream fileStream{filename.string()};
    if (!fileStream.is_open()) {
        return {};
    }

    std::string line;
    std::getline(fileStream, line);
    return line;
}

std::optional<std::string> readWholeFile(std::filesystem::path const& filename)
{
    auto const lines = readListOfStrings(filename.string());
    if (!lines) {
        return {};
    }

    std::string content{utils::string::join(*lines, "\n")};
    return content;
}

std::optional<std::vector<std::string>>
readListOfStrings(std::filesystem::path const& filename)
{
    std::vector<std::string> outList;

    bool const result{
        parseAndIterate(filename, [&outList](std::string_view line) {
            outList.emplace_back(line);
        })};
    if (!result) {
        return {};
    }

    return outList;
}

std::optional<std::vector<int64_t>>
readListOfNumbers(std::filesystem::path const& filename)
{
    std::vector<int64_t> outList;

    bool const result{
        parseAndIterate(filename, [&outList](const std::string_view line) {
            if (auto const value{utils::string::toNumber<int64_t>(line)}) {
                outList.emplace_back(*value);
            }
        })};
    if (!result) {
        return {};
    }

    return outList;
}

std::optional<std::vector<std::vector<int64_t>>>
readGroupsOfNumbers(std::filesystem::path const& filename)
{
    std::vector<std::vector<int64_t>> outList;

    bool const result{
        parseAndIterate(filename, [&outList](const std::string_view line) {
            if (utils::string::trim(line).empty()) {
                outList.emplace_back();
            } else {
                if (auto const value{utils::string::toNumber<int64_t>(line)}) {
                    if (outList.empty()) {
                        outList.emplace_back();
                    }
                    outList.back().emplace_back(*value);
                }
            }
        })};
    if (!result) {
        return {};
    }

    return outList;
}

std::optional<std::vector<std::vector<uint8_t>>>
readMatrixOfDigits(std::filesystem::path const& filename)
{
    std::vector<std::vector<uint8_t>> outList;

    bool const result{
        parseAndIterate(filename, [&outList](const std::string_view line) {
            std::vector<uint8_t> row;
            row.reserve(line.size());
            for (char const c : line) {
                row.emplace_back(c - '0');
            }
            outList.push_back(std::move(row));
        })};
    if (!result) {
        return {};
    }

    return outList;
}

bool parseAndIterate(
    std::filesystem::path const& filename,
    std::function<void(std::string_view line)> const& action)
{
    std::ifstream fileStream{filename.string()};
    if (!fileStream.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(fileStream, line)) {
        action(line);
    }

    return true;
}

} // namespace utils::file
