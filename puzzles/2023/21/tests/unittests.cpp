//**********************************************************************
// GENERATED CODE - DO NOT MODIFY
//**********************************************************************

#include "../sources/solutions.hpp"
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <string>
#include <utils/File.hpp>

TEST_CASE(
    "[2023_21] Use example input for Part 1",
    "[2023][2023_21][part1][2023_21_part1]")
{
    constexpr auto InputFile{"input1_test.txt"};

    constexpr uint32_t MaxSteps{6};
    std::string const mySolution = aoc_2023_21::solvePart1(InputFile, MaxSteps);
    std::string const expectedSolution
        = utils::file::readFirstLine("solution1_test.txt").value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2023_21] Use real input for Part 1",
    "[2023][2023_21][part1][2023_21_part1]")
{
    constexpr auto InputFile{"input.txt"};

    constexpr uint32_t MaxSteps{64};
    std::string const mySolution = aoc_2023_21::solvePart1(InputFile, MaxSteps);
    std::string const expectedSolution
        = utils::file::readFirstLine("solution1.txt").value();

    REQUIRE(mySolution == expectedSolution);
}

TEST_CASE(
    "[2023_21] Use real input for Part 2",
    "[2023][2023_21][part1][2023_21_part2]")
{
    constexpr auto InputFile{"input.txt"};

    constexpr uint32_t MaxSteps{26501365};
    std::string const mySolution = aoc_2023_21::solvePart2(InputFile, MaxSteps);
    std::string const expectedSolution
        = utils::file::readFirstLine("solution2.txt").value();

    REQUIRE(mySolution == expectedSolution);
}