#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Coord2D.hpp>

using namespace utils::geometry2d;

TEST_CASE("[Coord2D] Constructor", "[utils][Coord2D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Default constructor")
        {
            Coord2D<> const coords;
            CHECK(coords.getX() == 0);
            CHECK(coords.getY() == 0);
        }
        SECTION("Parametrized constructor")
        {
            Coord2D const coords{1, 2};
            CHECK(coords.getX() == 1);
            CHECK(coords.getY() == 2);
        }
    }
    SECTION("Static tests")
    {
        SECTION("Default constructor")
        {
            constexpr Coord2D<> coords;
            STATIC_CHECK(coords.getX() == 0);
            STATIC_CHECK(coords.getY() == 0);
        }
        SECTION("Parametrized constructor")
        {
            constexpr Coord2D coords{1, 2};
            STATIC_CHECK(coords.getX() == 1);
            STATIC_CHECK(coords.getY() == 2);
        }
    }
}

TEST_CASE("[Coord2D] Equality operator", "[utils][Coord2D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Equal")
        {
            Coord2D const coords1{1, 2};
            Coord2D const coords2{1, 2};
            CHECK(coords1 == coords2);
            CHECK_FALSE(coords1 != coords2);
        }
        SECTION("Different")
        {
            Coord2D const coords1{1, 2};
            Coord2D const coords2{7, 10};
            CHECK_FALSE(coords1 == coords2);
            CHECK(coords1 != coords2);
        }
    }
    SECTION("Static tests")
    {
        SECTION("Equal")
        {
            constexpr Coord2D coords1{1, 2};
            constexpr Coord2D coords2{1, 2};
            STATIC_CHECK(coords1 == coords2);
            STATIC_CHECK_FALSE(coords1 != coords2);
        }
        SECTION("Different")
        {
            constexpr Coord2D coords1{1, 2};
            constexpr Coord2D coords2{7, 10};
            STATIC_CHECK_FALSE(coords1 == coords2);
            STATIC_CHECK(coords1 != coords2);
        }
    }
}

TEST_CASE("[Coord2D] Structured binding", "[utils][Coord2D]")
{
    Coord2D const coords{1, 2};
    auto const [x, y]{coords};
    CHECK(x == 1);
    CHECK(y == 2);
}
