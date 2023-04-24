#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Direction2D.hpp>

using namespace utils::geometry2d;

TEST_CASE(
    "[Direction2D - constructor] Constructor initializes the value correctly",
    "[Direction2D, Direction2D_constructor]")
{
    const Direction2D direction2D{Direction2D::DownRight};
    REQUIRE(direction2D == Direction2D::DownRight);
}

TEST_CASE(
    "[Direction2D - toString] toString returns the correct value",
    "[Direction2D, Direction2D_toString]")
{
    const Direction2D d1{Direction2D::Up};
    CHECK(d1.toString() == "up");
    const Direction2D d2{Direction2D::Left};
    CHECK(d2.toString() == "left");
    const Direction2D d3{Direction2D::Down};
    CHECK(d3.toString() == "down");
    const Direction2D d4{Direction2D::Right};
    CHECK(d4.toString() == "right");
    const Direction2D d5{Direction2D::DownRight};
    CHECK(d5.toString() == "downright");
    const Direction2D d6{Direction2D::DownLeft};
    CHECK(d6.toString() == "downleft");
    const Direction2D d7{Direction2D::UpLeft};
    CHECK(d7.toString() == "upleft");
    const Direction2D d8{Direction2D::UpRight};
    CHECK(d8.toString() == "upright");
}

TEST_CASE(
    "[Direction2D - equality] Equality operators are correct",
    "[Direction2D, Direction2D_equality]")
{
    const Direction2D d1{Direction2D::Up};
    const Direction2D d2{Direction2D::Left};
    CHECK_FALSE(d1 == d2);
    CHECK(d1 != d2);
    const Direction2D d3{Direction2D::Up};
    CHECK(d1 == d3);
    CHECK_FALSE(d1 != d3);
}