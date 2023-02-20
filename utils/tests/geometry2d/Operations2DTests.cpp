#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Operations2D.hpp>
#include <utils/geometry2d/Point2D.hpp>
#include <utils/geometry2d/Vector2D.hpp>

using namespace utils::geometry2d;

TEST_CASE(
    "[Operations2D] Point2D + Vector2D",
    "[Operations2D, Operations2D_point2d]")
{
    const Point2D point2D{ 4, 1 };
    const Vector2D vector2D{ 2, 3 };
    const auto newPoint2D{ point2D + vector2D };
    CHECK(newPoint2D.getX() == 6);
    CHECK(newPoint2D.getY() == 4);
}

TEST_CASE(
    "[Operations2D] Vector2D + Point2D",
    "[Operations2D, Operations2D_point2d]")
{
    const Point2D point2D{ 4, 1 };
    const Vector2D vector2D{ 2, 3 };
    const auto newPoint2D{ vector2D + point2D };
    CHECK(newPoint2D.getX() == 6);
    CHECK(newPoint2D.getY() == 4);
}

TEST_CASE(
    "[Operations2D] Vector2D * scalar",
    "[Operations2D, Operations2D_vector2d]")
{
    const Vector2D vector2D{ 2, 3 };
    const auto newVector2D{ vector2D * 2 };
    CHECK(newVector2D.getX() == 4);
    CHECK(newVector2D.getY() == 6);
}

TEST_CASE(
    "[Operations2D] scalar * Vector2D",
    "[Operations2D, Operations2D_vector2d]")
{
    const Vector2D vector2D{ 2, 3 };
    const auto newVector2D{ 2 * vector2D };
    CHECK(newVector2D.getX() == 4);
    CHECK(newVector2D.getY() == 6);
}