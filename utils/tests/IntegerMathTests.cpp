#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/IntegerMath.hpp>

using namespace utils::integermath;

TEST_CASE("[IntegerMath] modulusFloor() method", "[utils][IntegerMath]")
{
    SECTION("Run-time")
    {
        REQUIRE(modulusFloor(4, 3) == 1);
        REQUIRE(modulusFloor(3, 3) == 0);
        REQUIRE(modulusFloor(2, 3) == 2);
        REQUIRE(modulusFloor(1, 3) == 1);
        REQUIRE(modulusFloor(0, 3) == 0);
        REQUIRE(modulusFloor(-1, 3) == 2);
        REQUIRE(modulusFloor(-2, 3) == 1);
        REQUIRE(modulusFloor(-3, 3) == 0);
        REQUIRE(modulusFloor(-4, 3) == 2);
    }
    SECTION("Compile-time")
    {
        STATIC_REQUIRE(modulusFloor(4, 3) == 1);
        STATIC_REQUIRE(modulusFloor(3, 3) == 0);
        STATIC_REQUIRE(modulusFloor(2, 3) == 2);
        STATIC_REQUIRE(modulusFloor(1, 3) == 1);
        STATIC_REQUIRE(modulusFloor(0, 3) == 0);
        STATIC_REQUIRE(modulusFloor(-1, 3) == 2);
        STATIC_REQUIRE(modulusFloor(-2, 3) == 1);
        STATIC_REQUIRE(modulusFloor(-3, 3) == 0);
        STATIC_REQUIRE(modulusFloor(-4, 3) == 2);
    }
}
