//**********************************************************************
// GENERATED CODE - DO NOT MODIFY
//**********************************************************************

#include "../sources/solutions.hpp"
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <string>
#include <utils/File.hpp>

TEST_CASE(
    "[2023_8] Use example input A for Part 1",
    "[2023][2023_8][part1][2023_8_part1]")
{
    constexpr auto InputFile{"input1a_test.txt"};

    std::string const mySolution = aoc_2023_8::solvePart1(InputFile);
    std::string const expectedSolution
        = utils::file::readFirstLine("solution1a_test.txt").value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2023_8] Use example input B for Part 1",
    "[2023][2023_8][part1][2023_8_part1]")
{
    constexpr auto InputFile{"input1b_test.txt"};

    std::string const mySolution = aoc_2023_8::solvePart1(InputFile);
    std::string const expectedSolution
        = utils::file::readFirstLine("solution1b_test.txt").value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2023_8] Use example input for Part 2",
    "[2023][2023_8][part2][2023_8_part2]")
{
    constexpr auto InputFile{"input2_test.txt"};

    std::string const mySolution = aoc_2023_8::solvePart2(InputFile);
    std::string const expectedSolution
        = utils::file::readFirstLine("solution2_test.txt").value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2023_8] Use real input for Part 1", "[2023][2023_8][part1][2023_8_part1]")
{
    constexpr auto InputFile{"input.txt"};

    std::string const mySolution = aoc_2023_8::solvePart1(InputFile);
    std::string const expectedSolution
        = utils::file::readFirstLine("solution1.txt").value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2023_8] Use real input for Part 2", "[2023][2023_8][part1][2023_8_part2]")
{
    constexpr auto InputFile{"input.txt"};

    std::string const mySolution = aoc_2023_8::solvePart2(InputFile);
    std::string const expectedSolution
        = utils::file::readFirstLine("solution2.txt").value();

    REQUIRE(mySolution == expectedSolution);
}