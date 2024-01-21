#include "solutions.hpp"

#include "Schematic.hpp"
#include <range/v3/algorithm/any_of.hpp>
#include <utils/File.hpp>
#include <utils/String.hpp>
#include <utils/geometry2d/Vector2D.hpp>

namespace aoc_2023_3 {

// ---------- Private Methods ----------

Schematic
parseInputLine(uint32_t const rowIndex, std::string_view line) noexcept
{
    Schematic schematic;
    for (uint32_t colIndex{0U}; colIndex < line.size();) {
        if (line[colIndex] == '.') {
            ++colIndex;
            continue;
        } else if (std::isdigit(line[colIndex])) {
            auto beginIt{std::begin(line) + colIndex};
            std::string_view substr{beginIt, std::end(line)};
            auto lastPos{substr.find_first_of('.')};
            lastPos = lastPos != std::string_view::npos ? lastPos : line.size();
            schematic.parts.emplace_back(
                *utils::string::toNumber<uint32_t>(
                    std::string{beginIt, beginIt + lastPos}),
                utils::geometry2d::Point2D<>::create(colIndex, rowIndex),
                utils::geometry2d::Point2D<>::create(
                    static_cast<uint32_t>(lastPos) - colIndex, rowIndex));
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
        [&schematic](
            uint32_t const index, std::string_view const line) -> void {
            auto tempSchematic{parseInputLine(index, line)};
            schematic.merge(std::move(tempSchematic));
        });
    return schematic;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    uint32_t accumPartNumbers{0U};
    auto const schematic{parseInputFile(filePath)};
    for (auto const& part : schematic.parts) {
        if (ranges::any_of(
                schematic.symbols,
                [](utils::geometry2d::Point2D<> const& symbolPos) -> bool {
                    // TODO
                    return true;
                })) {
            // TODO
        }
    }

    return std::to_string(accumPartNumbers);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_3