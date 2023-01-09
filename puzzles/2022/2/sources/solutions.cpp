#include "solutions.hpp"

#include <fstream>

namespace aoc_2022_2 {

#pragma region Private_Methods

enum class Shape { Rock, Paper, Scissors };

enum class MatchResult { Lose, Draw, Win };

Shape convertStringToShape(char str)
{
    if (str == 'A' || str == 'X') {
        return Shape::Rock;
    } else if (str == 'B' || str == 'Y') {
        return Shape::Paper;
    } else if (str == 'C' || str == 'Z') {
        return Shape::Scissors;
    } else {
        throw std::invalid_argument("Invalid character.");
    }
}

constexpr uint32_t PointsPerUsedRock{ 1U };
constexpr uint32_t PointsPerUsedPaper{ 2U };
constexpr uint32_t PointsPerUsedScissors{ 3U };

uint32_t calculatePointsOfUsedShape(const Shape yourShape)
{
    switch (yourShape) {
    case Shape::Rock:
        return PointsPerUsedRock;
    case Shape::Paper:
        return PointsPerUsedPaper;
    case Shape::Scissors:
        return PointsPerUsedScissors;
    default:
        throw std::invalid_argument("Invalid enum value.");
    }
}

constexpr uint32_t PointsPerLost{ 0U };
constexpr uint32_t PointsPerDraw{ 3U };
constexpr uint32_t PointsPerWin{ 6U };

uint32_t calculatePointsPerMatch(
    const Shape yourShape,
    const Shape opponentShape)
{
    if (yourShape == opponentShape) {
        return PointsPerDraw;
    } else if (
        (yourShape == Shape::Rock && opponentShape == Shape::Scissors)
        || (yourShape == Shape::Paper && opponentShape == Shape::Rock)
        || (yourShape == Shape::Scissors && opponentShape == Shape::Paper)) {
        return PointsPerWin;
    } else {
        return PointsPerLost;
    }
}

uint32_t calculateRoundScore(const Shape yourShape, const Shape opponentShape)
{
    return calculatePointsOfUsedShape(yourShape)
        + calculatePointsPerMatch(yourShape, opponentShape);
}

MatchResult convertStringToMatchResult(char str)
{
    if (str == 'X') {
        return MatchResult::Lose;
    } else if (str == 'Y') {
        return MatchResult::Draw;
    } else if (str == 'Z') {
        return MatchResult::Win;
    } else {
        throw std::invalid_argument("Invalid character.");
    }
}

Shape selectShapeBasedOnMatchResult(
    const MatchResult matchResult,
    const Shape opponentShape)
{
    switch (matchResult) {
    case MatchResult::Lose:
        switch (opponentShape) {
        case Shape::Rock:
            return Shape::Scissors;
        case Shape::Paper:
            return Shape::Rock;
        case Shape::Scissors:
            return Shape::Paper;
        default:
            throw std::invalid_argument("Invalid enum.");
        }
    case MatchResult::Draw:
        return opponentShape;
    case MatchResult::Win:
        switch (opponentShape) {
        case Shape::Rock:
            return Shape::Paper;
        case Shape::Paper:
            return Shape::Scissors;
        case Shape::Scissors:
            return Shape::Rock;
        default:
            throw std::invalid_argument("Invalid enum.");
        }
    default:
        throw std::invalid_argument("Invalid enum.");
    }
}

uint32_t calculateRoundScore(
    const MatchResult matchResult,
    const Shape opponentShape)
{
    const Shape yourShape = selectShapeBasedOnMatchResult(
        matchResult, opponentShape);
    return calculateRoundScore(yourShape, opponentShape);
}

#pragma endregion Private_Methods

#pragma region Public_Methods

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

#pragma endregion Public_Methods

} // namespace aoc_2022_2