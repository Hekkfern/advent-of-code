#include "solutions.hpp"

#include <fstream>

namespace aoc_2022_2 {

#pragma region Private_Methods

/**
 * @brief      This class describes a shape.
 */
enum class Shape { Rock, Paper, Scissors };

/**
 * @brief      This class describes a match result.
 */
enum class MatchResult { Lose, Draw, Win };

/**
 * @brief      Converts a shape character into its correcponding enum value.
 *
 * @param[in]  str   Character to convert to.
 *
 * @return     Enum value corresponding to the converted character.
 */
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

/**
 * @brief      Calculates the points earned by uing a shape in a match.
 *
 * @param[in]  yourShape  The shape you use during the match.
 *
 * @return     The points earned.
 */
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

/**
 * @brief      Calculates the points earned as the result of the match.
 *
 * @param[in]  yourShape      The shape you use during the match.
 * @param[in]  opponentShape  The shape your opponent uses during the match.
 *
 * @return     The points earned.
 */
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

/**
 * @brief      Calculates the total round score, as result of adding the points
 *             earned because of the used shaped as well as the points earned
 *             because of the result of the match.
 *
 * @param[in]  yourShape      The shape you use during the match.
 * @param[in]  opponentShape  The shape your opponent uses during the match.
 *
 * @return     The total points of the round.
 */
uint32_t calculateRoundScore(const Shape yourShape, const Shape opponentShape)
{
    return calculatePointsOfUsedShape(yourShape)
        + calculatePointsPerMatch(yourShape, opponentShape);
}

/**
 * @brief      Converts a match result character into its correcponding enum
 *             value.
 *
 * @param[in]  str   Character to convert to.
 *
 * @return     Enum value corresponding to the converted character.
 */
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

/**
 * @brief      Determines the shape you should use in order to achieve the
 *             selected result during the match.
 *
 * @param[in]  matchResult    The match result to achieve.
 * @param[in]  opponentShape  The shape your opponent uses during the match.
 *
 * @return     The shape you should use.
 */
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

/**
 * @brief      Calculates the total round score, as result of adding the points
 *             earned because of the used shaped as well as the points earned
 *             because of the result of the match.
 *
 * @param[in]  matchResult    The match result to achieve.
 * @param[in]  opponentShape  The shape your opponent uses during the match.
 *
 * @return     The total points of the round.
 */
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