#include "AoC.hpp"

#include <iostream>

namespace utils::aoc {

void printPart1Solution(
    const std::string_view solution,
    const std::chrono::microseconds execTime)
{
    std::cout << "\n-----Part 1-----\n\nValue:\n"
              << solution << "\n\nExecution time:\n"
              << execTime.count() << " us" << std::endl;
}

void printPart2Solution(
    const std::string_view solution,
    const std::chrono::microseconds execTime)
{
    std::cout << "\n-----Part 2-----\n\nValue:\n"
              << solution << "\n\nExecution time:\n"
              << execTime.count() << " us" << std::endl;
}

} // namespace utils::aoc
