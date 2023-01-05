#pragma once

#include <cstdint>

namespace aoc_2022_4 {

struct SectionRange {
    uint32_t first;
    uint32_t last;
};

bool areSectionsOverlapped(
    const SectionRange& sectionsElf1,
    const SectionRange& sectionsElf2);

bool areSectionsNotOverlapped(
    const SectionRange& sectionsElf1,
    const SectionRange& sectionsElf2);

} // namespace aoc_2022_4