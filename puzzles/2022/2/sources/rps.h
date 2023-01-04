#pragma once

#include <string_view>
#include <cstdint>

namespace aoc_2022_2 {

enum class Shape { Rock, Paper, Scissors };

enum class MatchResult { Lose, Draw, Win };

Shape convertStringToShape(char str);

uint32_t calculateRoundScore(Shape yourShape, Shape opponentShape);

MatchResult convertStringToMatchResult(char str);

uint32_t calculateRoundScore(MatchResult matchResult, Shape opponentShape);

} // namespace aoc_2022_2
