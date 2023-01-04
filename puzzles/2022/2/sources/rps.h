#pragma once

#include <stdexcept>
#include <string_view>

namespace aoc_2022_2 {

enum class Shape { Rock, Paper, Scissors };

Shape convertStringToShape(char str);

uint32_t calculateRoundScore(Shape yourShape, Shape opponentShape);

} // namespace aoc_2022_2
