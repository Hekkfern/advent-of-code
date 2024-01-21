#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry3d/Operations3D.hpp>

using namespace utils::geometry3d;

TEST_CASE("[Operations3D] Move point by a vector", "[Operations3D]")
{
    Point3D const p1{3, -2, 4};
    Point3D<> const p2{Operations3D<>::move(p1, Vector3D{-1, 4, 1})};
    CHECK(p2 == Point3D{2, 2, 5});
}

TEST_CASE("[Operations3D] Point3D + Vector3D", "[utils][Operations3D]")
{
    Point3D const point3D{4, 1, 4};
    Vector3D const vector3D{2, 3, 1};
    auto const newPoint3D{point3D + vector3D};
    CHECK(newPoint3D.getX() == 6);
    CHECK(newPoint3D.getY() == 4);
    CHECK(newPoint3D.getZ() == 5);
}

TEST_CASE("[Operations3D] Vector3D + Point3D", "[utils][Operations3D]")
{
    Point3D const point3D{4, 1, 4};
    Vector3D const vector3D{2, 3, 1};
    auto const newPoint3D{vector3D + point3D};
    CHECK(newPoint3D.getX() == 6);
    CHECK(newPoint3D.getY() == 4);
    CHECK(newPoint3D.getZ() == 5);
}

TEST_CASE("[Operations3D] Point3D += Vector3D", "[utils][Operations3D]")
{
    Point3D point3D{4, 1, 1};
    Vector3D const vector3D{2, 3, 1};
    point3D += vector3D;
    CHECK(point3D.getX() == 6);
    CHECK(point3D.getY() == 4);
    CHECK(point3D.getZ() == 2);
}
