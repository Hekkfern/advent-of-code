#include "rucksack.h"

#include <algorithm>
#include <stdexcept>
#include <unordered_set>
#include <vector>

namespace aoc_2022_3 {

uint32_t calculatePriority(const char itemType)
{
    constexpr uint32_t UppercaseFirstPriorityValue{ 27 };
    constexpr uint32_t LowercaseFirstPriorityValue{ 1 };

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

char searchCommonItemType(
    const std::string& compartment1,
    const std::string& compartment2)
{
    // fill first set
    const std::unordered_set<char> itemTypes1(
        std::cbegin(compartment1), std::cend(compartment1));
    // look for repeated item types in both compartments
    for (const char& c : compartment2) {
        if (const auto search = itemTypes1.find(c);
            search != itemTypes1.cend()) {
            return c;
        }
    }
    return 0;
}

} // namespace aoc_2022_3
