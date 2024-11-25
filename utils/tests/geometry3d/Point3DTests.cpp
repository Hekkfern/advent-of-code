#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry3d/Point3D.hpp>

using namespace utils::geometry3d;

TEST_CASE("[Point3D] create() method", "[utils][Point3D]")
{
    SECTION("Runtime tests")
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
            Point3D<> const point3D{Point3D<>::create(-2, 3, 5)};
            CHECK(point3D.getX() == -2);
            CHECK(point3D.getY() == 3);
            CHECK(point3D.getZ() == 5);
        }
    }
}

TEST_CASE("[Point3D] Constructor", "[Point3D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Default constructor")
        {
            Point3D<> const point3D;
            CHECK(point3D.getX() == 0);
            CHECK(point3D.getY() == 0);
            CHECK(point3D.getZ() == 0);
            auto const coords{point3D.getCoordinates()};
            CHECK(coords[0] == 0);
            CHECK(coords[1] == 0);
            CHECK(coords[2] == 0);
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
                CHECK(coords[0] == 2);
                CHECK(coords[1] == 4);
                CHECK(coords[2] == 5);
            }
            SECTION("Positive and negatives values")
            {
                Point3D<> const point3D{-2, 3, 5};
                CHECK(point3D.getX() == -2);
                CHECK(point3D.getY() == 3);
                CHECK(point3D.getZ() == 5);
                auto const coords{point3D.getCoordinates()};
                CHECK(coords[0] == -2);
                CHECK(coords[1] == 3);
                CHECK(coords[2] == 5);
            }
        }
        SECTION("Group constructor")
        {
            SECTION("Positive values")
            {
                Point3D<> const point3D{Point3D{2, 4, 5}};
                CHECK(point3D.getX() == 2);
                CHECK(point3D.getY() == 4);
                CHECK(point3D.getZ() == 5);
                auto const coords{point3D.getCoordinates()};
                CHECK(coords[0] == 2);
                CHECK(coords[1] == 4);
                CHECK(coords[2] == 5);
            }
            SECTION("Positive and negatives values")
            {
                Point3D<> const point3D{Point3D{-2, 3, 5}};
                CHECK(point3D.getX() == -2);
                CHECK(point3D.getY() == 3);
                CHECK(point3D.getZ() == 5);
                auto const coords{point3D.getCoordinates()};
                CHECK(coords[0] == -2);
                CHECK(coords[1] == 3);
                CHECK(coords[2] == 5);
            }
        }
    }
}

TEST_CASE("[Point3D] Constructor and containers", "[Point3D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Array")
        {
            std::array<Point3D<int32_t>, 2U> const points;
            for (auto const& p : points) {
                CHECK(p.getX() == 0);
                CHECK(p.getY() == 0);
                CHECK(p.getZ() == 0);
            }
        }
    }
}

TEST_CASE("[Point3D] getNeighbors() method", "[utils][Point3D]")
{
    SECTION("Runtime tests")
    {
        Point3D<> const point3D{Point3D{2, 4, 5}};
        auto const neighbors{point3D.getNeighbors()};
        CHECK(neighbors.size() == 6U);
    }
}

TEST_CASE("[Point3D] Setter methods", "[utils][Point3D]")
{
    SECTION("Runtime tests")
    {
        Point3D<> const point3D{2, 4, 5};
        SECTION("Set X")
        {
            auto const p2{point3D.setX(3)};
            CHECK(p2.getX() == 3);
            CHECK(p2.getY() == 4);
            CHECK(p2.getZ() == 5);
        }
        SECTION("Set Y")
        {
            auto const p2{point3D.setY(5)};
            CHECK(p2.getX() == 2);
            CHECK(p2.getY() == 5);
            CHECK(p2.getZ() == 5);
        }
        SECTION("Set Z")
        {
            auto const p2{point3D.setZ(7)};
            CHECK(p2.getX() == 2);
            CHECK(p2.getY() == 4);
            CHECK(p2.getZ() == 7);
        }
    }
    SECTION("Static tests")
    {
        constexpr Point3D<> point3D{2, 4, 5};
        SECTION("Set X")
        {
            constexpr auto p2{point3D.setX(3)};
            STATIC_CHECK(p2.getX() == 3);
            STATIC_CHECK(p2.getY() == 4);
            STATIC_CHECK(p2.getZ() == 5);
        }
        SECTION("Set Y")
        {
            constexpr auto p2{point3D.setY(5)};
            STATIC_CHECK(p2.getX() == 2);
            STATIC_CHECK(p2.getY() == 5);
            STATIC_CHECK(p2.getZ() == 5);
        }
        SECTION("Set Z")
        {
            constexpr auto p2{point3D.setZ(7)};
            STATIC_CHECK(p2.getX() == 2);
            STATIC_CHECK(p2.getY() == 4);
            STATIC_CHECK(p2.getZ() == 7);
        }
    }
}

TEST_CASE("[Point3D] Equality operator", "[utils][Point3D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Different")
        {
            Point3D<> const p1{2, 3, 5};
            Point3D<> const p2{-4, 2, 5};
            CHECK_FALSE(p1 == p2);
            CHECK(p1 != p2);
        }
        SECTION("Equal")
        {
            Point3D<> const p1{2, 3, 5};
            Point3D<> const p2{2, 3, 5};
            CHECK(p1 == p2);
            CHECK_FALSE(p1 != p2);
        }
    }
    SECTION("Static tests")
    {
        SECTION("Different")
        {
            constexpr Point3D<> p1{2, 3, 5};
            constexpr Point3D<> p2{-4, 2, 5};
            STATIC_CHECK_FALSE(p1 == p2);
            STATIC_CHECK(p1 != p2);
        }
        SECTION("Equal")
        {
            constexpr Point3D<> p1{2, 3, 5};
            constexpr Point3D<> p2{2, 3, 5};
            STATIC_CHECK(p1 == p2);
            STATIC_CHECK_FALSE(p1 != p2);
        }
    }
}

TEST_CASE("[Point3D] Negation operator", "[utils][Point3D]")
{
    SECTION("Runtime tests")
    {
        Point3D<> const p1{-2, 3, 5};
        Point3D<> const p2{4, -2, 5};
        CHECK(-p1 == Point3D{2, -3, -5});
        CHECK(-p2 == Point3D{-4, 2, -5});
    }
    SECTION("Static tests")
    {
        constexpr Point3D<> p1{-2, 3, 5};
        constexpr Point3D<> p2{4, -2, 5};
        STATIC_CHECK(-p1 == Point3D<>{2, -3, -5});
        STATIC_CHECK(-p2 == Point3D<>{-4, 2, -5});
    }
}

TEST_CASE("[Point3D] Structured binding", "[utils][Point3D]")
{
    Point3D<> const coords{1, 2, 3};
    auto const [x, y, z]{coords};
    CHECK(x == 1);
    CHECK(y == 2);
    CHECK(z == 3);
}

TEST_CASE("[Point3D] Hash calculation", "[utils][Point3D]")
{
    std::hash<Point3D<int32_t>> hasher;
    Point3D<> const coords1{1, 7, 2};
    Point3D<> const coords2{1, 7, 2};
    Point3D<> const coords3{4, 8, 1};

    SECTION("Same") { REQUIRE(hasher(coords1) == hasher(coords1)); }

    SECTION("Equal") { REQUIRE(hasher(coords1) == hasher(coords2)); }

    SECTION("Different") { REQUIRE(hasher(coords1) != hasher(coords3)); }
}
