#include "solutions.hpp"

#include "PipeType.hpp"
#include <cassert>
#include <utils/File.hpp>

namespace aoc_2023_10 {

// ---------- Private Methods ----------

PipeType parsePipeType(char const c)
{
    switch (c) {
    case 'F':
        return PipeType::SouthEast;
    case '-':
        return PipeType::Horizontal;
    case 'J':
        return PipeType::NorthWest;
    case '|':
        return PipeType::Vertical;
    case 'L':
        return PipeType::NorthEast;
    case '7':
        return PipeType::SouthWest;
    case '.':
        return PipeType::None;
    default:
        assert(false);
        return {};
    }
}

using Field = std::vector<std::vector<PipeType>>;

Field parseInput(std::filesystem::path const& filePath)
{
    Field outList;

    utils::file::parseAndIterate(
        filePath, [&outList](std::string_view const line) {
            std::vector<PipeType> row;
            row.reserve(line.size());
            for (char const c : line) {
                row.emplace_back(parsePipeType(c));
            }
            outList.emplace_back(std::move(row));
        });

    return outList;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto const field{parseInput(filePath)};
    return "";
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_10
