#include "../sources/solutions.hpp"
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/FileUtils.hpp>

TEST_CASE(
    "[2022_1] Use example input for Part 1",
    "[2022, 2022_1, part1, 2022_1_part1]")
{
    constexpr auto InputFile{ "input_test.txt" };

    std::string mySolution = aoc_2022_1::solvePart1(InputFile);
    std::string expectedSolution = utils::FileUtils::readFirstLine(
                                       "solution1_test.txt")
                                       .value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2022_1] Use example input for Part 2",
    "[2022, 2022_1, part2, 2022_1_part2]")
{
    constexpr auto InputFile{ "input_test.txt" };

    std::string mySolution = aoc_2022_1::solvePart2(InputFile);
    std::string expectedSolution = utils::FileUtils::readFirstLine(
                                       "solution2_test.txt")
                                       .value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2022_1] Use real input for Part 1",
    "[2022, 2022_1, part1, 2022_1_part1]")
{
    constexpr auto InputFile{ "input.txt" };

    std::string mySolution = aoc_2022_1::solvePart1(InputFile);
    std::string expectedSolution = utils::FileUtils::readFirstLine(
                                       "solution1.txt")
                                       .value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2022_1] Use real input for Part 2",
    "[2022, 2022_1, part1, 2022_1_part2]")
{
    constexpr auto InputFile{ "input.txt" };

    std::string mySolution = aoc_2022_1::solvePart2(InputFile);
    std::string expectedSolution = utils::FileUtils::readFirstLine(
                                       "solution2.txt")
                                       .value();

    REQUIRE(mySolution == expectedSolution);
}