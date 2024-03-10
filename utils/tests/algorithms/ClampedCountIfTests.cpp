#define CATCH_CONFIG_MAIN
#include "utils/algorithms/ClampedCountIf.hpp"
#include <catch.hpp>

TEST_CASE("[Algorithms] count_if_until method", "[utils][Algorithms]")
{
    std::vector<int> data{1, 4, 75, 42, -3, 3, 3, 74, 5, -5, 6, 41, 0, -9};

    SECTION("With iterators")
    {
        SECTION("Reach limit")
        {
            auto result{utils::algorithms::clamped_count_if(
                data.begin(), data.end(), 2, [](int const item) -> bool {
                    return item < 10;
                })};
            CHECK(result == 2);
        }
        SECTION("Not reach limit")
        {
            auto result{utils::algorithms::clamped_count_if(
                data.begin(), data.end(), 1000, [](int const item) -> bool {
                    return item < 10;
                })};
            CHECK(result == 10);
        }
    }
    SECTION("With ranges")
    {
        SECTION("Reach limit")
        {
            auto result{utils::algorithms::clamped_count_if(
                data, 2, [](int const item) -> bool { return item < 10; })};
            CHECK(result == 2);
        }
        SECTION("Not reach limit")
        {
            auto result{utils::algorithms::clamped_count_if(
                data, 1000, [](int const item) -> bool { return item < 10; })};
            CHECK(result == 10);
        }
    }
}
