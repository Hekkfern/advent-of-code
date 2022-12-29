#include "solutions.hpp"
#include <utils/AocUtils.hpp>
#include <utils/TimeUtils.hpp>

int main()
{
    std::string solution1;
    auto part1ExecTime = utils::TimeUtils::calculateExecutionTime(
        [&solution1]() { solution1 = aoc_2021_01::solvePart1(); });
    utils::AocUtils::printPart1Solution(solution1, part1ExecTime);

    std::string solution2;
    auto part2ExecTime = utils::TimeUtils::calculateExecutionTime(
        [&solution2]() { solution2 = aoc_2021_01::solvePart2(); });
    utils::AocUtils::printPart2Solution(solution2, part2ExecTime);

    return 0;
}
