#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry3d/Vector3D.hpp>

using namespace utils::geometry3d;

TEST_CASE("[Vector3D] create() method", "[utils][Vector3D]")
{
    SECTION("Positive values")
    {
        Vector3D<> const vector3D{Vector3D<>::create(2, 4, 5)};
        CHECK(vector3D.getX() == 2);
        CHECK(vector3D.getY() == 4);
        CHECK(vector3D.getZ() == 5);
        auto const coords{vector3D.getCoordinates()};
        CHECK(coords.mX == 2);
        CHECK(coords.mY == 4);
        CHECK(coords.mZ == 5);
    }
    SECTION("Positive and negatives values")
    {
        Vector3D<> const vector3D{Vector3D<>::create(-2, 3, -1)};
        CHECK(vector3D.getX() == -2);
        CHECK(vector3D.getY() == 3);
        CHECK(vector3D.getZ() == -1);
        auto const coords{vector3D.getCoordinates()};
        CHECK(coords.mX == -2);
        CHECK(coords.mY == 3);
        CHECK(coords.mZ == -1);
    }
}

TEST_CASE("[Vector3D] Constructor", "[utils][Vector3D]")
{
    SECTION("Default constructor")
    {
        Vector3D<> const vector3D;
        CHECK(vector3D.getX() == 0);
        CHECK(vector3D.getY() == 0);
        CHECK(vector3D.getZ() == 0);
        auto const coords{vector3D.getCoordinates()};
        CHECK(coords.mX == 0);
        CHECK(coords.mY == 0);
        CHECK(coords.mZ == 0);
    }
    SECTION("Parametrized constructor")
    {
        SECTION("Positive values")
        {
            Vector3D<> const vector3D{2, 4, 5};
            CHECK(vector3D.getX() == 2);
            CHECK(vector3D.getY() == 4);
            CHECK(vector3D.getZ() == 5);
            auto const coords{vector3D.getCoordinates()};
            CHECK(coords.mX == 2);
            CHECK(coords.mY == 4);
            CHECK(coords.mZ == 5);
        }
        SECTION("Positive and negatives values")
        {
            Vector3D<> const vector3D{-2, 3, -1};
            CHECK(vector3D.getX() == -2);
            CHECK(vector3D.getY() == 3);
            CHECK(vector3D.getZ() == -1);
            auto const coords{vector3D.getCoordinates()};
            CHECK(coords.mX == -2);
            CHECK(coords.mY == 3);
            CHECK(coords.mZ == -1);
        }
    }
    SECTION("Group constructor")
    {
        SECTION("Positive values")
        {
            Vector3D<> const vector3D{Coord3D<>{2, 4, 5}};
            CHECK(vector3D.getX() == 2);
            CHECK(vector3D.getY() == 4);
            CHECK(vector3D.getZ() == 5);
            auto const coords{vector3D.getCoordinates()};
            CHECK(coords.mX == 2);
            CHECK(coords.mY == 4);
            CHECK(coords.mZ == 5);
        }
        SECTION("Positive and negatives values")
        {
            Vector3D<> const vector3D{Coord3D<>{-2, 3, -1}};
            CHECK(vector3D.getX() == -2);
            CHECK(vector3D.getY() == 3);
            CHECK(vector3D.getZ() == -1);
            auto const coords{vector3D.getCoordinates()};
            CHECK(coords.mX == -2);
            CHECK(coords.mY == 3);
            CHECK(coords.mZ == -1);
        }
    }
}

TEST_CASE("[Vector3D] range() method", "[utils][Vector3D]")
{
    SECTION("Zero vector")
    {
        Vector3D<> const v1;
        CHECK(v1.range() == 0UL);
    }
    SECTION("Positive values")
    {
        Vector3D const v1{2, 3, 3};
        CHECK(v1.range() == 3UL);
    }
    SECTION("Positive and negatives values")
    {
        Vector3D const v1{-2, 1, -1};
        CHECK(v1.range() == 2UL);
    }
}

TEST_CASE("[Vector3D] distance() method", "[utils][Vector3D]")
{
    SECTION("Zero vector")
    {
        Vector3D<> const v1;
        CHECK(v1.distance() == 0UL);
    }
    SECTION("Positive values")
    {
        Vector3D const v1{2, 3, 2};
        CHECK(v1.distance() == 7UL);
    }
    SECTION("Positive and negatives values")
    {
        Vector3D const v1{-2, 1, 2};
        CHECK(v1.distance() == 5UL);
    }
}

TEST_CASE("[Vector3D] normalize() method", "[utils][Vector3D]")
{
    SECTION("Zero vector")
    {
        Vector3D<> v1;
        v1.normalize();
        CHECK(v1 == Vector3D{0, 0, 0});
    }
    SECTION("Positive values")
    {
        Vector3D v1{2, 3, 2};
        v1.normalize();
        CHECK(v1 == Vector3D{1, 1, 1});
    }
    SECTION("Positive and negatives values")
    {
        Vector3D v1{-2, 1, -6};
        v1.normalize();
        CHECK(v1 == Vector3D{-1, 1, -1});
    }
    SECTION("Already-normalized vector")
    {
        Vector3D v1{-1, 0, 0};
        v1.normalize();
        CHECK(v1 == Vector3D{-1, 0, 0});
    }
}

TEST_CASE("[Vector3D] getNormalized() method", "[utils][Vector3D]")
{
    SECTION("Zero vector")
    {
        Vector3D<> const v1;
        CHECK(v1.getNormalized() == Vector3D{0, 0, 0});
    }
    SECTION("Positive values")
    {
        Vector3D const v1{2, 3, 2};
        CHECK(v1.getNormalized() == Vector3D{1, 1, 1});
    }
    SECTION("Positive and negatives values")
    {
        Vector3D const v1{-2, 1, -6};
        CHECK(v1.getNormalized() == Vector3D{-1, 1, -1});
    }
    SECTION("Already-normalized vector")
    {
        Vector3D const v1{-1, 0, 0};
        CHECK(v1.getNormalized() == Vector3D{-1, 0, 0});
    }
}

TEST_CASE("[Vector3D] isZero() method", "[utils][Vector3D]")
{
    SECTION("Zero vector")
    {
        Vector3D<> const v1;
        CHECK(v1.isZero());
    }
    SECTION("Positive values")
    {
        Vector3D const v2{2, 3, 2};
        CHECK_FALSE(v2.isZero());
    }
    SECTION("Positive and negatives values")
    {
        Vector3D const v3{-1, 2, -5};
        CHECK_FALSE(v3.isZero());
    }
    SECTION("Semi-zero vector")
    {
        Vector3D const v4{0, -1, 0};
        CHECK_FALSE(v4.isZero());
    }
}

TEST_CASE("[Vector3D] Equality operator", "[utils][Vector3D]")
{
    SECTION("Different")
    {
        Vector3D const v1{2, 3, 5};
        Vector3D const v2{-4, 2, 4};
        CHECK_FALSE(v1 == v2);
        CHECK(v1 != v2);
    }
    SECTION("Equal")
    {
        Vector3D const v1{2, 3, 5};
        Vector3D const v2{2, 3, 5};
        CHECK(v1 == v2);
        CHECK_FALSE(v1 != v2);
    }
}

TEST_CASE("[Vector3D] Addition operator", "[utils][Vector3D]")
{
    Vector3D const v1{-2, 3, 1};
    Vector3D const v2{4, 2, 2};
    CHECK((v1 + v2) == Vector3D{2, 5, 3});
    CHECK((v2 + v1) == Vector3D{2, 5, 3});
}

TEST_CASE("[Vector3D] Negation operator", "[utils][Vector3D]")
{
    Vector3D const v1{-2, 3, 2};
    Vector3D const v2{4, -2, 1};
    CHECK(-v1 == Vector3D{2, -3, -2});
    CHECK(-v2 == Vector3D{-4, 2, -1});
}

TEST_CASE("[Vector3D] Subtraction operator", "[utils][Vector3D]")
{
    Vector3D const v1{-2, 3, 2};
    Vector3D const v2{4, 2, 1};
    CHECK((v1 - v2) == Vector3D{-6, 1, 1});
    CHECK((v2 - v1) == Vector3D{6, -1, -1});
}

TEST_CASE("[Vector3D] Vector3D * scalar", "[utils][Vector3D]")
{
    Vector3D const vector3D{2, 3, 1};
    Vector3D const newVector3D{vector3D * 2};
    CHECK(newVector3D.getX() == 4);
    CHECK(newVector3D.getY() == 6);
    CHECK(newVector3D.getZ() == 2);
}

TEST_CASE("[Vector3D] scalar * Vector3D", "[utils][Vector3D]")
{
    Vector3D const vector3D{2, 3, 1};
    Vector3D const newVector3D{2 * vector3D};
    CHECK(newVector3D.getX() == 4);
    CHECK(newVector3D.getY() == 6);
    CHECK(newVector3D.getZ() == 2);
}
