#include "solutions.hpp"

#include "PipeSystem.hpp"
#include "Valve.hpp"
#include <fstream>
#include <regex>
#include <utils/String.hpp>

namespace aoc_2022_16 {

// ---------- Private Methods ----------

Valve parseInputLine(const std::string& line)
{
    std::smatch regexResult;
    constexpr auto Pattern{
        R"(Valve ([A-Z]{2} has flow rate=([0-9]+); tunnel(?:s?) lead(?:s?) to valve(?:s?) ([A-Z, ]+)))"
    };
    if (!std::regex_match(line, regexResult, std::regex(Pattern))) {
        throw std::logic_error("Regex failed in parsing the line");
    }
    return Valve{ std::string{ regexResult[1] },
                  utils::string::toNumber<uint32_t>(regexResult[2]),
                  std::vector<std::string>{ { regexResult[3] } } };
}

PipeSystem parseInput(std::ifstream& fileStream)
{
    std::string line;
    PipeSystem pipeSystem;
    while (std::getline(fileStream, line)) {
        pipeSystem.addValve(parseInputLine(line));
    }
    return pipeSystem;
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

} // namespace aoc_2022_16