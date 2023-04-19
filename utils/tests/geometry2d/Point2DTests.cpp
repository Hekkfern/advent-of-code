#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Point2D.hpp>

using namespace utils::geometry2d;

TEST_CASE("[Point2D] create() method", "[utils][Point2D]")
{
    SECTION("Positive values")
    {
        const Point2D<> point2D{Point2D<>::create(2, 4)};
        CHECK(point2D.getX() == 2);
        CHECK(point2D.getY() == 4);
    }
    SECTION("Positive and negatives values")
    {
        const Point2D<> point2D{Point2D<>::create(-2, 3)};
        CHECK(point2D.getX() == -2);
        CHECK(point2D.getY() == 3);
    }
}

TEST_CASE("[Point2D] Constructor", "[Point2D]")
{
    SECTION("Default constructor")
    {
        const Point2D<> point2D;
        CHECK(point2D.getX() == 0);
        CHECK(point2D.getY() == 0);
        const auto coords{point2D.getCoordinates()};
        CHECK(coords.mX == 0);
        CHECK(coords.mY == 0);
    }
    SECTION("Parametrized constructor")
    {
        SECTION("Positive values")
        {
            const Point2D<> point2D{2, 4};
            CHECK(point2D.getX() == 2);
            CHECK(point2D.getY() == 4);
            const auto coords{point2D.getCoordinates()};
            CHECK(coords.mX == 2);
            CHECK(coords.mY == 4);
        }
        SECTION("Positive and negatives values")
        {
            const Point2D<> point2D{-2, 3};
            CHECK(point2D.getX() == -2);
            CHECK(point2D.getY() == 3);
            const auto coords{point2D.getCoordinates()};
            CHECK(coords.mX == -2);
            CHECK(coords.mY == 3);
        }
    }
    SECTION("Group constructor")
    {
        SECTION("Positive values")
        {
            const Point2D<> point2D{Coord2D<>{2, 4}};
            CHECK(point2D.getX() == 2);
            CHECK(point2D.getY() == 4);
            const auto coords{point2D.getCoordinates()};
            CHECK(coords.mX == 2);
            CHECK(coords.mY == 4);
        }
        SECTION("Positive and negatives values")
        {
            const Point2D<> point2D{Coord2D<>{-2, 3}};
            CHECK(point2D.getX() == -2);
            CHECK(point2D.getY() == 3);
            const auto coords{point2D.getCoordinates()};
            CHECK(coords.mX == -2);
            CHECK(coords.mY == 3);
        }
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
