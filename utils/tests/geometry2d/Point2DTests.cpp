#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Point2D.hpp>

using namespace utils::geometry2d;

TEST_CASE("[Point2D] create() method", "[utils][Point2D]")
{
    SECTION("Runtime tests")
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
}

TEST_CASE("[Point2D] Constructor", "[Point2D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Default constructor")
        {
            Point2D<> const point2D;
            CHECK(point2D.getX() == 0);
            CHECK(point2D.getY() == 0);
            auto const coords{point2D.getCoordinates()};
            CHECK(coords.getX() == 0);
            CHECK(coords.getY() == 0);
        }
        SECTION("Parametrized constructor")
        {
            SECTION("Positive values")
            {
                Point2D<> const point2D{2, 4};
                CHECK(point2D.getX() == 2);
                CHECK(point2D.getY() == 4);
                auto const coords{point2D.getCoordinates()};
                CHECK(coords.getX() == 2);
                CHECK(coords.getY() == 4);
            }
            SECTION("Positive and negatives values")
            {
                Point2D<> const point2D{-2, 3};
                CHECK(point2D.getX() == -2);
                CHECK(point2D.getY() == 3);
                auto const coords{point2D.getCoordinates()};
                CHECK(coords.getX() == -2);
                CHECK(coords.getY() == 3);
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
                CHECK(coords.getX() == 2);
                CHECK(coords.getY() == 4);
            }
            SECTION("Positive and negatives values")
            {
                Point2D<> const point2D{Coord2D<>{-2, 3}};
                CHECK(point2D.getX() == -2);
                CHECK(point2D.getY() == 3);
                auto const coords{point2D.getCoordinates()};
                CHECK(coords.getX() == -2);
                CHECK(coords.getY() == 3);
            }
        }
    }
}

TEST_CASE("[Point2D] Constructor and containers", "[Point2D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Array")
        {
            std::array<Point2D<int32_t>, 2U> const points;
            for (auto const& p : points) {
                CHECK(p.getX() == 0);
                CHECK(p.getY() == 0);
            }
        }
    }
}

TEST_CASE("[Point2D] getNeighbors() method", "[utils][Point2D]")
{
    SECTION("Runtime tests")
    {
        Point2D<> const point2D{Coord2D<>{2, 4}};
        auto const neighbors{point2D.getNeighbors()};
        CHECK(neighbors.size() == 4U);
    }
}

TEST_CASE("[Point2D] Setter methods", "[utils][Point2D]")
{
    SECTION("Runtime tests")
    {
        Point2D const point2D{2, 4};
        SECTION("Set X")
        {
            auto const p2{point2D.setX(3)};
            CHECK(p2.getX() == 3);
            CHECK(p2.getY() == 4);
        }
        SECTION("Set Y")
        {
            auto const p2{point2D.setY(5)};
            CHECK(p2.getX() == 2);
            CHECK(p2.getY() == 5);
        }
    }
    SECTION("Static tests")
    {
        constexpr Point2D point2D{2, 4};
        SECTION("Set X")
        {
            constexpr auto p2{point2D.setX(3)};
            STATIC_CHECK(p2.getX() == 3);
            STATIC_CHECK(p2.getY() == 4);
        }
        SECTION("Set Y")
        {
            constexpr auto p2{point2D.setY(5)};
            STATIC_CHECK(p2.getX() == 2);
            STATIC_CHECK(p2.getY() == 5);
        }
    }
}

TEST_CASE("[Point2D] Equality operator", "[utils][Point2D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Different")
        {
            Point2D const p1{2, 3};
            Point2D const p2{-4, 2};
            CHECK_FALSE(p1 == p2);
            CHECK(p1 != p2);
        }
        SECTION("Equal")
        {
            Point2D const p1{2, 3};
            Point2D const p2{2, 3};
            CHECK(p1 == p2);
            CHECK_FALSE(p1 != p2);
        }
    }
    SECTION("Static tests")
    {
        SECTION("Different")
        {
            constexpr Point2D p1{2, 3};
            constexpr Point2D p2{-4, 2};
            STATIC_CHECK_FALSE(p1 == p2);
            STATIC_CHECK(p1 != p2);
        }
        SECTION("Equal")
        {
            constexpr Point2D p1{2, 3};
            constexpr Point2D p2{2, 3};
            STATIC_CHECK(p1 == p2);
            STATIC_CHECK_FALSE(p1 != p2);
        }
    }
}

TEST_CASE("[Point2D] Addition operator", "[utils][Point2D]")
{
    SECTION("Runtime tests")
    {
        Point2D const p1{-2, 3};
        Point2D const p2{4, 2};
        CHECK((p1 + p2) == Point2D{2, 5});
        CHECK((p2 + p1) == Point2D{2, 5});
    }
}

TEST_CASE("[Point2D] Negation operator", "[utils][Point2D]")
{
    SECTION("Runtime tests")
    {
        Point2D const p1{-2, 3};
        Point2D const p2{4, -2};
        CHECK(-p1 == Point2D{2, -3});
        CHECK(-p2 == Point2D{-4, 2});
    }
    SECTION("Static tests")
    {
        constexpr Point2D p1{-2, 3};
        constexpr Point2D p2{4, -2};
        STATIC_CHECK(-p1 == Point2D{2, -3});
        STATIC_CHECK(-p2 == Point2D{-4, 2});
    }
}

TEST_CASE("[Point2D] Subtraction operator", "[utils][Point2D]")
{
    SECTION("Runtime tests")
    {
        Point2D const p1{-2, 3};
        Point2D const p2{4, 2};
        CHECK((p1 - p2) == Point2D{-6, 1});
        CHECK((p2 - p1) == Point2D{6, -1});
    }
}
