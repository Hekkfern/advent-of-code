#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Vector2D.hpp>

using namespace utils::geometry2d;

TEST_CASE("[Vector2D] create() method", "[utils][Vector2D]")
{
    SECTION("Positive values")
    {
        Vector2D<> const vector2D{Vector2D<>::create(2, 4)};
        CHECK(vector2D.getX() == 2);
        CHECK(vector2D.getY() == 4);
        auto const coords{vector2D.getCoordinates()};
        CHECK(coords.mX == 2);
        CHECK(coords.mY == 4);
    }
    SECTION("Positive and negatives values")
    {
        Vector2D<> const vector2D{Vector2D<>::create(-2, 3)};
        CHECK(vector2D.getX() == -2);
        CHECK(vector2D.getY() == 3);
        auto const coords{vector2D.getCoordinates()};
        CHECK(coords.mX == -2);
        CHECK(coords.mY == 3);
    }
}

TEST_CASE("[Vector2D] Constructor", "[utils][Vector2D]")
{
    SECTION("Default constructor")
    {
        Vector2D<> const vector2D;
        CHECK(vector2D.getX() == 0);
        CHECK(vector2D.getY() == 0);
        auto const coords{vector2D.getCoordinates()};
        CHECK(coords.mX == 0);
        CHECK(coords.mY == 0);
    }
    SECTION("Parametrized constructor")
    {
        SECTION("Positive values")
        {
            Vector2D<> const vector2D{2, 4};
            CHECK(vector2D.getX() == 2);
            CHECK(vector2D.getY() == 4);
            auto const coords{vector2D.getCoordinates()};
            CHECK(coords.mX == 2);
            CHECK(coords.mY == 4);
        }
        SECTION("Positive and negatives values")
        {
            Vector2D<> const vector2D{-2, 3};
            CHECK(vector2D.getX() == -2);
            CHECK(vector2D.getY() == 3);
            auto const coords{vector2D.getCoordinates()};
            CHECK(coords.mX == -2);
            CHECK(coords.mY == 3);
        }
    }
    SECTION("Group constructor")
    {
        SECTION("Positive values")
        {
            Vector2D<> const vector2D{Coord2D<>{2, 4}};
            CHECK(vector2D.getX() == 2);
            CHECK(vector2D.getY() == 4);
            auto const coords{vector2D.getCoordinates()};
            CHECK(coords.mX == 2);
            CHECK(coords.mY == 4);
        }
        SECTION("Positive and negatives values")
        {
            Vector2D<> const vector2D{Coord2D<>{-2, 3}};
            CHECK(vector2D.getX() == -2);
            CHECK(vector2D.getY() == 3);
            auto const coords{vector2D.getCoordinates()};
            CHECK(coords.mX == -2);
            CHECK(coords.mY == 3);
        }
    }
}

TEST_CASE("[Vector2D] range() method", "[utils][Vector2D]")
{
    SECTION("Zero vector")
    {
        Vector2D<> const v1;
        CHECK(v1.range() == 0UL);
    }
    SECTION("Positive values")
    {
        const Vector2D v1{2, 3};
        CHECK(v1.range() == 3UL);
    }
    SECTION("Positive and negatives values")
    {
        const Vector2D v1{-2, 1};
        CHECK(v1.range() == 2UL);
    }
}

TEST_CASE("[Vector2D] distance() method", "[utils][Vector2D]")
{
    SECTION("Zero vector")
    {
        Vector2D<> const v1;
        CHECK(v1.distance() == 0UL);
    }
    SECTION("Positive values")
    {
        const Vector2D v1{2, 3};
        CHECK(v1.distance() == 5UL);
    }
    SECTION("Positive and negatives values")
    {
        const Vector2D v1{-2, 1};
        CHECK(v1.distance() == 3UL);
    }
}

TEST_CASE("[Vector2D] normalize() method", "[utils][Vector2D]")
{
    SECTION("Zero vector")
    {
        Vector2D<> v1;
        v1.normalize();
        CHECK(v1 == Vector2D{0, 0});
    }
    SECTION("Positive values")
    {
        Vector2D v1{2, 3};
        v1.normalize();
        CHECK(v1 == Vector2D{1, 1});
    }
    SECTION("Positive and negatives values")
    {
        Vector2D v1{-2, 1};
        v1.normalize();
        CHECK(v1 == Vector2D{-1, 1});
    }
    SECTION("Already-normalized vector")
    {
        Vector2D v1{-1, 0};
        v1.normalize();
        CHECK(v1 == Vector2D{-1, 0});
    }
}

TEST_CASE("[Vector2D] getNormalized() method", "[utils][Vector2D]")
{
    SECTION("Zero vector")
    {
        Vector2D<> const v1;
        CHECK(v1.getNormalized() == Vector2D{0, 0});
    }
    SECTION("Positive values")
    {
        const Vector2D v1{2, 3};
        CHECK(v1.getNormalized() == Vector2D{1, 1});
    }
    SECTION("Positive and negatives values")
    {
        const Vector2D v1{-2, 1};
        CHECK(v1.getNormalized() == Vector2D{-1, 1});
    }
    SECTION("Already-normalized vector")
    {
        const Vector2D v1{-1, 0};
        CHECK(v1.getNormalized() == Vector2D{-1, 0});
    }
}

TEST_CASE("[Vector2D] isZero() method", "[utils][Vector2D]")
{
    SECTION("Zero vector")
    {
        Vector2D<> const v1;
        CHECK(v1.isZero());
    }
    SECTION("Positive values")
    {
        const Vector2D v2{2, 3};
        CHECK_FALSE(v2.isZero());
    }
    SECTION("Positive and negatives values")
    {
        const Vector2D v3{-1, 2};
        CHECK_FALSE(v3.isZero());
    }
    SECTION("Semi-zero vector")
    {
        const Vector2D v4{0, -1};
        CHECK_FALSE(v4.isZero());
    }
}

TEST_CASE("[Vector2D] Equality operator", "[utils][Vector2D]")
{
    SECTION("Different")
    {
        const Vector2D v1{2, 3};
        const Vector2D v2{-4, 2};
        CHECK_FALSE(v1 == v2);
        CHECK(v1 != v2);
    }
    SECTION("Equal")
    {
        const Vector2D v1{2, 3};
        const Vector2D v2{2, 3};
        CHECK(v1 == v2);
        CHECK_FALSE(v1 != v2);
    }
}

TEST_CASE("[Vector2D] Addition operator", "[utils][Vector2D]")
{
    const Vector2D v1{-2, 3};
    const Vector2D v2{4, 2};
    CHECK((v1 + v2) == Vector2D{2, 5});
    CHECK((v2 + v1) == Vector2D{2, 5});
}

TEST_CASE("[Vector2D] Negation operator", "[utils][Vector2D]")
{
    const Vector2D v1{-2, 3};
    const Vector2D v2{4, -2};
    CHECK(-v1 == Vector2D{2, -3});
    CHECK(-v2 == Vector2D{-4, 2});
}

TEST_CASE("[Vector2D] Subtraction operator", "[utils][Vector2D]")
{
    const Vector2D v1{-2, 3};
    const Vector2D v2{4, 2};
    CHECK((v1 - v2) == Vector2D{-6, 1});
    CHECK((v2 - v1) == Vector2D{6, -1});
}

TEST_CASE("[Vector2D] Vector2D * scalar", "[utils][Vector2D]")
{
    const Vector2D vector2D{2, 3};
    const Vector2D newVector2D{vector2D * 2};
    CHECK(newVector2D.getX() == 4);
    CHECK(newVector2D.getY() == 6);
}

TEST_CASE("[Vector2D] scalar * Vector2D", "[utils][Vector2D]")
{
    const Vector2D vector2D{2, 3};
    const Vector2D newVector2D{2 * vector2D};
    CHECK(newVector2D.getX() == 4);
    CHECK(newVector2D.getY() == 6);
}
