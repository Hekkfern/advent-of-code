#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry3d/Operations3D.hpp>

using namespace utils::geometry3d;

TEST_CASE("[Operations3D] Move point by a vector", "[Operations3D]")
{
    Point3D<> const p1{3, -2, 1};
    auto const p2{move(p1, Vector3D<>{-1, 4, 1})};
    REQUIRE(p2);
    CHECK(*p2 == Point3D<>{2, 2, 2});
}

TEST_CASE("[Operations3D] Point3D + Vector3D", "[utils][Operations3D]")
{
    Point3D<> const point3D{4, 1, 1};
    Vector3D<> const vector3D{2, 3, 1};
    auto const newPoint3D{point3D + vector3D};
    REQUIRE(newPoint3D);
    CHECK(newPoint3D->getX() == 6);
    CHECK(newPoint3D->getY() == 4);
    CHECK(newPoint3D->getZ() == 2);
}

TEST_CASE("[Operations3D] Vector3D + Point3D", "[utils][Operations3D]")
{
    Point3D<> const point3D{4, 1, 1};
    Vector3D<> const vector3D{2, 3, 1};
    auto const newPoint3D{vector3D + point3D};
    REQUIRE(newPoint3D);
    CHECK(newPoint3D->getX() == 6);
    CHECK(newPoint3D->getY() == 4);
    CHECK(newPoint3D->getZ() == 2);
}
