#include "solutions.hpp"

#include "sections.h"

#include <array>
#include <fstream>
#include <utils/StringUtils.hpp>

namespace aoc_2022_4 {

// ---------- Private Methods ----------

constexpr uint32_t GroupSize{ 2U };

std::array<SectionRange, GroupSize> parseInputLine(const std::string& line)
{
    constexpr auto ElfSeparator{ ',' };
    constexpr auto RangeSeparator{ '-' };

    std::array<SectionRange, GroupSize> sections{};

    // parse line of the input file
    std::stringstream lineStream{ line };
    std::string range;
    uint32_t elfCounter = 0U;
    while (std::getline(lineStream, range, ElfSeparator)) {
        std::stringstream rangeStream{ range };
        std::string rangeEdge;
        uint32_t valueCounter = 0U;
        while (std::getline(rangeStream, rangeEdge, RangeSeparator)) {
            const auto value = utils::StringUtils::toNumber<uint32_t>(
                rangeEdge);
            if (valueCounter == 0) {
                sections.at(elfCounter).mFirst = value;
            } else {
                sections.at(elfCounter).mLast = value;
            }
            ++valueCounter;
        }
        ++elfCounter;
    }

    return sections;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    std::ifstream fileStream{ filename };
    std::string line;
    uint32_t totalOverlaps = 0U;

    while (std::getline(fileStream, line)) {
        std::array<SectionRange, GroupSize> sections = parseInputLine(line);
        if (areSectionsOverlapped(sections[0], sections[1])) {
            ++totalOverlaps;
        }
    }

    return std::to_string(totalOverlaps);
}

std::string solvePart2(const std::string& filename)
{
    std::ifstream fileStream{ filename };
    std::string line;
    uint32_t totalNoOverlaps = 0U;

    while (std::getline(fileStream, line)) {
        std::array<SectionRange, GroupSize> sections = parseInputLine(line);
        if (!areSectionsNotOverlapped(sections[0], sections[1])) {
            ++totalNoOverlaps;
        }
    }

    return std::to_string(totalNoOverlaps);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_4
