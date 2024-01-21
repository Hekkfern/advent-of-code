#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Direction2D.hpp>

using namespace utils::geometry2d;

TEST_CASE(
    "[Direction2D - constructor] Constructor initializes the value correctly",
    "[Direction2D, Direction2D_constructor]")
{
    Direction2D const direction2D{Direction2D::DownRight};
    REQUIRE(direction2D == Direction2D::DownRight);
}

TEST_CASE(
    "[Direction2D - toString] toString returns the correct value",
    "[Direction2D, Direction2D_toString]")
{
    Direction2D const d1{Direction2D::Up};
    CHECK(d1.toString() == "up");
    Direction2D const d2{Direction2D::Left};
    CHECK(d2.toString() == "left");
    Direction2D const d3{Direction2D::Down};
    CHECK(d3.toString() == "down");
    Direction2D const d4{Direction2D::Right};
    CHECK(d4.toString() == "right");
    Direction2D const d5{Direction2D::DownRight};
    CHECK(d5.toString() == "downright");
    Direction2D const d6{Direction2D::DownLeft};
    CHECK(d6.toString() == "downleft");
    Direction2D const d7{Direction2D::UpLeft};
    CHECK(d7.toString() == "upleft");
    Direction2D const d8{Direction2D::UpRight};
    CHECK(d8.toString() == "upright");
}

TEST_CASE(
    "[Direction2D - equality] Equality operators are correct",
    "[Direction2D, Direction2D_equality]")
{
    Direction2D const d1{Direction2D::Up};
    Direction2D const d2{Direction2D::Left};
    CHECK_FALSE(d1 == d2);
    CHECK(d1 != d2);
    Direction2D const d3{Direction2D::Up};
    CHECK(d1 == d3);
    CHECK_FALSE(d1 != d3);
}