#pragma once

#include <chrono>
#include <string_view>

namespace utils::aoc {

void printPart1Solution(
    std::string_view solution, std::chrono::microseconds execTime);
void printPart2Solution(
    std::string_view solution, std::chrono::microseconds execTime);

} // namespace utils::aoc
