#pragma once

#include <cstdint>
#include <string>

namespace aoc_2022_3 {

uint32_t calculatePriority(char itemType);

char searchCommonItemType(
    const std::string& compartment1,
    const std::string& compartment2);

} // namespace aoc_2022_3
