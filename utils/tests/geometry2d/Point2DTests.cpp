#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Point2D.hpp>

using namespace utils::geometry2d;

TEST_CASE("[Point2D] create() method", "[utils][Point2D]")
{
    SECTION("Positive values")
    {
        Point2D<> const point2D{Point2D<>::create(2, 4)};
        CHECK(point2D.getX() == 2);
        CHECK(point2D.getY() == 4);
    }
    SECTION("Positive and negatives values")
    {
        Point2D<> const point2D{Point2D<>::create(-2, 3)};
        CHECK(point2D.getX() == -2);
        CHECK(point2D.getY() == 3);
    }
}

TEST_CASE("[Point2D] Constructor", "[Point2D]")
{
    SECTION("Default constructor")
    {
        Point2D<> const point2D;
        CHECK(point2D.getX() == 0);
        CHECK(point2D.getY() == 0);
        auto const coords{point2D.getCoordinates()};
        CHECK(coords.mX == 0);
        CHECK(coords.mY == 0);
    }
    SECTION("Parametrized constructor")
    {
        SECTION("Positive values")
        {
            Point2D<> const point2D{2, 4};
            CHECK(point2D.getX() == 2);
            CHECK(point2D.getY() == 4);
            auto const coords{point2D.getCoordinates()};
            CHECK(coords.mX == 2);
            CHECK(coords.mY == 4);
        }
        SECTION("Positive and negatives values")
        {
            Point2D<> const point2D{-2, 3};
            CHECK(point2D.getX() == -2);
            CHECK(point2D.getY() == 3);
            auto const coords{point2D.getCoordinates()};
            CHECK(coords.mX == -2);
            CHECK(coords.mY == 3);
        }
    }
    SECTION("Group constructor")
    {
        SECTION("Positive values")
        {
            Point2D<> const point2D{Coord2D<>{2, 4}};
            CHECK(point2D.getX() == 2);
            CHECK(point2D.getY() == 4);
            auto const coords{point2D.getCoordinates()};
            CHECK(coords.mX == 2);
            CHECK(coords.mY == 4);
        }
        SECTION("Positive and negatives values")
        {
            Point2D<> const point2D{Coord2D<>{-2, 3}};
            CHECK(point2D.getX() == -2);
            CHECK(point2D.getY() == 3);
            auto const coords{point2D.getCoordinates()};
            CHECK(coords.mX == -2);
            CHECK(coords.mY == 3);
        }
    }
}

TEST_CASE("[Point2D] Constructor and containers", "[Point2D]")
{
    SECTION("Array")
    {
        const std::array<Point2D<int32_t>, 2U> points;
        for (auto const& p : points) {
            REQUIRE(p.getX() == 0);
            REQUIRE(p.getY() == 0);
        }
    }
}

TEST_CASE("[Point2D] getNeighbors() method", "[utils][Point2D]")
{
    Point2D<> const point2D{Coord2D<>{2, 4}};
    auto const neighbors{point2D.getNeighbors()};
    CHECK(neighbors.size() == 4U);
}

TEST_CASE("[Point2D] Setter methods", "[utils][Point2D]")
{
    Point2D<> point2D{2, 4};
    REQUIRE(point2D.getX() == 2);
    REQUIRE(point2D.getY() == 4);
    SECTION("Set X")
    {
        point2D.setX(3);
        REQUIRE(point2D.getX() == 3);
        REQUIRE(point2D.getY() == 4);
    }
    SECTION("Set Y")
    {
        point2D.setY(5);
        REQUIRE(point2D.getX() == 2);
        REQUIRE(point2D.getY() == 5);
    }
}

TEST_CASE("[Point2D] Equality operator", "[utils][Point2D]")
{
    SECTION("Different")
    {
        const Point2D p1{2, 3};
        const Point2D p2{-4, 2};
        CHECK_FALSE(p1 == p2);
        CHECK(p1 != p2);
    }
    SECTION("Equal")
    {
        const Point2D p1{2, 3};
        const Point2D p2{2, 3};
        CHECK(p1 == p2);
        CHECK_FALSE(p1 != p2);
    }
}

TEST_CASE("[Point2D] Addition operator", "[utils][Point2D]")
{
    const Point2D p1{-2, 3};
    const Point2D p2{4, 2};
    CHECK((p1 + p2) == Point2D{2, 5});
    CHECK((p2 + p1) == Point2D{2, 5});
}

TEST_CASE("[Point2D] Negation operator", "[utils][Point2D]")
{
    const Point2D p1{-2, 3};
    const Point2D p2{4, -2};
    CHECK(-p1 == Point2D{2, -3});
    CHECK(-p2 == Point2D{-4, 2});
}

TEST_CASE("[Point2D] Subtraction operator", "[utils][Point2D]")
{
    const Point2D p1{-2, 3};
    const Point2D p2{4, 2};
    CHECK((p1 - p2) == Point2D{-6, 1});
    CHECK((p2 - p1) == Point2D{6, -1});
}
