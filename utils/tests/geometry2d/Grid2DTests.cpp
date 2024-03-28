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
        SECTION("First row")
        {
            auto const row{grid2D.getRow(0)};
            REQUIRE_FALSE(row.empty());
            CHECK(row == std::vector<int>{1, 2});
        }
        SECTION("Intermediate row")
        {
            auto const row{grid2D.getRow(1)};
            REQUIRE_FALSE(row.empty());
            CHECK(row == std::vector<int>{3, 4});
        }
        SECTION("Out-of-bounds row") { CHECK(grid2D.getRow(7).empty()); }
    }
}

TEST_CASE("[Grid2D] getColumn() method", "[utils][Grid2D]")
{
    SECTION("Empty grid")
    {
        Grid2D<int> const grid2D;
        CHECK(grid2D.getColumn(0).empty());
        CHECK(grid2D.getColumn(7).empty());
    }
    SECTION("Filled grid")
    {
        Grid2D<int> const grid2D{{{1, 2}, {3, 4}, {5, 6}}};
        SECTION("First column")
        {
            auto const col{grid2D.getColumn(0)};
            REQUIRE_FALSE(col.empty());
            CHECK(col == std::vector<int>{1, 3, 5});
        }
        SECTION("Intermediate column")
        {
            auto const col{grid2D.getColumn(1)};
            REQUIRE_FALSE(col.empty());
            CHECK(col == std::vector<int>{2, 4, 6});
        }
        SECTION("Out-of-bounds row") { CHECK(grid2D.getColumn(7).empty()); }
    }
}

TEST_CASE("[Grid2D] Equality operator", "[utils][Grid2D]")
{
    SECTION("Empty grids")
    {
        Grid2D<int> const grid2D_1;
        Grid2D<int> const grid2D_2;
        CHECK(grid2D_1 == grid2D_2);
        CHECK_FALSE(grid2D_1 != grid2D_2);
    }
    SECTION("Filled grid and empty grid")
    {
        Grid2D<int> const grid2D_1{{{1, 2}, {3, 4}, {5, 6}}};
        Grid2D<int> const grid2D_2;
        CHECK_FALSE(grid2D_1 == grid2D_2);
        CHECK(grid2D_1 != grid2D_2);
    }
    SECTION("Filled grids")
    {
        SECTION("Equal")
        {
            Grid2D<int> const grid2D_1{{{1, 2}, {3, 4}, {5, 6}}};
            Grid2D<int> const grid2D_2{{{1, 2}, {3, 4}, {5, 6}}};
            CHECK(grid2D_1 == grid2D_2);
            CHECK_FALSE(grid2D_1 != grid2D_2);
        }
        SECTION("Different")
        {
            Grid2D<int> const grid2D_1{{{1, 2}, {3, 4}, {5, 6}}};
            Grid2D<int> const grid2D_2{{{2, 2, 4}, {3, 4, 2}}};
            CHECK_FALSE(grid2D_1 == grid2D_2);
            CHECK(grid2D_1 != grid2D_2);
        }
    }
}
