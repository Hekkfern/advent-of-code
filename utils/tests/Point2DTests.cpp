#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Point2D.hpp>

using namespace utils::geometry2d;

TEST_CASE(
    "[Point2D - getters] Getters return correct values with default "
    "constructor",
    "[Point2D, Point2D_getters]")
{
    const Point2D point2D;
    CHECK(point2D.getX() == 0);
    CHECK(point2D.getY() == 0);
    const auto coords{ point2D.get() };
    CHECK(coords.first == 0);
    CHECK(coords.second == 0);
}

TEST_CASE(
    "[Point2D - getters] Getters return correct values with parametrized "
    "constructor",
    "[Point2D, Point2D_getters]")
{
    const Point2D point2D{ 2, 3 };
    CHECK(point2D.getX() == 2);
    CHECK(point2D.getY() == 3);
    const auto coords{ point2D.get() };
    CHECK(coords.first == 2);
    CHECK(coords.second == 3);
}
