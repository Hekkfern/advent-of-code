#include "solutions.hpp"

#include <fstream>
#include <unordered_map>

namespace aoc_2022_2 {

// ---------- Private Methods ----------

// A hash function used to hash a pair of any kind
struct HashPair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto hash1{ std::hash<T1>{}(p.first) };
        auto hash2{ std::hash<T2>{}(p.second) };

        if (hash1 != hash2) {
            return hash1 ^ hash2;
        }

        // If hash1 == hash2, their XOR is zero.
        return hash1;
    }
};

constexpr uint32_t PointsPerUsedRock{ 1U };
constexpr uint32_t PointsPerUsedPaper{ 2U };
constexpr uint32_t PointsPerUsedScissors{ 3U };
constexpr uint32_t PointsPerLost{ 0U };
constexpr uint32_t PointsPerDraw{ 3U };
constexpr uint32_t PointsPerWin{ 6U };

constexpr char OpponentRock{ 'A' };
constexpr char OpponentPaper{ 'B' };
constexpr char OpponentScissors{ 'C' };
constexpr char PlayerRock{ 'X' };
constexpr char PlayerPaper{ 'Y' };
constexpr char PlayerScissors{ 'Z' };
constexpr char MatchLost{ 'X' };
constexpr char MatchDraw{ 'Y' };
constexpr char MatchWin{ 'Z' };

std::unordered_map<std::pair<char, char>, uint32_t, HashPair> PointsPerShapes{
    { { OpponentRock, PlayerRock }, PointsPerUsedRock + PointsPerDraw },
    { { OpponentRock, PlayerPaper }, PointsPerUsedPaper + PointsPerWin },
    { { OpponentRock, PlayerScissors }, PointsPerUsedScissors + PointsPerLost },
    { { OpponentPaper, PlayerRock }, PointsPerUsedRock + PointsPerLost },
    { { OpponentPaper, PlayerPaper }, PointsPerUsedPaper + PointsPerDraw },
    { { OpponentPaper, PlayerScissors }, PointsPerUsedScissors + PointsPerWin },
    { { OpponentScissors, PlayerRock }, PointsPerUsedRock + PointsPerWin },
    { { OpponentScissors, PlayerPaper }, PointsPerUsedPaper + PointsPerLost },
    { { OpponentScissors, PlayerScissors },
      PointsPerUsedScissors + PointsPerDraw }
};

/**
 * @brief Look-up table which links the opponent shape and the result of the match, to the shape that the player must use to reach the said result.
 */
std::unordered_map<std::pair<char, char>, char, HashPair> ResultConversion{
    { { OpponentRock, MatchLost }, PlayerScissors },
    { { OpponentRock, MatchDraw }, PlayerRock },
    { { OpponentRock, MatchWin }, PlayerPaper },
    { { OpponentPaper, MatchLost }, PlayerRock },
    { { OpponentPaper, MatchDraw }, PlayerPaper },
    { { OpponentPaper, MatchWin }, PlayerScissors },
    { { OpponentScissors, MatchLost }, PlayerPaper },
    { { OpponentScissors, MatchDraw }, PlayerScissors },
    { { OpponentScissors, MatchWin }, PlayerRock }
};

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
uint32_t calculateRoundScoreFromShapes(
    const char yourShape,
    const char opponentShape)
{
    return PointsPerShapes.at(std::make_pair(opponentShape, yourShape));
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
uint32_t calculateRoundScoreFromResult(
    const char matchResult,
    const char opponentShape)
{
    return PointsPerShapes.at(std::make_pair(
        opponentShape,
        ResultConversion.at(std::make_pair(opponentShape, matchResult))));
}

// ---------- End of Private Methods ----------

// ---------- End of Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    std::ifstream stream{ filename };
    std::string line;
    uint32_t totalScore{ 0U };

    while (std::getline(stream, line)) {
        totalScore += calculateRoundScoreFromShapes(line[2], line[0]);
    }

    return std::to_string(totalScore);
}

std::string solvePart2(const std::string& filename)
{
    std::ifstream stream{ filename };
    std::string line;
    uint32_t totalScore{ 0U };

    while (std::getline(stream, line)) {
        totalScore += calculateRoundScoreFromResult(line[2], line[0]);
    }

    return std::to_string(totalScore);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_2
