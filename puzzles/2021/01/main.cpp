#include "solutions.hpp"

#include <utils/AocUtils.hpp>
#include <string>

int main() {
    std::string solution1;
    solution1 = aoc_2021_01::solvePart1();
    utils::AocUtils::printPart1Solution(solution1);

    std::string solution2;
    solution2 = aoc_2021_01::solvePart2();
    utils::AocUtils::printPart1Solution(solution2);

    return 0;
}
