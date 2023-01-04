#include "solutions.hpp"
#include <utils/AocUtils.hpp>
#include <utils/TimeUtils.hpp>

int main()
{
    const std::string inputFile{ "input.txt" };

    std::string solution1;
    const auto part1ExecTime = utils::TimeUtils::calculateExecutionTime(
        [&solution1, &inputFile]() {
            solution1 = aoc_2022_2::solvePart1(inputFile);
        });
    utils::AocUtils::printPart1Solution(solution1, part1ExecTime);

    std::string solution2;
    const auto part2ExecTime = utils::TimeUtils::calculateExecutionTime(
        [&solution2, &inputFile]() {
            solution2 = aoc_2022_2::solvePart2(inputFile);
        });
    utils::AocUtils::printPart2Solution(solution2, part2ExecTime);

    return EXIT_SUCCESS;
}