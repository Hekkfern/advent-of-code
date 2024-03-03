#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <range/v3/algorithm/find.hpp>
#include <utils/Combinations.hpp>

using namespace utils::combinations;

TEST_CASE(
    "[Combinations] calculateNumberCombinations() method",
    "[utils][Combinations]")
{
    CHECK(calculateNumberCombinations(9, 2) == 36);
}

TEST_CASE("[Combinations] forEachCombination() method", "[utils][Combinations]")
{
    std::vector<int> const numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<std::pair<int, int>> result;
    forEachCombination(
        numbers, 2, [&result](std::vector<int> const& combination) -> void {
            result.emplace_back(combination[0], combination[1]);
        });
    REQUIRE(result.size() == 36);
    CHECK(ranges::find(result, std::pair(1, 7)) != result.end());
    CHECK_FALSE(ranges::find(result, std::pair(7, 1)) != result.end());
    CHECK(ranges::find(result, std::pair(5, 9)) != result.end());
}
