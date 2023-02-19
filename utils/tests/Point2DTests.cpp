#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Point2D.hpp>

using namespace utils::geometry2d;

TEST_CASE("[Point2D - getters] Works OK", "[Point2D, Point2D_getters]")
{
    const Point2D point2D{ 2, 3 };
    CHECK(point2D.getX() == 2);
    CHECK(point2D.getY() == 3);
    const auto coords{ point2D.get() };
    CHECK(coords.first == 2);
    CHECK(coords.second == 3);
}
