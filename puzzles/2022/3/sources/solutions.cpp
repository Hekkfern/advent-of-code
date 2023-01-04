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
    //constexpr uint32_t GroupSize{ 3U };

    std::ifstream stream{ filename };
    std::string line1;
    std::string line2;
    std::string line3;
    uint32_t totalPriority = 0U;

    while (std::getline(stream, line1)) {
        std::getline(stream, line2);
        std::getline(stream, line3);
        totalPriority += calculatePriority(
            searchCommonItemInGroup(line1, line2, line3));
    }

    return std::to_string(totalPriority);
}

} // namespace aoc_2022_3
