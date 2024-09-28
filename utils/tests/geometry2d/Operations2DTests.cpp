#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Operations2D.hpp>

using namespace utils::geometry2d;

TEST_CASE(
    "[Operations2D] Move point towards a direction", "[utils][Operations2D]")
{
    Point2D<> const p1{3, -2};
    Point2D<> const p2{move(p1, Direction2D::UpRight)};
    CHECK(p2 == Point2D{4, -1});
}

TEST_CASE("[Operations2D] Move point by a vector", "[Operations2D]")
{
    Point2D<> const p1{3, -2};
    Point2D<> const p2{move(p1, Vector2D{-1, 4})};
    CHECK(p2 == Point2D{2, 2});
}

TEST_CASE("[Operations2D] Point2D + Vector2D", "[utils][Operations2D]")
{
    Point2D<> const point2D{4, 1};
    Vector2D<> const vector2D{2, 3};
    auto const newPoint2D{point2D + vector2D};
    CHECK(newPoint2D.getX() == 6);
    CHECK(newPoint2D.getY() == 4);
}

TEST_CASE("[Operations2D] Vector2D + Point2D", "[utils][Operations2D]")
{
    Point2D<> const point2D{4, 1};
    Vector2D<> const vector2D{2, 3};
    auto const newPoint2D{vector2D + point2D};
    CHECK(newPoint2D.getX() == 6);
    CHECK(newPoint2D.getY() == 4);
}

TEST_CASE("[Operations2D] Point2D += Vector2D", "[utils][Operations2D]")
{
    Point2D<> point2D{4, 1};
    Vector2D<> const vector2D{2, 3};
    point2D += vector2D;
    CHECK(point2D.getX() == 6);
    CHECK(point2D.getY() == 4);
}

TEST_CASE("[Operations2D] toVector2D() method", "[utils][Operations2D]")
{
    SECTION("Up")
    {
        Vector2D<> const v1{toVector2D(Direction2D::Up)};
        CHECK(v1 == Vector2D{0, 1});
    }
    SECTION("Left")
    {
        Vector2D<> const v1{toVector2D(Direction2D::Left)};
        CHECK(v1 == Vector2D{-1, 0});
    }
    SECTION("Down")
    {
        Vector2D<> const v1{toVector2D(Direction2D::Down)};
        CHECK(v1 == Vector2D{0, -1});
    }
    SECTION("Right")
    {
        Vector2D<> const v1{toVector2D(Direction2D::Right)};
        CHECK(v1 == Vector2D{1, 0});
    }
    SECTION("UpRight")
    {
        Vector2D<> const v1{toVector2D(Direction2D::UpRight)};
        CHECK(v1 == Vector2D{1, 1});
    }
    SECTION("UpLeft")
    {
        Vector2D<> const v1{toVector2D(Direction2D::UpLeft)};
        CHECK(v1 == Vector2D{-1, 1});
    }
    SECTION("DownRight")
    {
        Vector2D<> const v1{toVector2D(Direction2D::DownRight)};
        CHECK(v1 == Vector2D{1, -1});
    }
    SECTION("DownLeft")
    {
        Vector2D<> const v1{toVector2D(Direction2D::DownLeft)};
        CHECK(v1 == Vector2D{-1, -1});
    }
}
