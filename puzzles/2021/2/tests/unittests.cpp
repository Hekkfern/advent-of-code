//**********************************************************************
// GENERATED CODE - DO NOT MODIFY
//**********************************************************************

#include "../sources/solutions.hpp"
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/FileUtils.hpp>

TEST_CASE(
    "[2021_2] Use example input for Part 1",
    "[2021, 2021_2, part1, 2021_2_part1]")
{
    constexpr auto InputFile{ "input_test.txt" };

    std::string mySolution = aoc_2021_2::solvePart1(InputFile);
    std::string expectedSolution = utils::FileUtils::readFirstLine(
                                       "solution1_test.txt")
                                       .value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2021_2] Use example input for Part 2",
    "[2021, 2021_2, part2, 2021_2_part2]")
{
    constexpr auto InputFile{ "input_test.txt" };

    std::string mySolution = aoc_2021_2::solvePart2(InputFile);
    std::string expectedSolution = utils::FileUtils::readFirstLine(
                                       "solution2_test.txt")
                                       .value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2021_2] Use real input for Part 1",
    "[2021, 2021_2, part1, 2021_2_part1]")
{
    constexpr auto InputFile{ "input.txt" };

    std::string mySolution = aoc_2021_2::solvePart1(InputFile);
    std::string expectedSolution = utils::FileUtils::readFirstLine(
                                       "solution1.txt")
                                       .value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2021_2] Use real input for Part 2",
    "[2021, 2021_2, part1, 2021_2_part2]")
{
    constexpr auto InputFile{ "input.txt" };

    std::string mySolution = aoc_2021_2::solvePart2(InputFile);
    std::string expectedSolution = utils::FileUtils::readFirstLine(
                                       "solution2.txt")
                                       .value();

    REQUIRE(mySolution == expectedSolution);
}