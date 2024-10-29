#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <utils/geometry2d/InfiniteGrid2D.hpp>

using namespace utils::geometry2d;

TEST_CASE("[InfiniteGrid2D] Equality operator", "[utils][InfiniteGrid2D]")
{
    SECTION("Empty grids")
    {
        InfiniteGrid2D<int> const grid2D_1;
        InfiniteGrid2D<int> const grid2D_2;
        CHECK(grid2D_1 == grid2D_2);
        CHECK_FALSE(grid2D_1 != grid2D_2);
    }
    SECTION("Filled grid and empty grid")
    {
        InfiniteGrid2D<int> const grid2D_1{{{1, 2}, {3, 4}, {5, 6}}};
        InfiniteGrid2D<int> const grid2D_2;
        CHECK_FALSE(grid2D_1 == grid2D_2);
        CHECK(grid2D_1 != grid2D_2);
    }
    SECTION("Filled grids")
    {
        SECTION("Equal")
        {
            InfiniteGrid2D<int> const grid2D_1{{{1, 2}, {3, 4}, {5, 6}}};
            InfiniteGrid2D<int> const grid2D_2{{{1, 2}, {3, 4}, {5, 6}}};
            CHECK(grid2D_1 == grid2D_2);
            CHECK_FALSE(grid2D_1 != grid2D_2);
        }
        SECTION("Different")
        {
            InfiniteGrid2D<int> const grid2D_1{{{1, 2}, {3, 4}, {5, 6}}};
            InfiniteGrid2D<int> const grid2D_2{{{2, 2, 4}, {3, 4, 2}}};
            CHECK_FALSE(grid2D_1 == grid2D_2);
            CHECK(grid2D_1 != grid2D_2);
        }
    }
}

TEST_CASE("[InfiniteGrid2D] at() method", "[utils][InfiniteGrid2D]")
{
    SECTION("With X and Y")
    {
        SECTION("Read")
        {
            InfiniteGrid2D<int> const grid2D{{{1, 2}, {3, 4}, {5, 6}}};
            SECTION("Inside")
            {
                auto& item{grid2D.at(1LL, 1LL)};
                CHECK(item == 4);
            }
            SECTION("Outside")
            {
                auto& item{grid2D.at(4LL, -3LL)};
                CHECK(item == 4);
            }
        }
        SECTION("Read and write")
        {
            InfiniteGrid2D<int> grid2D{{{1, 2}, {3, 4}, {5, 6}}};
            auto& item{grid2D.at(1, 1)};
            CHECK(item == 4);
            item = 57;
            CHECK(item == 57);
        }
    }
    SECTION("With coordinates")
    {
        SECTION("Read")
        {
            InfiniteGrid2D<int> const grid2D{{{1, 2}, {3, 4}, {5, 6}}};
            SECTION("Inside")
            {
                auto& item{grid2D.at(InfiniteGrid2D<int>::Coord{1LL, 1LL})};
                CHECK(item == 4);
            }
            SECTION("Outside")
            {
                auto& item{grid2D.at(InfiniteGrid2D<int>::Coord{-3LL, 4LL})};
                CHECK(item == 4);
            }
        }
        SECTION("Read and write")
        {
            InfiniteGrid2D<int> grid2D{{{1, 2}, {3, 4}, {5, 6}}};
            auto& item{grid2D.at(InfiniteGrid2D<int>::Coord{1ULL, 1ULL})};
            CHECK(item == 4);
            item = 57;
            CHECK(item == 57);
        }
    }
}

TEST_CASE("[InfiniteGrid2D] flipHorizontal() method", "[utils][InfiniteGrid2D]")
{
    SECTION("Empty grid")
    {
        InfiniteGrid2D<int> grid2D;
        grid2D.flipHorizontal();
        CHECK(grid2D == InfiniteGrid2D<int>{});
    }
    SECTION("Filled grid")
    {
        /*
         * 5 6    6 5
         * 3 4 -> 4 3
         * 1 2    2 1
         */
        InfiniteGrid2D<int> grid2D{{{1, 2}, {3, 4}, {5, 6}}};
        CHECK(grid2D.at(0, 0) == 1);
        grid2D.flipHorizontal();
        CHECK(grid2D == InfiniteGrid2D<int>{{{2, 1}, {4, 3}, {6, 5}}});
        CHECK(grid2D.at(0, 0) == 2);
    }
}

TEST_CASE("[InfiniteGrid2D] flipVertical() method", "[utils][InfiniteGrid2D]")
{
    SECTION("Empty grid")
    {
        InfiniteGrid2D<int> grid2D;
        grid2D.flipVertical();
        CHECK(grid2D == InfiniteGrid2D<int>{});
    }
    SECTION("Filled grid")
    {
        /*
         * 5 6    1 2
         * 3 4 -> 3 4
         * 1 2    5 6
         */
        InfiniteGrid2D<int> grid2D{{{1, 2}, {3, 4}, {5, 6}}};
        CHECK(grid2D.at(0, 0) == 1);
        grid2D.flipVertical();
        CHECK(grid2D == InfiniteGrid2D<int>{{{5, 6}, {3, 4}, {1, 2}}});
        CHECK(grid2D.at(0, 0) == 5);
    }
}

TEST_CASE(
    "[InfiniteGrid2D] rotateClockwise() method", "[utils][InfiniteGrid2D]")
{
    SECTION("Empty grid")
    {
        InfiniteGrid2D<int> grid2D;
        grid2D.rotateClockwise();
        CHECK(grid2D == InfiniteGrid2D<int>{});
    }
    SECTION("Filled grid")
    {
        InfiniteGrid2D<int> grid2D{{{1, 2}, {3, 4}, {5, 6}}};
        grid2D.rotateClockwise();
        CHECK(grid2D == InfiniteGrid2D<int>{{{5, 3, 1}, {6, 4, 2}}});
    }
}

TEST_CASE(
    "[InfiniteGrid2D] rotateCounterClockwise() method",
    "[utils][InfiniteGrid2D]")
{
    SECTION("Empty grid")
    {
        InfiniteGrid2D<int> grid2D;
        grid2D.rotateCounterClockwise();
        CHECK(grid2D == InfiniteGrid2D<int>{std::vector<std::vector<int>>()});
    }
    SECTION("Filled grid")
    {
        InfiniteGrid2D<int> grid2D{{{1, 2}, {3, 4}, {5, 6}}};
        grid2D.rotateCounterClockwise();
        CHECK(grid2D == InfiniteGrid2D<int>{{{2, 4, 6}, {1, 3, 5}}});
    }
}

TEST_CASE("[InfiniteGrid2D] move() method", "[utils][InfiniteGrid2D]")
{
    InfiniteGrid2D<int> grid2D{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};

    SECTION("Success")
    {
        SECTION("Move right by 1")
        {
            auto const result{grid2D.move(
                InfiniteGrid2D<int>::Coord{1, 0}, Direction2D::Right)};
            REQUIRE(result);
            CHECK(*result == InfiniteGrid2D<int>::Coord{2, 0});
        }

        SECTION("Move up by 1")
        {
            auto const result{
                grid2D.move(InfiniteGrid2D<int>::Coord{0, 1}, Direction2D::Up)};
            REQUIRE(result);
            CHECK(*result == InfiniteGrid2D<int>::Coord{0, 2});
        }

        SECTION("Move diagonally by 1 right and 1 up")
        {
            auto const result{grid2D.move(
                InfiniteGrid2D<int>::Coord{1, 1}, Direction2D::UpRight)};
            REQUIRE(result);
            CHECK(*result == InfiniteGrid2D<int>::Coord{2, 2});
        }
    }

    SECTION("Out of bounds")
    {
        SECTION("Right side")
        {
            auto const result{grid2D.move(
                InfiniteGrid2D<int>::Coord{3, 3}, Direction2D::Right)};
            REQUIRE(result);
            CHECK(*result == InfiniteGrid2D<int>::Coord{4, 3});
        }

        SECTION("Left side")
        {
            auto const result{grid2D.move(
                InfiniteGrid2D<int>::Coord{0, 1}, Direction2D::Left)};
            REQUIRE(result);
            CHECK(*result == InfiniteGrid2D<int>::Coord{-1, 1});
        }

        SECTION("Up side")
        {
            auto const result{
                grid2D.move(InfiniteGrid2D<int>::Coord{3, 3}, Direction2D::Up)};
            REQUIRE(result);
            CHECK(*result == InfiniteGrid2D<int>::Coord{3, 4});
        }

        SECTION("Down side")
        {
            auto const result{grid2D.move(
                InfiniteGrid2D<int>::Coord{3, 0}, Direction2D::Down)};
            REQUIRE(result);
            CHECK(*result == InfiniteGrid2D<int>::Coord{3, -1});
        }
    }
}

TEST_CASE(
    "[InfiniteGrid2D] getCardinalNeighbors() method", "[utils][InfiniteGrid2D]")
{
    InfiniteGrid2D<int> grid2D{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};

    SECTION("Position inside")
    {
        std::vector<InfiniteGrid2D<int>::Coord> const expected{
            InfiniteGrid2D<int>::Coord{0ULL, 1ULL},
            InfiniteGrid2D<int>::Coord{2ULL, 1ULL},
            InfiniteGrid2D<int>::Coord{1ULL, 0ULL},
            InfiniteGrid2D<int>::Coord{1ULL, 2ULL}};
        auto const result{
            grid2D.getCardinalNeighbors(InfiniteGrid2D<int>::Coord{1, 1})};
        REQUIRE(result.size() == expected.size());
        for (auto const& item : result) {
            CHECK(ranges::contains(result, item));
        }
    }

    SECTION("Position outside")
    {
        std::vector<InfiniteGrid2D<int>::Coord> const expected{
            InfiniteGrid2D<int>::Coord{2ULL, 2ULL},
            InfiniteGrid2D<int>::Coord{4ULL, 2ULL},
            InfiniteGrid2D<int>::Coord{3ULL, 1ULL},
            InfiniteGrid2D<int>::Coord{3ULL, 3ULL}};
        auto const result{
            grid2D.getCardinalNeighbors(InfiniteGrid2D<int>::Coord{3, 2})};
        REQUIRE(result.size() == expected.size());
        for (auto const& item : result) {
            CHECK(ranges::contains(result, item));
        }
    }
}
