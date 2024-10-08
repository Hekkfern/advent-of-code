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
        SECTION("Empty grid")
        {
            Grid2D<int> const grid2D{{}};
            CHECK(grid2D.getWidth() == 0ULL);
            CHECK(grid2D.getHeight() == 0ULL);
        }
        SECTION("Filled grid")
        {
            Grid2D<int> const grid2D{{{1, 2}, {3, 4}, {5, 6}}};
            CHECK(grid2D.getWidth() == 2ULL);
            CHECK(grid2D.getHeight() == 3ULL);
        }
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

TEST_CASE("[Grid2D] iterateRow() method", "[utils][Grid2D]")
{
    SECTION("Immutable")
    {
        SECTION("Empty grid")
        {
            Grid2D<int> const grid2D;
            int count{0};
            grid2D.iterateRow(1, [&count](int const) -> bool {
                ++count;
                return true;
            });
            CHECK(count == 0);
        }
        SECTION("Filled grid")
        {
            Grid2D<int> const grid2D{{{1, 2}, {3, 4}, {5, 6}}};
            int count{0};
            grid2D.iterateRow(1, [&count](int const) -> bool {
                ++count;
                return true;
            });
            CHECK(count == 2);
        }
    }
    SECTION("Mutable")
    {
        Grid2D<int> grid2D{{{1, 2}, {3, 4}, {5, 6}}};
        grid2D.iterateRow(1, [](int& item) -> bool {
            ++item;
            return true;
        });
        CHECK(grid2D.at(0, 0) == 1);
        CHECK(grid2D.at(0, 1) == 2);
        CHECK(grid2D.at(1, 0) == 4);
        CHECK(grid2D.at(1, 1) == 5);
        CHECK(grid2D.at(2, 0) == 5);
        CHECK(grid2D.at(2, 1) == 6);
    }
}

TEST_CASE("[Grid2D] iterateColumn() method", "[utils][Grid2D]")
{
    SECTION("Immutable")
    {
        SECTION("Empty grid")
        {
            Grid2D<int> const grid2D;
            int count{0};
            grid2D.iterateColumn(1, [&count](int const) -> bool {
                ++count;
                return true;
            });
            CHECK(count == 0);
        }
        SECTION("Filled grid")
        {
            Grid2D<int> const grid2D{{{1, 2}, {3, 4}, {5, 6}}};
            int count{0};
            grid2D.iterateColumn(1, [&count](int const) -> bool {
                ++count;
                return true;
            });
            CHECK(count == 3);
        }
    }
    SECTION("Mutable")
    {
        Grid2D<int> grid2D{{{1, 2}, {3, 4}, {5, 6}}};
        grid2D.iterateColumn(1, [](int& item) -> bool {
            ++item;
            return true;
        });
        CHECK(grid2D.at(0, 0) == 1);
        CHECK(grid2D.at(0, 1) == 3);
        CHECK(grid2D.at(1, 0) == 3);
        CHECK(grid2D.at(1, 1) == 5);
        CHECK(grid2D.at(2, 0) == 5);
        CHECK(grid2D.at(2, 1) == 7);
    }
}

TEST_CASE("[Grid2D] at() method", "[utils][Grid2D]")
{
    SECTION("With X and Y")
    {
        SECTION("Read")
        {
            Grid2D<int> const grid2D{{{1, 2}, {3, 4}, {5, 6}}};
            auto& item{grid2D.at(1, 1)};
            CHECK(item == 4);
        }
        SECTION("Write and write")
        {
            Grid2D<int> grid2D{{{1, 2}, {3, 4}, {5, 6}}};
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
            Grid2D<int> const grid2D{{{1, 2}, {3, 4}, {5, 6}}};
            auto& item{grid2D.at(Coordinate2D<std::size_t>{1ULL, 1ULL})};
            CHECK(item == 4);
        }
        SECTION("Write and write")
        {
            Grid2D<int> grid2D{{{1, 2}, {3, 4}, {5, 6}}};
            auto& item{grid2D.at(Coordinate2D<std::size_t>{1ULL, 1ULL})};
            CHECK(item == 4);
            item = 57;
            CHECK(item == 57);
        }
    }
}

TEST_CASE("[Grid2D] subgrid() method", "[utils][Grid2D]")
{
    Grid2D<int> const grid2D{{{1, 2}, {3, 4}, {5, 6}}};
    SECTION("Correct subgrid")
    {
        auto const subgrid{grid2D.subgrid(1, 0, 2, 2)};
        CHECK(subgrid.at(0, 0) == 3);
        CHECK(subgrid.at(0, 1) == 4);
        CHECK(subgrid.at(1, 0) == 5);
        CHECK(subgrid.at(1, 1) == 6);
    }
    SECTION("Out of bounds")
    {
        auto const subgrid{grid2D.subgrid(1, 0, 6, 7)};
        CHECK(subgrid == Grid2D<int>{});
    }
}

TEST_CASE("[Grid2D] flipHorizontal() method", "[utils][Grid2D]")
{
    SECTION("Empty grid")
    {
        Grid2D<int> grid2D;
        grid2D.flipHorizontal();
        CHECK(grid2D == Grid2D<int>{});
    }
    SECTION("Filled grid")
    {
        /*
         * 5 6    6 5
         * 3 4 -> 4 3
         * 1 2    2 1
         */
        Grid2D<int> grid2D{{{1, 2}, {3, 4}, {5, 6}}};
        CHECK(grid2D.at(0, 0) == 1);
        grid2D.flipHorizontal();
        CHECK(grid2D == Grid2D<int>{{{2, 1}, {4, 3}, {6, 5}}});
        CHECK(grid2D.at(0, 0) == 2);
    }
}

TEST_CASE("[Grid2D] flipVertical() method", "[utils][Grid2D]")
{
    SECTION("Empty grid")
    {
        Grid2D<int> grid2D;
        grid2D.flipVertical();
        CHECK(grid2D == Grid2D<int>{});
    }
    SECTION("Filled grid")
    {
        /*
         * 5 6    1 2
         * 3 4 -> 3 4
         * 1 2    5 6
         */
        Grid2D<int> grid2D{{{1, 2}, {3, 4}, {5, 6}}};
        CHECK(grid2D.at(0, 0) == 1);
        grid2D.flipVertical();
        CHECK(grid2D == Grid2D<int>{{{5, 6}, {3, 4}, {1, 2}}});
        CHECK(grid2D.at(0, 0) == 5);
    }
}

TEST_CASE("[Grid2D] rotateClockwise() method", "[utils][Grid2D]")
{
    SECTION("Empty grid")
    {
        Grid2D<int> grid2D;
        grid2D.rotateClockwise();
        CHECK(grid2D == Grid2D<int>{});
    }
    SECTION("Filled grid")
    {
        Grid2D<int> grid2D{{{1, 2}, {3, 4}, {5, 6}}};
        grid2D.rotateClockwise();
        CHECK(grid2D == Grid2D<int>{{{5, 3, 1}, {6, 4, 2}}});
    }
}

TEST_CASE("[Grid2D] rotateCounterClockwise() method", "[utils][Grid2D]")
{
    SECTION("Empty grid")
    {
        Grid2D<int> grid2D;
        grid2D.rotateCounterClockwise();
        CHECK(grid2D == Grid2D<int>{std::vector<std::vector<int>>()});
    }
    SECTION("Filled grid")
    {
        Grid2D<int> grid2D{{{1, 2}, {3, 4}, {5, 6}}};
        grid2D.rotateCounterClockwise();
        CHECK(grid2D == Grid2D<int>{{{2, 4, 6}, {1, 3, 5}}});
    }
}

TEST_CASE("[Grid2D] findFirst() method", "[utils][Grid2D]")
{
    SECTION("Empty grid")
    {
        Grid2D<int> const grid2D{std::vector<std::vector<int>>()};
        REQUIRE_FALSE(grid2D.findFirst(34));
    }
    SECTION("Filled grid")
    {
        Grid2D<int> const grid2D{{{1, 2}, {3, 4}, {5, 6}}};
        SECTION("Found")
        {
            auto const result{grid2D.findFirst(3)};
            REQUIRE(result);
            CHECK(result->first == 0ULL);
            CHECK(result->second == 1ULL);
        }
        SECTION("Not found")
        {
            auto const result{grid2D.findFirst(65)};
            REQUIRE_FALSE(result);
        }
    }
}

TEST_CASE("[Grid2D] findAll() method", "[utils][Grid2D]")
{
    SECTION("Empty grid")
    {
        Grid2D<int> const grid2D{std::vector<std::vector<int>>{}};
        REQUIRE(grid2D.findAll(34).empty());
    }
    SECTION("Filled grid")
    {
        Grid2D<int> const grid2D{{{1, 2}, {3, 4}, {5, 6}}};
        SECTION("Found")
        {
            auto const result{grid2D.findAll(3)};
            REQUIRE(result.size() == 1);
            CHECK(result[0].getX() == 0ULL);
            CHECK(result[0].getY() == 1ULL);
        }
        SECTION("Not found")
        {
            auto const result{grid2D.findAll(65)};
            REQUIRE(result.empty());
        }
    }
}

TEST_CASE("[Grid2D] resize() method", "[utils][Grid2D]")
{
    Grid2D<int> grid2D{{{1, 2}, {3, 4}, {5, 6}}};
    SECTION("Increase")
    {
        grid2D.resize(4ULL, 3ULL, 0);
        REQUIRE(grid2D.getWidth() == 3ULL);
        REQUIRE(grid2D.getHeight() == 4ULL);
        CHECK(grid2D.at(2ULL, 3ULL) == 0);
    }
    SECTION("Decrease")
    {
        grid2D.resize(2ULL, 1ULL, 0);
        REQUIRE(grid2D.getWidth() == 1ULL);
        REQUIRE(grid2D.getHeight() == 2ULL);
        CHECK(grid2D.at(0ULL, 0ULL) == 1);
        CHECK(grid2D.at(0ULL, 1ULL) == 3);
    }
}

TEST_CASE("[Grid2D] where() method", "[utils][Grid2D]")
{
    Grid2D<int> grid2D{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};
    SECTION("With X and Y")
    {
        SECTION("Inside")
        {
            CHECK(grid2D.where(1, 1) == PositionStatus::Inside);
        }
        SECTION("On Border")
        {
            CHECK(grid2D.where(0, 0) == PositionStatus::OnBorder);
            CHECK(grid2D.where(2, 2) == PositionStatus::OnBorder);
        }
        SECTION("Outside")
        {
            CHECK(grid2D.where(7, 4) == PositionStatus::Outside);
        }
    }
    SECTION("With coords")
    {
        SECTION("Inside")
        {
            CHECK(
                grid2D.where(Coordinate2D<std::size_t>{1, 1})
                == PositionStatus::Inside);
        }
        SECTION("On Border")
        {
            CHECK(
                grid2D.where(Coordinate2D<std::size_t>{0, 0})
                == PositionStatus::OnBorder);
            CHECK(
                grid2D.where(Coordinate2D<std::size_t>{2, 2})
                == PositionStatus::OnBorder);
        }
        SECTION("Outside")
        {
            CHECK(
                grid2D.where(Coordinate2D<std::size_t>{7, 4})
                == PositionStatus::Outside);
        }
    }
}

TEST_CASE("[Grid2D] move() method", "[utils][Grid2D]")
{
    Grid2D<int> grid2D{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};

    SECTION("Success")
    {
        SECTION("Move right by 1")
        {
            auto const result{grid2D.move(
                Coordinate2D<std::size_t>{1, 0}, Direction2D::Right)};
            REQUIRE(result);
            CHECK(*result == Coordinate2D<std::size_t>{2, 0});
        }

        SECTION("Move up by 1")
        {
            auto const result{
                grid2D.move(Coordinate2D<std::size_t>{0, 1}, Direction2D::Up)};
            REQUIRE(result);
            CHECK(*result == Coordinate2D<std::size_t>{0, 2});
        }

        SECTION("Move diagonally by 1 right and 1 up")
        {
            auto const result{grid2D.move(
                Coordinate2D<std::size_t>{1, 1}, Direction2D::UpRight)};
            REQUIRE(result);
            CHECK(*result == Coordinate2D<std::size_t>{2, 2});
        }
    }

    SECTION("Out of bounds")
    {
        SECTION("Right side")
        {
            auto const result{grid2D.move(
                Coordinate2D<std::size_t>{3, 3}, Direction2D::Right)};
            CHECK_FALSE(result);
        }

        SECTION("Left side")
        {
            auto const result{grid2D.move(
                Coordinate2D<std::size_t>{0, 1}, Direction2D::Left)};
            CHECK_FALSE(result);
        }

        SECTION("Up side")
        {
            auto const result{
                grid2D.move(Coordinate2D<std::size_t>{3, 3}, Direction2D::Up)};
            CHECK_FALSE(result);
        }

        SECTION("Down side")
        {
            auto const result{grid2D.move(
                Coordinate2D<std::size_t>{3, 0}, Direction2D::Down)};
            CHECK_FALSE(result);
        }
    }
}
