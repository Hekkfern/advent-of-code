#include "solutions.hpp"

#include "CharSlidingWindow.h"
#include <fstream>

namespace aoc_2022_6 {

// ---------- Private Methods ----------

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    constexpr uint32_t NumberOfDifferentCharacters{4U};

    std::ifstream fileStream{filePath};
    char newChar = 0;
    uint32_t charCounter = 0U;
    CharSlidingWindow<NumberOfDifferentCharacters> charSlidingWindow;
    bool found = false;
    // analyze every new character
    while (fileStream.get(newChar) && !found) {
        ++charCounter;
        charSlidingWindow.addChar(newChar);
        if (charSlidingWindow.areUnique()) {
            found = true;
        }
    }

    return std::to_string(charCounter);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    constexpr uint32_t NumberOfDifferentCharacters{14U};

    std::ifstream fileStream{filePath};
    char newChar = 0;
    uint32_t charCounter = 0U;
    CharSlidingWindow<NumberOfDifferentCharacters> charSlidingWindow;
    bool found = false;
    // analyze every new character
    while (fileStream.get(newChar) && !found) {
        ++charCounter;
        charSlidingWindow.addChar(newChar);
        if (charSlidingWindow.areUnique()) {
            found = true;
        }
    }

    return std::to_string(charCounter);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_6