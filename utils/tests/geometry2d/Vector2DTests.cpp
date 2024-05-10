#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Vector2D.hpp>

using namespace utils::geometry2d;

TEST_CASE("[Vector2D] create() method", "[utils][Vector2D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Positive values")
        {
            Vector2D const vector2D{Vector2D<>::create(2, 4)};
            CHECK(vector2D.getX() == 2);
            CHECK(vector2D.getY() == 4);
            auto const coords{vector2D.getCoordinates()};
            CHECK(coords.getX() == 2);
            CHECK(coords.getY() == 4);
        }
        SECTION("Positive and negatives values")
        {
            Vector2D const vector2D{Vector2D<>::create(-2, 3)};
            CHECK(vector2D.getX() == -2);
            CHECK(vector2D.getY() == 3);
            auto const coords{vector2D.getCoordinates()};
            CHECK(coords.getX() == -2);
            CHECK(coords.getY() == 3);
        }
    }
}

TEST_CASE("[Vector2D] Constructor", "[utils][Vector2D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Default constructor")
        {
            Vector2D<> const vector2D;
            CHECK(vector2D.getX() == 0);
            CHECK(vector2D.getY() == 0);
            auto const coords{vector2D.getCoordinates()};
            CHECK(coords.getX() == 0);
            CHECK(coords.getY() == 0);
        }
        SECTION("Parametrized constructor")
        {
            SECTION("Positive values")
            {
                Vector2D const vector2D{2, 4};
                CHECK(vector2D.getX() == 2);
                CHECK(vector2D.getY() == 4);
                auto const coords{vector2D.getCoordinates()};
                CHECK(coords.getX() == 2);
                CHECK(coords.getY() == 4);
            }
            SECTION("Positive and negatives values")
            {
                Vector2D const vector2D{-2, 3};
                CHECK(vector2D.getX() == -2);
                CHECK(vector2D.getY() == 3);
                auto const coords{vector2D.getCoordinates()};
                CHECK(coords.getX() == -2);
                CHECK(coords.getY() == 3);
            }
        }
        SECTION("Group constructor")
        {
            SECTION("Positive values")
            {
                Vector2D const vector2D{Coordinate2D{2, 4}};
                CHECK(vector2D.getX() == 2);
                CHECK(vector2D.getY() == 4);
                auto const coords{vector2D.getCoordinates()};
                CHECK(coords.getX() == 2);
                CHECK(coords.getY() == 4);
            }
            SECTION("Positive and negatives values")
            {
                Vector2D const vector2D{Coordinate2D{-2, 3}};
                CHECK(vector2D.getX() == -2);
                CHECK(vector2D.getY() == 3);
                auto const coords{vector2D.getCoordinates()};
                CHECK(coords.getX() == -2);
                CHECK(coords.getY() == 3);
            }
        }
    }
}

TEST_CASE("[Vector2D] size() method", "[utils][Vector2D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Zero vector")
        {
            Vector2D<> const v1;
            CHECK(v1.size() == std::array<uint64_t, 2ULL>{0ULL, 0ULL});
        }
        SECTION("Positive values")
        {
            Vector2D const v1{2, 3};
            CHECK(v1.size() == std::array<uint64_t, 2ULL>{2ULL, 3ULL});
        }
        SECTION("Positive and negatives values")
        {
            Vector2D const v1{-2, 1};
            CHECK(v1.size() == std::array<uint64_t, 2ULL>{2ULL, 1ULL});
        }
    }
}

TEST_CASE("[Vector2D] range() method", "[utils][Vector2D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Zero vector")
        {
            Vector2D<> const v1;
            CHECK(v1.range() == 0UL);
        }
        SECTION("Positive values")
        {
            Vector2D const v1{2, 3};
            CHECK(v1.range() == 3UL);
        }
        SECTION("Positive and negatives values")
        {
            Vector2D const v1{-2, 1};
            CHECK(v1.range() == 2UL);
        }
    }
}

TEST_CASE("[Vector2D] distance() method", "[utils][Vector2D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Zero vector")
        {
            Vector2D<> const v1;
            CHECK(v1.distance() == 0UL);
        }
        SECTION("Positive values")
        {
            Vector2D const v1{2, 3};
            CHECK(v1.distance() == 5UL);
        }
        SECTION("Positive and negatives values")
        {
            Vector2D const v1{-2, 1};
            CHECK(v1.distance() == 3UL);
        }
    }
}

TEST_CASE("[Vector2D] normalize() method", "[utils][Vector2D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Zero vector")
        {
            Vector2D<> const v1;
            auto const v2{v1.normalize()};
            CHECK(v2 == Vector2D{0, 0});
        }
        SECTION("Positive values")
        {
            Vector2D const v1{2, 3};
            auto const v2{v1.normalize()};
            CHECK(v2 == Vector2D{1, 1});
        }
        SECTION("Positive and negatives values")
        {
            Vector2D const v1{-2, 1};
            auto const v2{v1.normalize()};
            CHECK(v2 == Vector2D{-1, 1});
        }
        SECTION("Already-normalized vector")
        {
            Vector2D const v1{-1, 0};
            auto const v2{v1.normalize()};
            CHECK(v2 == Vector2D{-1, 0});
        }
    }
}

TEST_CASE("[Vector2D] isZero() method", "[utils][Vector2D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Zero vector")
        {
            Vector2D<> const v1;
            CHECK(v1.isZero());
        }
        SECTION("Positive values")
        {
            Vector2D const v1{2, 3};
            CHECK_FALSE(v1.isZero());
        }
        SECTION("Positive and negatives values")
        {
            Vector2D const v1{-1, 2};
            CHECK_FALSE(v1.isZero());
        }
        SECTION("Semi-zero vector")
        {
            Vector2D const v1{0, -1};
            CHECK_FALSE(v1.isZero());
        }
    }
}

TEST_CASE(
    "[Vector2D] isHorizontal(), isVertical() and isDiagonal() methods",
    "[utils][Vector2D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Zero vector")
        {
            Vector2D<> const v1;
            CHECK(v1.isHorizontal());
            CHECK(v1.isVertical());
            CHECK(v1.isDiagonal());
        }
        SECTION("Horizontal")
        {
            Vector2D const v1{2, 0};
            CHECK(v1.isHorizontal());
            CHECK_FALSE(v1.isVertical());
            CHECK_FALSE(v1.isDiagonal());
        }
        SECTION("Vertical")
        {
            Vector2D const v1{0, 5};
            CHECK_FALSE(v1.isHorizontal());
            CHECK(v1.isVertical());
            CHECK_FALSE(v1.isDiagonal());
        }
        SECTION("Diagonal")
        {
            SECTION("Ascending")
            {
                Vector2D const v1{2, 2};
                CHECK_FALSE(v1.isHorizontal());
                CHECK_FALSE(v1.isVertical());
                CHECK(v1.isDiagonal());
            }
            SECTION("Descending")
            {
                Vector2D const v1{2, -2};
                CHECK_FALSE(v1.isHorizontal());
                CHECK_FALSE(v1.isVertical());
                CHECK(v1.isDiagonal());
            }
        }
    }
}

TEST_CASE("[Vector2D] Equality operator", "[utils][Vector2D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Different")
        {
            Vector2D const v1{2, 3};
            Vector2D const v2{-4, 2};
            CHECK_FALSE(v1 == v2);
            CHECK(v1 != v2);
        }
        SECTION("Equal")
        {
            Vector2D const v1{2, 3};
            Vector2D const v2{2, 3};
            CHECK(v1 == v2);
            CHECK_FALSE(v1 != v2);
        }
    }
}

TEST_CASE("[Vector2D] Addition operator", "[utils][Vector2D]")
{
    SECTION("Runtime tests")
    {
        Vector2D const v1{-2, 3};
        Vector2D const v2{4, 2};
        CHECK((v1 + v2) == Vector2D{2, 5});
        CHECK((v2 + v1) == Vector2D{2, 5});
    }
}

TEST_CASE("[Vector2D] Negation operator", "[utils][Vector2D]")
{
    SECTION("Runtime tests")
    {
        Vector2D const v1{-2, 3};
        CHECK(-v1 == Vector2D{2, -3});
        Vector2D const v2{4, -2};
        CHECK(-v2 == Vector2D{-4, 2});
        Vector2D const v3{2, 3};
        CHECK(-v3 == Vector2D{-2, -3});
        Vector2D const v4{-2, -3};
        CHECK(-v4 == Vector2D{2, 3});
    }
}

TEST_CASE("[Vector2D] Subtraction operator", "[utils][Vector2D]")
{
    SECTION("Runtime tests")
    {
        Vector2D const v1{-2, 3};
        Vector2D const v2{4, 2};
        CHECK((v1 - v2) == Vector2D{-6, 1});
        CHECK((v2 - v1) == Vector2D{6, -1});
    }
}

TEST_CASE("[Vector2D] Vector2D * scalar", "[utils][Vector2D]")
{
    SECTION("Runtime tests")
    {
        Vector2D const vector2D{2, 3};
        Vector2D const newVector2D{vector2D * 2};
        CHECK(newVector2D.getX() == 4);
        CHECK(newVector2D.getY() == 6);
    }
}

TEST_CASE("[Vector2D] scalar * Vector2D", "[utils][Vector2D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Positive scalar")
        {
            SECTION("Positive values")
            {
                Vector2D const vector2D{2, 3};
                Vector2D const newVector2D{2 * vector2D};
                CHECK(newVector2D.getX() == 4);
                CHECK(newVector2D.getY() == 6);
            }
            SECTION("Positive and negatives values")
            {
                Vector2D const vector2D{2, -3};
                Vector2D const newVector2D{2 * vector2D};
                CHECK(newVector2D.getX() == 4);
                CHECK(newVector2D.getY() == -6);
            }
        }
        SECTION("Negative scalar")
        {
            SECTION("Positive values")
            {
                Vector2D const vector2D{2, 3};
                Vector2D const newVector2D{-2 * vector2D};
                CHECK(newVector2D.getX() == -4);
                CHECK(newVector2D.getY() == -6);
            }
            SECTION("Positive and negatives values")
            {
                Vector2D const vector2D{2, -3};
                Vector2D const newVector2D{-2 * vector2D};
                CHECK(newVector2D.getX() == -4);
                CHECK(newVector2D.getY() == 6);
            }
        }
    }
}
