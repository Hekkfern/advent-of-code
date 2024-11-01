#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry3d/Operations3D.hpp>

using namespace utils::geometry3d;

TEST_CASE(
    "[Operations3D] Move point towards a direction", "[utils][Operations3D]")
{
    Point3D<> const p1{3, -2};
    Point3D<> const p2{move(p1, Direction3D::UpRight)};
    CHECK(p2 == Point3D{4, -1});
}

TEST_CASE("[Operations3D] Move point by a vector", "[Operations3D]")
{
    Point3D<> const p1{3, -2};
    Point3D<> const p2{move(p1, Vector3D{-1, 4})};
    CHECK(p2 == Point3D{2, 2});
}

TEST_CASE("[Operations3D] Point3D + Vector3D", "[utils][Operations3D]")
{
    Point3D<> const point3D{4, 1};
    Vector3D<> const vector3D{2, 3};
    auto const newPoint3D{point3D + vector3D};
    CHECK(newPoint3D.getX() == 6);
    CHECK(newPoint3D.getY() == 4);
}

TEST_CASE("[Operations3D] Vector3D + Point3D", "[utils][Operations3D]")
{
    Point3D<> const point3D{4, 1};
    Vector3D<> const vector3D{2, 3};
    auto const newPoint3D{vector3D + point3D};
    CHECK(newPoint3D.getX() == 6);
    CHECK(newPoint3D.getY() == 4);
}

TEST_CASE("[Operations3D] Point3D += Vector3D", "[utils][Operations3D]")
{
    Point3D<> point3D{4, 1};
    Vector3D<> const vector3D{2, 3};
    point3D += vector3D;
    CHECK(point3D.getX() == 6);
    CHECK(point3D.getY() == 4);
}

TEST_CASE("[Operations3D] toVector3D() method", "[utils][Operations3D]")
{
    SECTION("Up")
    {
        Vector3D<> const v1{toVector3D(Direction3D::Up)};
        CHECK(v1 == Vector3D{0, 1});
    }
    SECTION("Left")
    {
        Vector3D<> const v1{toVector3D(Direction3D::Left)};
        CHECK(v1 == Vector3D{-1, 0});
    }
    SECTION("Down")
    {
        Vector3D<> const v1{toVector3D(Direction3D::Down)};
        CHECK(v1 == Vector3D{0, -1});
    }
    SECTION("Right")
    {
        Vector3D<> const v1{toVector3D(Direction3D::Right)};
        CHECK(v1 == Vector3D{1, 0});
    }
    SECTION("UpRight")
    {
        Vector3D<> const v1{toVector3D(Direction3D::UpRight)};
        CHECK(v1 == Vector3D{1, 1});
    }
    SECTION("UpLeft")
    {
        Vector3D<> const v1{toVector3D(Direction3D::UpLeft)};
        CHECK(v1 == Vector3D{-1, 1});
    }
    SECTION("DownRight")
    {
        Vector3D<> const v1{toVector3D(Direction3D::DownRight)};
        CHECK(v1 == Vector3D{1, -1});
    }
    SECTION("DownLeft")
    {
        Vector3D<> const v1{toVector3D(Direction3D::DownLeft)};
        CHECK(v1 == Vector3D{-1, -1});
    }
}
