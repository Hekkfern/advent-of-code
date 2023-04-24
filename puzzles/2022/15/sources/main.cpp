//**********************************************************************
// GENERATED CODE - DO NOT MODIFY
//**********************************************************************

#include "solutions.hpp"
#include <utils/AoC.hpp>
#include <utils/Time.hpp>

int main()
{
    const std::string inputFile{"input.txt"};
    constexpr int32_t GoalCoordY{2000000};

    std::string solution1;
    auto const part1ExecTime = utils::time::calculateExecutionTime(
        [&solution1, &inputFile, GoalCoordY]() {
            solution1 = aoc_2022_15::solvePart1(
                inputFile, {{"GoalCoordY", GoalCoordY}});
        });
    utils::aoc::printPart1Solution(solution1, part1ExecTime);

    constexpr uint32_t GridSize{4000000U};

    std::string solution2;
    auto const part2ExecTime = utils::time::calculateExecutionTime(
        [&solution2, &inputFile, GridSize]() {
            solution2 = aoc_2022_15::solvePart2(
                inputFile, {{"GridSize", GridSize}});
        });
    utils::aoc::printPart2Solution(solution2, part2ExecTime);

    return EXIT_SUCCESS;
}
