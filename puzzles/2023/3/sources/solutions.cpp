#include "solutions.hpp"

#include "Schematic.hpp"
#include <utils/File.hpp>
#include <utils/String.hpp>

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
            if (lastPos == std::string_view::npos) {
                schematic.parts.emplace_back(
                    *utils::string::toNumber<uint32_t>(
                        std::string{beginIt, beginIt + lastPos}),
                    utils::geometry2d::Point2D<>::create(colIndex, rowIndex),
                    utils::geometry2d::Point2D<>::create(
                        static_cast<uint32_t>(lastPos) - colIndex, rowIndex));
            } else {
            }

        } else if (std::ispunct(line[colIndex])) {
            schematic.symbols.emplace_back(colIndex, rowIndex);
            ++colIndex;
        }
    }
    return schematic;
}

Schematic parseInputFile() noexcept
{
    // TODO
    return {};
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_3