#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Direction2D.hpp>

using namespace utils::geometry2d;

TEST_CASE(
    "[Direction2D - constructor] Constructor initializes the value correctly",
    "[Direction2D]")
{
    Direction2D const direction2D{Direction2D::DownRight};
    REQUIRE(direction2D == Direction2D::DownRight);
}

TEST_CASE(
    "[Direction2D - toString] toString returns the correct value",
    "[Direction2D]")
{
    std::vector<std::pair<Direction2D, std::string>> const testCases{
        {Direction2D::Up, "up"},
        {Direction2D::Left, "left"},
        {Direction2D::Down, "down"},
        {Direction2D::Right, "right"},
        {Direction2D::UpLeft, "upleft"},
        {Direction2D::DownLeft, "downleft"},
        {Direction2D::DownRight, "downright"},
        {Direction2D::UpRight, "upright"}};

    for (auto const& [direction, expectedString] : testCases) {
        CHECK(direction.toString() == expectedString);
    }
}

TEST_CASE(
    "[Direction2D - equality] Equality operators are correct", "[Direction2D]")
{
    Direction2D const d1{Direction2D::Up};
    SECTION("Different")
    {
        Direction2D const d2{Direction2D::Left};
        CHECK_FALSE(d1 == d2);
        CHECK(d1 != d2);
    }
    SECTION("Equal")
    {
        Direction2D const d2{Direction2D::Up};
        CHECK(d1 == d2);
        CHECK_FALSE(d1 != d2);
    }
}
TEST_CASE(
    "[Direction2D - invert] Invert returns the correct value", "[Direction2D]")
{
    std::vector<std::pair<Direction2D, Direction2D>> const testCases{
        {Direction2D::Up, Direction2D::Down},
        {Direction2D::Left, Direction2D::Right},
        {Direction2D::Down, Direction2D::Up},
        {Direction2D::Right, Direction2D::Left},
        {Direction2D::UpLeft, Direction2D::DownRight},
        {Direction2D::DownLeft, Direction2D::UpRight},
        {Direction2D::UpRight, Direction2D::DownLeft},
        {Direction2D::DownRight, Direction2D::UpLeft}};

    for (auto const& [direction, expectedInverted] : testCases) {
        CHECK(direction.invert() == expectedInverted);
    }
}

TEST_CASE(
    "[Direction2D - turnLeft] turnLeft returns the correct value",
    "[Direction2D]")
{
    std::vector<std::pair<Direction2D, Direction2D>> const testCases{
        {Direction2D::Up, Direction2D::Left},
        {Direction2D::Left, Direction2D::Down},
        {Direction2D::Down, Direction2D::Right},
        {Direction2D::Right, Direction2D::Up},
        {Direction2D::UpLeft, Direction2D::DownLeft},
        {Direction2D::DownLeft, Direction2D::DownRight},
        {Direction2D::UpRight, Direction2D::UpLeft},
        {Direction2D::DownRight, Direction2D::UpRight}};

    for (auto const& [direction, expectedValue] : testCases) {
        CHECK(direction.turnLeft() == expectedValue);
    }
}

TEST_CASE(
    "[Direction2D - turnRight] turnRight returns the correct value",
    "[Direction2D]")
{
    std::vector<std::pair<Direction2D, Direction2D>> const testCases{
        {Direction2D::Up, Direction2D::Right},
        {Direction2D::Left, Direction2D::Up},
        {Direction2D::Down, Direction2D::Left},
        {Direction2D::Right, Direction2D::Down},
        {Direction2D::UpLeft, Direction2D::UpRight},
        {Direction2D::DownLeft, Direction2D::UpLeft},
        {Direction2D::UpRight, Direction2D::DownRight},
        {Direction2D::DownRight, Direction2D::DownLeft}};

    for (auto const& [direction, expectedValue] : testCases) {
        CHECK(direction.turnRight() == expectedValue);
    }
}

TEST_CASE(
    "[Direction2D - goStraight] goStraight returns the correct value",
    "[Direction2D]")
{
    std::vector<std::pair<Direction2D, Direction2D>> const testCases{
        {Direction2D::Up, Direction2D::Up},
        {Direction2D::Left, Direction2D::Left},
        {Direction2D::Down, Direction2D::Down},
        {Direction2D::Right, Direction2D::Right},
        {Direction2D::UpLeft, Direction2D::UpLeft},
        {Direction2D::DownLeft, Direction2D::DownLeft},
        {Direction2D::UpRight, Direction2D::UpRight},
        {Direction2D::DownRight, Direction2D::DownRight}};

    for (auto const& [direction, expectedValue] : testCases) {
        CHECK(direction.goStraight() == expectedValue);
    }
}