#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/Combinations.hpp>

using namespace utils::combinations;

TEST_CASE(
    "[Combinations] calculateNumberCombinations() method",
    "[utils][Combinations]")
{
    CHECK(calculateNumberCombinations(9, 2) == 36);
}
