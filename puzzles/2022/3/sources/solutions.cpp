#include "solutions.hpp"

#include <array>
#include <cassert>
#include <fstream>
#include <unordered_set>

namespace aoc_2022_3 {

// ---------- Private Methods ----------

/**
 * @brief
 *
 * @param[in] itemType
 *
 * @return
 */
uint32_t calculatePriority(char const itemType)
{
    constexpr uint32_t UppercaseFirstPriorityValue{27};
    constexpr uint32_t LowercaseFirstPriorityValue{1};

    if (itemType >= 'a' && itemType <= 'z') {
        return static_cast<uint32_t>(itemType - 'a')
            + LowercaseFirstPriorityValue;
    } else if (itemType >= 'A' && itemType <= 'Z') {
        return static_cast<uint32_t>(itemType - 'A')
            + UppercaseFirstPriorityValue;
    } else {
        throw std::invalid_argument("Invalid character.");
    }
}

char searchCommonItemInRucksack(
    std::string const& compartment1, std::string const& compartment2)
{
    // fill first set
    const std::unordered_set<char> itemTypes1(
        std::cbegin(compartment1), std::cend(compartment1));
    // look for repeated item types in both compartments
    for (char const& c : compartment2) {
        if (auto const search = itemTypes1.find(c);
            search != itemTypes1.cend()) {
            return c;
        }
    }
    return 0;
}

char searchCommonItemInGroup(
    std::string const& rucksack1,
    std::string const& rucksack2,
    std::string const& rucksack3)
{
    // fill first set
    const std::unordered_set<char> itemTypes1(
        std::cbegin(rucksack1), std::cend(rucksack1));
    // fill second set
    const std::unordered_set<char> itemTypes2(
        std::cbegin(rucksack2), std::cend(rucksack2));
    // look for repeated item types in both compartments
    for (char const& c : rucksack3) {
        if (auto const search1 = itemTypes1.find(c);
            search1 != itemTypes1.cend()) {
            if (auto const search2 = itemTypes2.find(c);
                search2 != itemTypes2.cend()) {
                return c;
            }
        }
    }
    return 0;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    std::ifstream fileStream{filePath};
    std::string line;
    uint32_t totalPriority = 0U;

    while (std::getline(fileStream, line)) {
        assert(line.size() % 2 == 0);
        const std::string compartment1 = line.substr(0, line.size() / 2);
        const std::string compartment2 = line.substr(
            line.size() / 2, line.size());
        totalPriority += calculatePriority(
            searchCommonItemInRucksack(compartment1, compartment2));
    }

    return std::to_string(totalPriority);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    constexpr uint32_t GroupSize{3U};

    std::ifstream stream{filePath};
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

// ---------- End of Public Methods ----------

} // namespace aoc_2022_3
