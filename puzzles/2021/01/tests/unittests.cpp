#include "../sources/solutions.hpp"
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/FileUtils.hpp>

TEST_CASE("[2021_01] Use example input", "[2021, 2021_01]")
{
    constexpr auto inputFile {"input_test.txt"};

    std::string mySolution = aoc_2021_01::solvePart1(inputFile);
    std::string expectedSolution = utils::FileUtils::readFirstLine("solution_test.txt").value();

    REQUIRE(mySolution == expectedSolution);
}
