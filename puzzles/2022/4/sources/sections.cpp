#include "sections.h"

namespace aoc_2022_4 {

constexpr uint32_t MaximumSectionId{ 99U };

bool areSectionsOverlapped(
    const SectionRange& sectionsElf1,
    const SectionRange& sectionsElf2)
{
    return ((sectionsElf1.first >= sectionsElf2.first)
            && (sectionsElf1.last <= sectionsElf2.last))
        || ((sectionsElf1.first <= sectionsElf2.first)
            && (sectionsElf1.last >= sectionsElf2.last));
}

bool areSectionsNotOverlapped(
    const SectionRange& sectionsElf1,
    const SectionRange& sectionsElf2)
{
    return (sectionsElf1.last < sectionsElf2.first)
        || (sectionsElf1.first > sectionsElf2.last);
}

} // namespace aoc_2022_4