#include "solutions.hpp"

#include "Monkey.h"
#include <array>
#include <fstream>
#include <regex>

namespace aoc_2022_11 {

// ---------- Private Methods ----------

Monkey parseMonkey(std::ifstream& fileStream)
{
    std::string line;
    std::smatch regexResult;
    // line 1
    std::getline(fileStream, line);
    auto patternLine1{ std::regex(R"(Monkey (\d+):)") };
    if (!regex_match(line, regexResult, patternLine1)) {
        throw std::logic_error("Regex failed in line 1");
    }
    MonkeyId monkeyId{ regexResult[1] };
}

void parseInput(const std::string& filename)
{
    std::ifstream inputFile{ filename };
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