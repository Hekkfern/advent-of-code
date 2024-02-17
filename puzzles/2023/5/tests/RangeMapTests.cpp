#include "../sources/RangeMap.hpp"
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

using namespace aoc_2023_5;

TEST_CASE("[RangeMap] Convert single key", "[2023][2023_5][RangeMap]")
{
    RangeMap rangeMap;
    SECTION("Empty map") { REQUIRE(rangeMap.convert(12LL) == 12LL); }
    SECTION("Non-empty map")
    {
        rangeMap.addSection(100, 20, 10);
        SECTION("Key is contained in the map")
        {
            REQUIRE(rangeMap.convert(27LL) == 107LL);
        }
        SECTION("Key is not contained in the map")
        {
            REQUIRE(rangeMap.convert(12LL) == 12LL);
        }
    }
}