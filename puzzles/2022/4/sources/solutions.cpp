#include "solutions.hpp"

#include <array>
#include <fstream>
#include <utils/String.hpp>

namespace aoc_2022_4 {

// ---------- Private Types and Constants ----------

struct SectionRange {
    uint32_t mFirst;
    uint32_t mLast;
};

constexpr uint32_t GroupSize{ 2U };

// ---------- End of Private Types and Constants ----------

// ---------- Private Methods ----------

bool areSectionsOverlapped(
    const SectionRange& sectionsElf1,
    const SectionRange& sectionsElf2)
{
    return ((sectionsElf1.mFirst >= sectionsElf2.mFirst)
            && (sectionsElf1.mLast <= sectionsElf2.mLast))
        || ((sectionsElf1.mFirst <= sectionsElf2.mFirst)
            && (sectionsElf1.mLast >= sectionsElf2.mLast));
}

bool areSectionsNotOverlapped(
    const SectionRange& sectionsElf1,
    const SectionRange& sectionsElf2)
{
    return (sectionsElf1.mLast < sectionsElf2.mFirst)
        || (sectionsElf1.mFirst > sectionsElf2.mLast);
}

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
            const auto value = utils::string::toNumber<uint32_t>(rangeEdge);
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
