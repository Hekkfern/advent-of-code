#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Grid2D.hpp>

using namespace utils::geometry2d;

TEST_CASE("[Grid2D] Constructor", "[utils][Grid2D]")
{
    SECTION("Default constructor")
    {
        Grid2D<int> const grid2D;
        CHECK(grid2D.getWidth() == 0ULL);
        CHECK(grid2D.getHeight() == 0ULL);
    }
    SECTION("Parametrized constructor")
    {
        Grid2D<int> const grid2D{{{1, 2}, {3, 4}, {5, 6}}};
        CHECK(grid2D.getWidth() == 2ULL);
        CHECK(grid2D.getHeight() == 3ULL);
    }
}

TEST_CASE("[Grid2D] getRow() method", "[utils][Grid2D]")
{
    SECTION("Empty grid")
    {
        Grid2D<int> const grid2D;
        CHECK(grid2D.getRow(0).empty());
        CHECK(grid2D.getRow(7).empty());
    }
    SECTION("Filled grid")
    {
        Grid2D<int> const grid2D{{{1, 2}, {3, 4}, {5, 6}}};
        auto const row0{grid2D.getRow(0)};
        REQUIRE_FALSE(row0.empty());
        CHECK(row0 == std::vector<int>{1, 2});
        CHECK(grid2D.getRow(7).empty());
    }
}
