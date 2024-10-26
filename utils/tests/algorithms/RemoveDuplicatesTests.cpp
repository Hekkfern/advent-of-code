#define CATCH_CONFIG_MAIN
#include "utils/algorithms/RemoveDuplicates.hpp"
#include <catch.hpp>

TEST_CASE(
    "[Algorithms] remove_duplicates_without_reordering method",
    "[utils][Algorithms]")
{
    SECTION("Empty vector")
    {
        std::vector<int> data;
        std::vector<int> const expected;
        utils::algorithms::remove_duplicates_without_reordering(data);
        CHECK(data == expected);
    }
    SECTION("Vector without duplicates")
    {
        std::vector<int> data{1, 4, 75, 42, -3, 3, 74, 5, -5, 6, 41, 0, -9};
        std::vector<int> const expected{data};
        utils::algorithms::remove_duplicates_without_reordering(data);
        CHECK(data == expected);
    }
    SECTION("Vector with duplicates")
    {
        std::vector<int> data{
            1, 0, 4, 75, 42, -3, 3, 3, 74, 5, -5, 6, 41, 0, -9};
        std::vector<int> const expected{
            1, 0, 4, 75, 42, -3, 3, 74, 5, -5, 6, 41, -9};
        utils::algorithms::remove_duplicates_without_reordering(data);
        CHECK(data == expected);
    }
}
