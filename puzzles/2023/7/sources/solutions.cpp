#include "solutions.hpp"

#include "Hand.hpp"
#include <sstream>
#include <utils/File.hpp>

namespace aoc_2023_7 {

// ---------- Private Methods ----------

std::vector<Hand> parseInput(std::filesystem::path const& filePath)
{
    std::vector<Hand> handList;
    bool const result{utils::file::parseAndIterate(
        filePath, [&handList](std::string_view line) {
            std::stringstream ss{std::string{line}};
            std::string cards;
            uint32_t bid;
            ss >> cards >> bid;
            handList.emplace_back(cards, bid);
        })};
    if (!result) {
        return {};
    }

    return handList;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto const input{parseInput(filePath)};
    return "";
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_7