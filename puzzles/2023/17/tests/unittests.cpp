//**********************************************************************
// GENERATED CODE - DO NOT MODIFY
//**********************************************************************

#include "../sources/solutions.hpp"
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <string>
#include <utils/File.hpp>

TEST_CASE(
    "[2023_17] Use example input for Part 1",
    "[2023][2023_17][part1][2023_17_part1]")
{
    constexpr auto InputFile{"input1_test.txt"};

    std::string const mySolution = aoc_2023_17::solvePart1(InputFile);
    std::string const expectedSolution
        = utils::file::readFirstLine("solution1_test.txt").value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2023_17] Use example input A for Part 2",
    "[2023][2023_17][part2][2023_17_part2]")
{
    constexpr auto InputFile{"input2a_test.txt"};

    std::string const mySolution = aoc_2023_17::solvePart2(InputFile);
    std::string const expectedSolution
        = utils::file::readFirstLine("solution2a_test.txt").value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2023_17] Use example input B for Part 2",
    "[2023][2023_17][part2][2023_17_part2]")
{
    constexpr auto InputFile{"input2b_test.txt"};

    std::string const mySolution = aoc_2023_17::solvePart2(InputFile);
    std::string const expectedSolution
        = utils::file::readFirstLine("solution2b_test.txt").value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2023_17] Use real input for Part 1",
    "[2023][2023_17][part1][2023_17_part1]")
{
    constexpr auto InputFile{"input.txt"};

    std::string const mySolution = aoc_2023_17::solvePart1(InputFile);
    std::string const expectedSolution
        = utils::file::readFirstLine("solution1.txt").value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2023_17] Use real input for Part 2",
    "[2023][2023_17][part1][2023_17_part2]")
{
    constexpr auto InputFile{"input.txt"};

    std::string const mySolution = aoc_2023_17::solvePart2(InputFile);
    std::string const expectedSolution
        = utils::file::readFirstLine("solution2.txt").value();

    REQUIRE(mySolution == expectedSolution);
}