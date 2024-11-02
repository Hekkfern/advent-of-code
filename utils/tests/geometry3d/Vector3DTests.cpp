#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <numbers>
#include <utils/geometry3d/Vector3D.hpp>

using namespace utils::geometry3d;

TEST_CASE("[Vector3D] create() method", "[utils][Vector3D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Positive values")
        {
            Vector3D<> const vector3D{Vector3D<>::create(2, 4, 1)};
            CHECK(vector3D.getX() == 2);
            CHECK(vector3D.getY() == 4);
            CHECK(vector3D.getZ() == 1);
            auto const coords{vector3D.getCoordinates()};
            CHECK(coords.getX() == 2);
            CHECK(coords.getY() == 4);
            CHECK(coords.getZ() == 1);
        }
        SECTION("Positive and negatives values")
        {
            Vector3D<> const vector3D{Vector3D<>::create(-2, 3, 1)};
            CHECK(vector3D.getX() == -2);
            CHECK(vector3D.getY() == 3);
            CHECK(vector3D.getZ() == 1);
            auto const coords{vector3D.getCoordinates()};
            CHECK(coords.getX() == -2);
            CHECK(coords.getY() == 3);
            CHECK(coords.getZ() == 1);
        }
    }
}

TEST_CASE("[Vector3D] Constructor", "[utils][Vector3D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Default constructor")
        {
            Vector3D<> const vector3D;
            CHECK(vector3D.getX() == 0);
            CHECK(vector3D.getY() == 0);
            CHECK(vector3D.getZ() == 0);
            auto const coords{vector3D.getCoordinates()};
            CHECK(coords.getX() == 0);
            CHECK(coords.getY() == 0);
            CHECK(coords.getZ() == 0);
        }
        SECTION("Parametrized constructor")
        {
            SECTION("Positive values")
            {
                Vector3D<> const vector3D{2, 4, 1};
                CHECK(vector3D.getX() == 2);
                CHECK(vector3D.getY() == 4);
                CHECK(vector3D.getZ() == 1);
                auto const coords{vector3D.getCoordinates()};
                CHECK(coords.getX() == 2);
                CHECK(coords.getY() == 4);
                CHECK(coords.getZ() == 1);
            }
            SECTION("Positive and negatives values")
            {
                Vector3D<> const vector3D{-2, 3, 1};
                CHECK(vector3D.getX() == -2);
                CHECK(vector3D.getY() == 3);
                CHECK(vector3D.getZ() == 1);
                auto const coords{vector3D.getCoordinates()};
                CHECK(coords.getX() == -2);
                CHECK(coords.getY() == 3);
                CHECK(coords.getZ() == 1);
            }
        }
        SECTION("Group constructor")
        {
            SECTION("Positive values")
            {
                Vector3D<> const vector3D{Coordinate3D{2, 4, 1}};
                CHECK(vector3D.getX() == 2);
                CHECK(vector3D.getY() == 4);
                CHECK(vector3D.getZ() == 1);
                auto const coords{vector3D.getCoordinates()};
                CHECK(coords.getX() == 2);
                CHECK(coords.getY() == 4);
                CHECK(coords.getZ() == 1);
            }
            SECTION("Positive and negatives values")
            {
                Vector3D<> const vector3D{Coordinate3D{-2, 3, 1}};
                CHECK(vector3D.getX() == -2);
                CHECK(vector3D.getY() == 3);
                CHECK(vector3D.getZ() == 1);
                auto const coords{vector3D.getCoordinates()};
                CHECK(coords.getX() == -2);
                CHECK(coords.getY() == 3);
                CHECK(coords.getZ() == 1);
            }
        }
    }
}

TEST_CASE("[Vector3D] size() method", "[utils][Vector3D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Zero vector")
        {
            Vector3D<> const v1;
            CHECK(v1.size() == std::to_array<uint64_t>({0ULL, 0ULL, 0ULL}));
        }
        SECTION("Positive values")
        {
            Vector3D<> const v1{2, 3, 1};
            CHECK(v1.size() == std::to_array<uint64_t>({2ULL, 3ULL, 1ULL}));
        }
        SECTION("Positive and negatives values")
        {
            Vector3D<> const v1{-2, 1, 1};
            CHECK(v1.size() == std::to_array<uint64_t>({2ULL, 1ULL, 1ULL}));
        }
    }
}

TEST_CASE("[Vector3D] range() method", "[utils][Vector3D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Zero vector")
        {
            Vector3D<> const v1;
            CHECK(v1.range() == 0ULL);
        }
        SECTION("Positive values")
        {
            Vector3D<> const v1{2, 3, 1};
            CHECK(v1.range() == 3ULL);
        }
        SECTION("Positive and negatives values")
        {
            Vector3D<> const v1{-2, 1, 1};
            CHECK(v1.range() == 2ULL);
        }
    }
}

TEST_CASE("[Vector3D] distance() method", "[utils][Vector3D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Zero vector")
        {
            Vector3D<> const v1;
            CHECK(v1.distance() == 0ULL);
        }
        SECTION("Positive values")
        {
            Vector3D<> const v1{2, 3, 1};
            CHECK(v1.distance() == 6ULL);
        }
        SECTION("Positive and negatives values")
        {
            Vector3D<> const v1{-2, 1, 1};
            CHECK(v1.distance() == 4ULL);
        }
    }
}

TEST_CASE("[Vector3D] normalize() method", "[utils][Vector3D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Zero vector")
        {
            Vector3D<> const v1;
            auto const v2{v1.normalize()};
            CHECK(v2 == Vector3D{0, 0, 0});
        }
        SECTION("Positive values")
        {
            Vector3D<> const v1{2, 3, 1};
            auto const v2{v1.normalize()};
            CHECK(v2 == Vector3D{1, 1, 1});
        }
        SECTION("Positive and negatives values")
        {
            Vector3D<> const v1{-2, 1, 1};
            auto const v2{v1.normalize()};
            CHECK(v2 == Vector3D{-1, 1, 1});
        }
        SECTION("Already-normalized vector")
        {
            Vector3D<> const v1{-1, 0, 0};
            auto const v2{v1.normalize()};
            CHECK(v2 == Vector3D{-1, 0, 0});
        }
    }
}

TEST_CASE("[Vector3D] is() method", "[utils][Vector3D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Zero vector")
        {
            Vector3D<> const v;
            CHECK(v.is() == Vector3DType::Zero);
        }
        SECTION("Positive values")
        {
            Vector3D const v{2, 3, 1};
            CHECK(v.is() == Vector3DType::Arbitrary);
        }
        SECTION("Positive and negatives values")
        {
            Vector3D const v{-1, 2, 1};
            CHECK(v.is() == Vector3DType::Arbitrary);
        }
        SECTION("Across X Axis")
        {
            SECTION("Right")
            {
                Vector3D const v{1, 0, 0};
                CHECK(v.is() == Vector3DType::AcrossXAxis);
            }
            SECTION("Left")
            {
                Vector3D const v{-3, 0, 0};
                CHECK(v.is() == Vector3DType::AcrossXAxis);
            }
        }
        SECTION("Across Y Axis")
        {
            SECTION("Right")
            {
                Vector3D const v{0, 1, 0};
                CHECK(v.is() == Vector3DType::AcrossYAxis);
            }
            SECTION("Left")
            {
                Vector3D const v{0, -1, 0};
                CHECK(v.is() == Vector3DType::AcrossYAxis);
            }
        }
        SECTION("Across Z Axis")
        {
            SECTION("Right")
            {
                Vector3D const v{0, 0, 1};
                CHECK(v.is() == Vector3DType::AcrossZAxis);
            }
            SECTION("Left")
            {
                Vector3D const v{0, 0, -1};
                CHECK(v.is() == Vector3DType::AcrossZAxis);
            }
        }
    }
}

TEST_CASE("[Vector3D] Equality operator", "[utils][Vector3D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Different")
        {
            Vector3D const v1{2, 3, 1};
            Vector3D const v2{-4, 2, 2};
            CHECK_FALSE(v1 == v2);
            CHECK(v1 != v2);
        }
        SECTION("Equal")
        {
            Vector3D const v1{2, 3, 1};
            Vector3D const v2{2, 3, 1};
            CHECK(v1 == v2);
            CHECK_FALSE(v1 != v2);
        }
    }
}

TEST_CASE("[Vector3D] Addition operator", "[utils][Vector3D]")
{
    SECTION("Runtime tests")
    {
        Vector3D const v1{-2, 3, 1};
        Vector3D const v2{4, 2, 1};
        CHECK((v1 + v2) == Vector3D{2, 5, 2});
        CHECK((v2 + v1) == Vector3D{2, 5, 2});
    }
}

TEST_CASE("[Vector3D] Negation operator", "[utils][Vector3D]")
{
    SECTION("Runtime tests")
    {
        Vector3D const v1{-2, 3, 1};
        CHECK(-v1 == Vector3D{2, -3, -1});
        Vector3D const v2{4, -2, 1};
        CHECK(-v2 == Vector3D{-4, 2, -1});
        Vector3D const v3{2, 3, -1};
        CHECK(-v3 == Vector3D{-2, -3, 1});
        Vector3D const v4{-2, -3, -1};
        CHECK(-v4 == Vector3D{2, 3, 1});
    }
}

TEST_CASE("[Vector3D] Subtraction operator", "[utils][Vector3D]")
{
    SECTION("Runtime tests")
    {
        Vector3D const v1{-2, 3, 2};
        Vector3D const v2{4, 2, 1};
        CHECK((v1 - v2) == Vector3D{-6, 1, 1});
        CHECK((v2 - v1) == Vector3D{6, -1, -1});
    }
}

TEST_CASE("[Vector3D] Vector3D * scalar", "[utils][Vector3D]")
{
    SECTION("Runtime tests")
    {
        Vector3D const vector3D{2, 3, 1};
        Vector3D const newVector3D{vector3D * 2};
        CHECK(newVector3D.getX() == 4);
        CHECK(newVector3D.getY() == 6);
        CHECK(newVector3D.getZ() == 2);
    }
}

TEST_CASE("[Vector3D] scalar * Vector3D", "[utils][Vector3D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Positive scalar")
        {
            SECTION("Positive values")
            {
                Vector3D const vector3D{2, 3, 1};
                Vector3D const newVector3D{2 * vector3D};
                CHECK(newVector3D.getX() == 4);
                CHECK(newVector3D.getY() == 6);
                CHECK(newVector3D.getZ() == 2);
            }
            SECTION("Positive and negatives values")
            {
                Vector3D const vector3D{2, -3, -1};
                Vector3D const newVector3D{2 * vector3D};
                CHECK(newVector3D.getX() == 4);
                CHECK(newVector3D.getY() == -6);
                CHECK(newVector3D.getZ() == -2);
            }
        }
        SECTION("Negative scalar")
        {
            SECTION("Positive values")
            {
                Vector3D const vector3D{2, 3, 1};
                Vector3D const newVector3D{-2 * vector3D};
                CHECK(newVector3D.getX() == -4);
                CHECK(newVector3D.getY() == -6);
                CHECK(newVector3D.getZ() == -2);
            }
            SECTION("Positive and negatives values")
            {
                Vector3D const vector3D{2, -3, -1};
                Vector3D const newVector3D{-2 * vector3D};
                CHECK(newVector3D.getX() == -4);
                CHECK(newVector3D.getY() == 6);
                CHECK(newVector3D.getZ() == 2);
            }
        }
    }
}
