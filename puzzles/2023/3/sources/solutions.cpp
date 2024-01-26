#include "solutions.hpp"

#include "Schematic.hpp"
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/fold_left.hpp>
#include <utils/File.hpp>
#include <utils/String.hpp>
#include <utils/geometry2d/Vector2D.hpp>

namespace aoc_2023_3 {

// ---------- Private Methods ----------

Schematic
parseInputLine(std::size_t const rowIndex, std::string_view line) noexcept
{
    static constexpr std::string_view Digits{"0123456789"};

    Schematic schematic;
    for (std::size_t colIndex{0ULL}; colIndex < line.size();) {
        if (line[colIndex] == '.') {
            ++colIndex;
        } else if (std::isdigit(line[colIndex])) {
            std::string_view substr{line.substr(colIndex)};
            std::size_t lastPos{substr.find_first_not_of(Digits)};
            lastPos = lastPos != std::string_view::npos
                ? lastPos
                : line.size() - colIndex;
            schematic.parts.emplace_back(
                *utils::string::toNumber<uint32_t>(substr.substr(0, lastPos)),
                utils::geometry2d::Line2D<>{
                    utils::geometry2d::Point2D<>::create(colIndex, rowIndex),
                    utils::geometry2d::Point2D<>::create(
                        lastPos + colIndex - 1U, rowIndex)});
            colIndex += lastPos;
        } else if (std::ispunct(line[colIndex])) {
            schematic.symbols.emplace_back(colIndex, rowIndex);
            ++colIndex;
        }
    }
    return schematic;
}

Schematic parseInputFile(std::filesystem::path const& filePath) noexcept
{
    Schematic schematic;
    utils::file::parseAndIterateWithIndex(
        filePath,
        [&schematic](size_t const index, std::string_view const line) -> void {
            auto tempSchematic{parseInputLine(index, line)};
            schematic.merge(std::move(tempSchematic));
        });
    return schematic;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto const schematic{parseInputFile(filePath)};
    uint64_t accumPartNumbers{ranges::fold_left(
        schematic.parts,
        0ULL,
        [&schematic](uint64_t accum, Part const& part) -> uint64_t {
            if (ranges::any_of(
                    schematic.symbols,
                    [&part](
                        utils::geometry2d::Point2D<> const& symbolPos) -> bool {
                        return ranges::any_of(
                            part.line.getVertexes(),
                            [&symbolPos](
                                utils::geometry2d::Point2D<> const& vertex)
                                -> bool {
                                utils::geometry2d::Vector2D<> v{
                                    vertex, symbolPos};
                                return v.distance() <= 1ULL;
                            });
                    })) {
                return accum + part.partNumber;
            }
            return accum;
        })};

    return std::to_string(accumPartNumbers);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_3