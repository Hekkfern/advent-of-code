#include "solutions.hpp"

#include "rucksack.h"

#include <array>
#include <cassert>
#include <fstream>

namespace aoc_2022_3 {

std::string solvePart1(const std::string& filename)
{
    std::ifstream stream{ filename };
    std::string line;
    uint32_t totalPriority = 0U;

    while (std::getline(stream, line)) {
        assert(line.size() % 2 == 0);
        const std::string compartment1 = line.substr(0, line.size() / 2);
        const std::string compartment2 = line.substr(
            line.size() / 2, line.size());
        totalPriority += calculatePriority(
            searchCommonItemInRucksack(compartment1, compartment2));
    }

    return std::to_string(totalPriority);
}

std::string solvePart2(const std::string& filename)
{
    constexpr uint32_t GroupSize{ 3U };

    std::ifstream stream{ filename };
    std::array<std::string, GroupSize> rucksacks;
    uint32_t totalPriority = 0U;

    while (std::getline(stream, rucksacks[0])) {
        for (uint32_t i = 1; i < GroupSize; ++i) {
            std::getline(stream, rucksacks.at(i));
        }
        totalPriority += calculatePriority(
            searchCommonItemInGroup(rucksacks[0], rucksacks[1], rucksacks[2]));
    }

    return std::to_string(totalPriority);
}

} // namespace aoc_2022_3
