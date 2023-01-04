#include "solutions.hpp"

#include "rps.h"

#include <fstream>

namespace aoc_2022_2 {

std::string solvePart1(const std::string& filename)
{
    std::ifstream stream{ filename };
    std::string line;
    uint32_t totalScore = 0U;

    while (std::getline(stream, line)) {
        const Shape opponentShape = convertStringToShape(line[0]);
        const Shape yourShape = convertStringToShape(line[2]);
        totalScore += calculateRoundScore(yourShape, opponentShape);
    }

    return std::to_string(totalScore);
}

std::string solvePart2(const std::string& filename)
{
    std::ifstream stream{ filename };
    std::string line;
    uint32_t totalScore = 0U;

    while (std::getline(stream, line)) {
        const Shape opponentShape = convertStringToShape(line[0]);
        const MatchResult matchResult = convertStringToMatchResult(line[2]);
        totalScore += calculateRoundScore(matchResult, opponentShape);
    }

    return std::to_string(totalScore);
}

} // namespace aoc_2022_2