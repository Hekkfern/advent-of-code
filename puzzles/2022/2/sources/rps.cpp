#include "rps.h"

namespace aoc_2022_2 {

Shape convertStringToShape(char str)
{
    if (str == 'A' || str == 'X') {
        return Shape::Rock;
    } else if (str == 'B' || str == 'Y') {
        return Shape::Paper;
    } else if (str == 'C' || str == 'Z') {
        return Shape::Scissors;
    } else {
        throw std::invalid_argument("Invalid string.");
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

} // namespace aoc_2022_2