#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry3d/Point3D.hpp>

using namespace utils::geometry3d;

TEST_CASE("[Point3D] create() method", "[utils][Point3D]")
{
    SECTION("Positive values")
    {
        Point3D<> const point3D{Point3D<>::create(2, 4, 5)};
        CHECK(point3D.getX() == 2);
        CHECK(point3D.getY() == 4);
        CHECK(point3D.getZ() == 5);
    }
    SECTION("Positive and negatives values")
    {
        Point3D<> const point3D{Point3D<>::create(-2, 3, -1)};
        CHECK(point3D.getX() == -2);
        CHECK(point3D.getY() == 3);
        CHECK(point3D.getZ() == -1);
    }
}

TEST_CASE("[Point3D] Constructor", "[Point3D]")
{
    SECTION("Default constructor")
    {
        Point3D<> const point3D;
        CHECK(point3D.getX() == 0);
        CHECK(point3D.getY() == 0);
        CHECK(point3D.getZ() == 0);
        auto const coords{point3D.getCoordinates()};
        CHECK(coords.mX == 0);
        CHECK(coords.mY == 0);
        CHECK(coords.mZ == 0);
    }
    SECTION("Parametrized constructor")
    {
        SECTION("Positive values")
        {
            Point3D<> const point3D{2, 4, 5};
            CHECK(point3D.getX() == 2);
            CHECK(point3D.getY() == 4);
            CHECK(point3D.getZ() == 5);
            auto const coords{point3D.getCoordinates()};
            CHECK(coords.mX == 2);
            CHECK(coords.mY == 4);
            CHECK(coords.mZ == 5);
        }
        SECTION("Positive and negatives values")
        {
            Point3D<> const point3D{-2, 3, -1};
            CHECK(point3D.getX() == -2);
            CHECK(point3D.getY() == 3);
            CHECK(point3D.getZ() == -1);
            auto const coords{point3D.getCoordinates()};
            CHECK(coords.mX == -2);
            CHECK(coords.mY == 3);
            CHECK(coords.mZ == -1);
        }
    }
    SECTION("Group constructor")
    {
        SECTION("Positive values")
        {
            Point3D<> const point3D{Coord3D<>{2, 4, 5}};
            CHECK(point3D.getX() == 2);
            CHECK(point3D.getY() == 4);
            CHECK(point3D.getZ() == 5);
            auto const coords{point3D.getCoordinates()};
            CHECK(coords.mX == 2);
            CHECK(coords.mY == 4);
            CHECK(coords.mZ == 5);
        }
        SECTION("Positive and negatives values")
        {
            Point3D<> const point3D{Coord3D<>{-2, 3, -1}};
            CHECK(point3D.getX() == -2);
            CHECK(point3D.getY() == 3);
            CHECK(point3D.getZ() == -1);
            auto const coords{point3D.getCoordinates()};
            CHECK(coords.mX == -2);
            CHECK(coords.mY == 3);
            CHECK(coords.mZ == -1);
        }
    }
}

TEST_CASE("[Point3D] getNeighbors() method", "[utils][Point3D]")
{
    Point3D<> const point3D{Coord3D<>{2, 4, 5}};
    auto const neighbors{point3D.getNeighbors()};
    CHECK(neighbors.size() == 6U);
}

TEST_CASE("[Point3D] Setter methods", "[utils][Point3D]")
{
    Point3D<> point3D{2, 4, 1};
    REQUIRE(point3D.getX() == 2);
    REQUIRE(point3D.getY() == 4);
    REQUIRE(point3D.getZ() == 1);
    SECTION("Set X")
    {
        point3D.setX(3);
        REQUIRE(point3D.getX() == 3);
        REQUIRE(point3D.getY() == 4);
        REQUIRE(point3D.getZ() == 1);
    }
    SECTION("Set Y")
    {
        point3D.setY(5);
        REQUIRE(point3D.getX() == 2);
        REQUIRE(point3D.getY() == 5);
        REQUIRE(point3D.getZ() == 1);
    }
    SECTION("Set Z")
    {
        point3D.setZ(7);
        REQUIRE(point3D.getX() == 2);
        REQUIRE(point3D.getY() == 4);
        REQUIRE(point3D.getZ() == 7);
    }
}

TEST_CASE("[Point3D] Equality operator", "[utils][Point3D]")
{
    SECTION("Different")
    {
        const Point3D p1{2, 3, 5};
        const Point3D p2{-4, 2, -3};
        CHECK_FALSE(p1 == p2);
        CHECK(p1 != p2);
    }
    SECTION("Equal")
    {
        const Point3D p1{2, 3, 5};
        const Point3D p2{2, 3, 5};
        CHECK(p1 == p2);
        CHECK_FALSE(p1 != p2);
    }
}

TEST_CASE("[Point3D] Addition operator", "[utils][Point3D]")
{
    const Point3D p1{-2, 3, 5};
    const Point3D p2{4, 2, 4};
    CHECK((p1 + p2) == Point3D{2, 5, 9});
    CHECK((p2 + p1) == Point3D{2, 5, 9});
}

TEST_CASE("[Point3D] Negation operator", "[utils][Point3D]")
{
    const Point3D p1{-2, 3, 5};
    const Point3D p2{4, -2, 4};
    CHECK(-p1 == Point3D{2, -3, -5});
    CHECK(-p2 == Point3D{-4, 2, -4});
}

TEST_CASE("[Point3D] Subtraction operator", "[utils][Point3D]")
{
    const Point3D p1{-2, 3, 5};
    const Point3D p2{4, 2, 4};
    CHECK((p1 - p2) == Point3D{-6, 1, 1});
    CHECK((p2 - p1) == Point3D{6, -1, -1});
}
