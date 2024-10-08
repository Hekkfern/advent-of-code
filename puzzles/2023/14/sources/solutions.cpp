#include "solutions.hpp"

#include "Rocks.hpp"
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/join.hpp>
#include <utils/File.hpp>
#include <utils/cache/LoopCache.hpp>

namespace aoc_2023_14 {

// ---------- Private Methods ----------

/**
 * @brief      Parses the whole input file and generates a flatten grid.
 *
 * @param[in]  filePath  The path to the input file.
 *
 * @return     Parsed data.
 */
Rocks parseInput(std::filesystem::path const& filePath)
{
    std::vector<std::string> rocks;
    utils::file::parseAndIterate(
        filePath, [&rocks](std::string_view const line) -> void {
            rocks.emplace_back(line);
        });
    return Rocks{
        rocks | ranges::views::join | ranges::to<std::string>,
        rocks[0].size(),
        rocks.size()};
}

/**
 * \brief ???
 * \param[in,out] rocks  ???
 */
void executeOneCycle(Rocks& rocks)
{
    rocks.shiftNorth();
    rocks.shiftWest();
    rocks.shiftSouth();
    rocks.shiftEast();
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto rocks{parseInput(filePath)};
    rocks.shiftNorth();
    return std::to_string(rocks.calculateLoad());
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    auto rocks{parseInput(filePath)};
    /** Cache whose "key" is the status of the rocks before the cycle, and the
     * "value" is the status after the cycle.
     */
    utils::cache::LoopCache::run<
        Rocks>(rocks, 1'000'000'000LL, [](Rocks& rocksToChange) -> void {
        executeOneCycle(rocksToChange);
    });
    return std::to_string(rocks.calculateLoad());
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_14
