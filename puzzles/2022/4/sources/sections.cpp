#include "sections.h"

namespace aoc_2022_4 {

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

} // namespace aoc_2022_4