#include "../sources/solutions.hpp"
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/FileUtils.hpp>

TEST_CASE(
    "[2021_01] Use example input for Part 1",
    "[2021, 2021_01, part1, 2021_01_part1]")
{
    constexpr auto inputFile{ "input_test.txt" };

    std::string mySolution = aoc_2021_01::solvePart1(inputFile);
    std::string expectedSolution = utils::FileUtils::readFirstLine(
                                       "solution1_test.txt")
                                       .value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2021_01] Use example input for Part 2",
    "[2021, 2021_01, part2, 2021_01_part2]")
{
    constexpr auto inputFile{ "input_test.txt" };

    std::string mySolution = aoc_2021_01::solvePart2(inputFile);
    std::string expectedSolution = utils::FileUtils::readFirstLine(
                                       "solution2_test.txt")
                                       .value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2021_01] Use real input for Part 1",
    "[2021, 2021_01, part1, 2021_01_part1]")
{
    constexpr auto inputFile{ "input.txt" };

    std::string mySolution = aoc_2021_01::solvePart1(inputFile);
    std::string expectedSolution = utils::FileUtils::readFirstLine(
                                       "solution1.txt")
                                       .value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2021_01] Use real input for Part 2",
    "[2021, 2021_01, part1, 2021_01_part2]")
{
    constexpr auto inputFile{ "input.txt" };

    std::string mySolution = aoc_2021_01::solvePart2(inputFile);
    std::string expectedSolution = utils::FileUtils::readFirstLine(
                                       "solution2.txt")
                                       .value();

    REQUIRE(mySolution == expectedSolution);
}
