#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/Math.hpp>

using namespace utils::math;

TEST_CASE("[Math] modulusFloor() method", "[utils][Math]")
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

TEST_CASE("[Math] lcm() method", "[utils][Math]")
{
    SECTION("Two values") { REQUIRE(lcm(3, 6) == 6); }

    SECTION("More than two values") { REQUIRE(lcm(3, 6, 12, 36) == 36); }
}
