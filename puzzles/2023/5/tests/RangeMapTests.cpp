#include "../sources/RangeMap.hpp"
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

using namespace aoc_2023_5;
using namespace utils::interval;

TEST_CASE("[RangeMap] Convert single key", "[2023][2023_5][RangeMap]")
{
    RangeMap rangeMap;
    SECTION("Empty map") { CHECK(rangeMap.convert(12LL) == 12LL); }
    SECTION("Map with one single item")
    {
        rangeMap.addSection(100, 20, 10);
        SECTION("Key is contained in the map")
        {
            CHECK(rangeMap.convert(27LL) == 107LL);
        }
        SECTION("Key is not contained in the map")
        {
            CHECK(rangeMap.convert(12LL) == 12LL);
        }
    }
    SECTION("Map with multiple items")
    {
        rangeMap.addSection(100, 20, 10);
        rangeMap.addSection(55, 35, 10);
        SECTION("Key is contained in the map")
        {
            CHECK(rangeMap.convert(27LL) == 107LL);
            CHECK(rangeMap.convert(36LL) == 56LL);
        }
        SECTION("Key is not contained in the map")
        {
            CHECK(rangeMap.convert(12LL) == 12LL);
        }
    }
}

TEST_CASE("[RangeMap] Convert interval key", "[2023][2023_5][RangeMap]")
{
    RangeMap rangeMap;
    SECTION("Empty map") { CHECK(rangeMap.convert(12LL) == 12LL); }
    SECTION("Map with one single item")
    {
        rangeMap.addSection(100, 20, 10);
        SECTION("Key is contained in the map")
        {
            auto const result{rangeMap.convert(Interval{27LL, 28LL})};
            REQUIRE(result.get().size() == 1);
            CHECK(result.get()[0] == Interval{107LL, 108LL});
        }
        SECTION("Key is not contained in the map")
        {
            auto const result{rangeMap.convert(Interval{12LL, 13LL})};
            REQUIRE(result.get().size() == 1);
            CHECK(result.get()[0] == Interval{12LL, 13LL});
        }
        SECTION("Key is semi-contained (left) in the map")
        {
            auto const result{rangeMap.convert(Interval{18LL, 22LL})};
            REQUIRE(result.get().size() == 2);
            CHECK(result.get()[0] == Interval{18LL, 19LL});
            CHECK(result.get()[1] == Interval{100LL, 102LL});
        }
        SECTION("Key is semi-contained (right) in the map")
        {
            auto const result{rangeMap.convert(Interval{28LL, 33LL})};
            REQUIRE(result.get().size() == 2);
            CHECK(result.get()[0] == Interval{108LL, 110LL});
            CHECK(result.get()[1] == Interval{31LL, 32LL});
        }
    }
    SECTION("Map with multiple items")
    {
        rangeMap.addSection(100, 20, 10);
        rangeMap.addSection(55, 35, 10);
        SECTION("Key is contained in the map")
        {
            SECTION("In first range")
            {
                auto const result{rangeMap.convert(Interval{27LL, 28LL})};
                REQUIRE(result.get().size() == 1);
                CHECK(result.get()[0] == Interval{107LL, 108LL});
            }
            SECTION("In second range")
            {
                auto const result{rangeMap.convert(Interval{36LL, 37LL})};
                REQUIRE(result.get().size() == 1);
                CHECK(result.get()[0] == Interval{56LL, 57LL});
            }
        }
        SECTION("Key is not contained in the map")
        {
            auto const result{rangeMap.convert(Interval{12LL, 13LL})};
            REQUIRE(result.get().size() == 1);
            CHECK(result.get()[0] == Interval{12LL, 13LL});
        }
    }
}