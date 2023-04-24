#include "solutions.hpp"

#include <array>
#include <fstream>
#include <utils/Interval.hpp>
#include <utils/String.hpp>

namespace aoc_2022_4 {

// ---------- Private Methods ----------

constexpr uint32_t GroupSize{2U};

std::vector<utils::interval::Interval<int32_t>>
parseInputLine(std::string const& line)
{
    constexpr auto ElfSeparator{","};
    constexpr auto RangeSeparator{"-"};

    std::vector<utils::interval::Interval<int32_t>> sections;
    sections.reserve(GroupSize);

    // parse line of the input file
    auto ranges{utils::string::split(line, ElfSeparator)};
    for (auto const& range : ranges) {
        auto values{utils::string::split(range, RangeSeparator)};
        sections.emplace_back(
            utils::string::toNumber<int32_t>(values[0]),
            utils::string::toNumber<int32_t>(values[1]));
    }

    return sections;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::string const& filename)
{
    std::ifstream fileStream{filename};
    std::string line;
    uint32_t totalOverlaps{0U};

    while (std::getline(fileStream, line)) {
        std::vector<utils::interval::Interval<int32_t>> sections{
            parseInputLine(line)};
        if (sections[0].subsumes(sections[1])
            || sections[1].subsumes(sections[0])) {
            ++totalOverlaps;
        }
    }

    return std::to_string(totalOverlaps);
}

std::string solvePart2(std::string const& filename)
{
    std::ifstream fileStream{filename};
    std::string line;
    uint32_t totalNoOverlaps{0U};

    while (std::getline(fileStream, line)) {
        std::vector<utils::interval::Interval<int32_t>> sections{
            parseInputLine(line)};
        if (sections[0].overlaps(sections[1])) {
            ++totalNoOverlaps;
        }
    }

    return std::to_string(totalNoOverlaps);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_4
