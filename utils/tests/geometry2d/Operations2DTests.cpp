#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Operations2D.hpp>

using namespace utils::geometry2d;

TEST_CASE(
    "[Operations2D] Move point towards a direction", "[utils][Operations2D]")
{
    const Point2D p1{3, -2};
    const Point2D<> p2{Operations2D<>::move(p1, Direction2D::UpRight)};
    CHECK(p2 == Point2D{4, -1});
}

TEST_CASE("[Operations2D] Move point by a vector", "[Operations2D]")
{
    const Point2D p1{3, -2};
    const Point2D<> p2{Operations2D<>::move(p1, Vector2D{-1, 4})};
    CHECK(p2 == Point2D{2, 2});
}

TEST_CASE("[Operations2D] Point2D + Vector2D", "[utils][Operations2D]")
{
    const Point2D point2D{4, 1};
    const Vector2D vector2D{2, 3};
    const auto newPoint2D{point2D + vector2D};
    CHECK(newPoint2D.getX() == 6);
    CHECK(newPoint2D.getY() == 4);
}

TEST_CASE("[Operations2D] Vector2D + Point2D", "[utils][Operations2D]")
{
    const Point2D point2D{4, 1};
    const Vector2D vector2D{2, 3};
    const auto newPoint2D{vector2D + point2D};
    CHECK(newPoint2D.getX() == 6);
    CHECK(newPoint2D.getY() == 4);
}

TEST_CASE(
    "[Operations2D] toVector2D returns the correct value",
    "[utils][Operations2D]")
{
    SECTION("Up")
    {
        const Vector2D v1{Operations2D<>::toVector2D(Direction2D::Up)};
        CHECK(v1 == Vector2D{0, 1});
    }
    SECTION("Left")
    {
        const Vector2D v1{Operations2D<>::toVector2D(Direction2D::Left)};
        CHECK(v1 == Vector2D{-1, 0});
    }
    SECTION("Down")
    {
        const Vector2D v1{Operations2D<>::toVector2D(Direction2D::Down)};
        CHECK(v1 == Vector2D{0, -1});
    }
    SECTION("Right")
    {
        const Vector2D v1{Operations2D<>::toVector2D(Direction2D::Right)};
        CHECK(v1 == Vector2D{1, 0});
    }
    SECTION("UpRight")
    {
        const Vector2D v1{Operations2D<>::toVector2D(Direction2D::UpRight)};
        CHECK(v1 == Vector2D{1, 1});
    }
    SECTION("UpLeft")
    {
        const Vector2D v1{Operations2D<>::toVector2D(Direction2D::UpLeft)};
        CHECK(v1 == Vector2D{-1, 1});
    }
    SECTION("DownRight")
    {
        const Vector2D v1{Operations2D<>::toVector2D(Direction2D::DownRight)};
        CHECK(v1 == Vector2D{1, -1});
    }
    SECTION("DownLeft")
    {
        const Vector2D v1{Operations2D<>::toVector2D(Direction2D::DownLeft)};
        CHECK(v1 == Vector2D{-1, -1});
    }
}