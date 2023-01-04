#pragma once

#include <cstdint>
#include <string>

namespace aoc_2022_3 {

uint32_t calculatePriority(char itemType);

char searchCommonItemInRucksack(
    const std::string& compartment1,
    const std::string& compartment2);

char searchCommonItemInGroup(
    const std::string& rucksack1,
    const std::string& rucksack2,
    const std::string& rucksack3);

} // namespace aoc_2022_3
