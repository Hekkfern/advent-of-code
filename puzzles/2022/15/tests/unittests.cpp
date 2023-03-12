//**********************************************************************
// GENERATED CODE - DO NOT MODIFY
//**********************************************************************

#include "../sources/solutions.hpp"
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/File.hpp>

TEST_CASE(
    "[2022_15] Use example input for Part 1",
    "[2022, 2022_15, part1, 2022_15_part1]")
{
    constexpr auto InputFile{ "input_test.txt" };
    constexpr int32_t GoalCoordY{ 10 };

    std::string mySolution = aoc_2022_15::solvePart1(
        InputFile, { { "GoalCoordY", GoalCoordY } });
    std::string expectedSolution = utils::file::readFirstLine(
                                       "solution1_test.txt")
                                       .value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2022_15] Use example input for Part 2",
    "[2022, 2022_15, part2, 2022_15_part2]")
{
    constexpr auto InputFile{ "input_test.txt" };

    std::string mySolution = aoc_2022_15::solvePart2(InputFile);
    std::string expectedSolution = utils::file::readFirstLine(
                                       "solution2_test.txt")
                                       .value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2022_15] Use real input for Part 1",
    "[2022, 2022_15, part1, 2022_15_part1]")
{
    constexpr auto InputFile{ "input.txt" };
    constexpr int32_t GoalCoordY{ 2000000 };

    std::string mySolution = aoc_2022_15::solvePart1(
        InputFile, { { "GoalCoordY", GoalCoordY } });
    std::string expectedSolution = utils::file::readFirstLine("solution1.txt")
                                       .value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2022_15] Use real input for Part 2",
    "[2022, 2022_15, part1, 2022_15_part2]")
{
    constexpr auto InputFile{ "input.txt" };

    std::string mySolution = aoc_2022_15::solvePart2(InputFile);
    std::string expectedSolution = utils::file::readFirstLine("solution2.txt")
                                       .value();

    REQUIRE(mySolution == expectedSolution);
}
