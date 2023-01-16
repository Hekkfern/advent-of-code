#include "solutions.hpp"

#include <deque>
#include <fstream>
#include <unordered_set>

namespace aoc_2022_6 {

// ---------- Private Methods ----------

bool areAllCharactersDifferent(const std::deque<char>& chars)
{
    std::unordered_set<char> uniqueChars;

    for (const char& candidate : chars) {
        auto [it, res] = uniqueChars.emplace(candidate);
        if (!res) {
            return false;
        }
    }

    return true;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    constexpr uint32_t NumberOfDifferentCharacters{ 4U };

    std::ifstream fileStream{ filename };
    char newChar = 0;
    uint32_t charCounter = 0U;
    std::deque<char> chars;
    bool found = false;
    // initialize the first items of the sequence
    for (uint32_t i = 0U; i < (NumberOfDifferentCharacters - 1U); ++i) {
        fileStream.get(newChar);
        chars.emplace_back(newChar);
    }
    charCounter = NumberOfDifferentCharacters - 1U;
    // analyze every new character
    while (fileStream.get(newChar) && !found) {
        ++charCounter;
        chars.emplace_back(newChar);
        if (chars.size() > NumberOfDifferentCharacters) {
            chars.pop_front();
        }
        if (areAllCharactersDifferent(chars)) {
            found = true;
        }
    }

    return std::to_string(charCounter);
}

std::string solvePart2(const std::string& filename)
{
    constexpr uint32_t NumberOfDifferentCharacters{ 14U };

    std::ifstream fileStream{ filename };
    char newChar = 0;
    uint32_t charCounter = 0U;
    std::deque<char> chars;
    bool found = false;
    // initialize the first items of the sequence
    for (uint32_t i = 0U; i < (NumberOfDifferentCharacters - 1U); ++i) {
        fileStream.get(newChar);
        chars.emplace_back(newChar);
    }
    charCounter = NumberOfDifferentCharacters - 1U;
    // analyze every new character
    while (fileStream.get(newChar) && !found) {
        ++charCounter;
        chars.emplace_back(newChar);
        if (chars.size() > NumberOfDifferentCharacters) {
            chars.pop_front();
        }
        if (areAllCharactersDifferent(chars)) {
            found = true;
        }
    }

    return std::to_string(charCounter);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_6