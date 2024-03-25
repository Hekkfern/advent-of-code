#include "solutions.hpp"

#include "Rock.hpp"
#include <range/v3/view/enumerate.hpp>
#include <utils/File.hpp>

using namespace utils::geometry2d;

namespace aoc_2023_14 {

// ---------- Private Methods ----------

/**
 * @brief      Parses the whole input file.
 *
 * @param[in]  filePath  The path to the input file.
 *
 * @return     Parsed data.
 */
std::vector<Rock> parseInput(std::filesystem::path const& filePath)
{
    std::vector<Rock> rocks;
    utils::file::parseAndIterateWithIndex(
        filePath,
        [&rocks](
            std::size_t const rowIndex, std::string_view const line) -> void {
            for (const auto [colIndex, c] : line | ranges::views::enumerate) {
                switch (c) {
                case 'O':
                    rocks.emplace_back(
                        RockType::Rounded,
                        Point2D<>{
                            static_cast<int>(colIndex),
                            static_cast<int>(rowIndex)});
                    break;
                case '#':
                    rocks.emplace_back(
                        RockType::CubeShaped,
                        Point2D<>{
                            static_cast<int>(colIndex),
                            static_cast<int>(rowIndex)});
                    break;
                default:
                    /* No statements */
                    break;
                }
            }
        });
    return rocks;
}

std::vector<Rock> moveRocks(std::vector<Rock> const& rocks)
{
    // TODO
}

uint64_t calculateLoad(std::vector<Rock> const& rocks)
{
    // TODO
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto const rocks{parseInput(filePath)};
    auto const movedRocks{moveRocks(rocks)};
    return std::to_string(calculateLoad(moveRocks));
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_14