#include "solutions.hpp"

#include <array>
#include <fstream>
#include <regex>

namespace aoc_2022_11 {

// ---------- Private Methods ----------

void parseInput(const std::string& filename){
    constexpr uint8_t InputLinesPerMonkey{6U};
    std::ifstream inputFile{ filename };
    std::array<std::string,InputLinesPerMonkey> lines;

    for (uint8_t i = 0U; i <InputLinesPerMonkey; ++i){
        std::getline(inputFile, lines.at(i));
    }


}


// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    (void)filename;
    return "";
}

std::string solvePart2(const std::string& filename)
{
    (void)filename;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_11