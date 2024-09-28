//**********************************************************************
// GENERATED CODE - DO NOT MODIFY
//**********************************************************************

#include "../sources/solutions.hpp"
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <string>
#include <utils/File.hpp>

TEST_CASE(
    "[2023_18] Use example input for Part 1",
    "[2023][2023_18][part1][2023_18_part1]")
{
    constexpr auto InputFile{"input1_test.txt"};

    std::string const mySolution = aoc_2023_18::solvePart1(InputFile);
    std::string const expectedSolution
        = utils::file::readFirstLine("solution1_test.txt").value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2023_18] Use example input for Part 2",
    "[2023][2023_18][part2][2023_18_part2]")
{
    constexpr auto InputFile{"input2_test.txt"};

    std::string const mySolution = aoc_2023_18::solvePart2(InputFile);
    std::string const expectedSolution
        = utils::file::readFirstLine("solution2_test.txt").value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2023_18] Use real input for Part 1",
    "[2023][2023_18][part1][2023_18_part1]")
{
    constexpr auto InputFile{"input.txt"};

    std::string const mySolution = aoc_2023_18::solvePart1(InputFile);
    std::string const expectedSolution
        = utils::file::readFirstLine("solution1.txt").value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2023_18] Use real input for Part 2",
    "[2023][2023_18][part1][2023_18_part2]")
{
    constexpr auto InputFile{"input.txt"};

    std::string const mySolution = aoc_2023_18::solvePart2(InputFile);
    std::string const expectedSolution
        = utils::file::readFirstLine("solution2.txt").value();

    REQUIRE(mySolution == expectedSolution);
}