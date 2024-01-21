#include "AoC.hpp"

#include <iostream>

namespace utils::aoc {

void printPart1Solution(
    std::string_view const solution, std::chrono::microseconds const execTime)
{
    std::cout
        << "\n-----Part 1-----\n\nValue:\n"
        << solution << "\n\nExecution time:\n"
        << execTime.count() << " us" << std::endl;
}

void printPart2Solution(
    std::string_view const solution, std::chrono::microseconds const execTime)
{
    std::cout
        << "\n-----Part 2-----\n\nValue:\n"
        << solution << "\n\nExecution time:\n"
        << execTime.count() << " us" << std::endl;
}

} // namespace utils::aoc
