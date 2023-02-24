//**********************************************************************
// GENERATED CODE - DO NOT MODIFY
//**********************************************************************

#include "solutions.hpp"
#include <utils/AoC.hpp>
#include <utils/Time.hpp>

int main()
{
    const std::string inputFile{ "input.txt" };

    std::string solution1;
    const auto part1ExecTime = utils::time::calculateExecutionTime(
        [&solution1, &inputFile]() {
            solution1 = aoc_2022_14::solvePart1(inputFile);
        });
    utils::aoc::printPart1Solution(solution1, part1ExecTime);

    std::string solution2;
    const auto part2ExecTime = utils::time::calculateExecutionTime(
        [&solution2, &inputFile]() {
            solution2 = aoc_2022_14::solvePart2(inputFile);
        });
    utils::aoc::printPart2Solution(solution2, part2ExecTime);

    return EXIT_SUCCESS;
}
