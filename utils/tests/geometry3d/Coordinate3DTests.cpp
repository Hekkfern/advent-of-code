#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry3d/Coordinate3D.hpp>

using namespace utils::geometry3d;

TEST_CASE("[Coordinate3D] Constructor", "[utils][Coordinate3D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Default constructor")
        {
            Coordinate3D<> const coords;
            CHECK(coords.getX() == 0);
            CHECK(coords.getY() == 0);
            CHECK(coords.getZ() == 0);
        }
        SECTION("Parametrized constructor")
        {
            Coordinate3D<> const coords{1, 2, 3};
            CHECK(coords.getX() == 1);
            CHECK(coords.getY() == 2);
            CHECK(coords.getZ() == 3);
        }
    }
    SECTION("Static tests")
    {
        SECTION("Default constructor")
        {
            constexpr Coordinate3D<> coords;
            STATIC_CHECK(coords.getX() == 0);
            STATIC_CHECK(coords.getY() == 0);
            STATIC_CHECK(coords.getZ() == 0);
        }
        SECTION("Parametrized constructor")
        {
            constexpr Coordinate3D<> coords{1, 2, 3};
            STATIC_CHECK(coords.getX() == 1);
            STATIC_CHECK(coords.getY() == 2);
            STATIC_CHECK(coords.getZ() == 3);
        }
    }
}

TEST_CASE("[Coordinate3D] Equality operator", "[utils][Coordinate3D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Equal")
        {
            Coordinate3D<> const coords1{1, 2, 3};
            Coordinate3D<> const coords2{1, 2, 3};
            CHECK(coords1 == coords2);
            CHECK_FALSE(coords1 != coords2);
        }
        SECTION("Different")
        {
            Coordinate3D<> const coords1{1, 2, 3};
            Coordinate3D<> const coords2{7, 10, 11};
            CHECK_FALSE(coords1 == coords2);
            CHECK(coords1 != coords2);
        }
    }
    SECTION("Static tests")
    {
        SECTION("Equal")
        {
            constexpr Coordinate3D<> coords1{1, 2, 3};
            constexpr Coordinate3D<> coords2{1, 2, 3};
            STATIC_CHECK(coords1 == coords2);
            STATIC_CHECK_FALSE(coords1 != coords2);
        }
        SECTION("Different")
        {
            constexpr Coordinate3D<> coords1{1, 2, 3};
            constexpr Coordinate3D<> coords2{7, 10, 11};
            STATIC_CHECK_FALSE(coords1 == coords2);
            STATIC_CHECK(coords1 != coords2);
        }
    }
}

TEST_CASE("[Coordinate3D] Structured binding", "[utils][Coordinate3D]")
{
    Coordinate3D<> const coords{1, 2, 3};
    auto const [x, y, z]{coords};
    CHECK(x == 1);
    CHECK(y == 2);
    CHECK(z == 3);
}

TEST_CASE("[Coordinate3D] Hash calculation", "[utils][Coordinate3D]")
{
    std::hash<Coordinate3D<int32_t>> hasher;
    Coordinate3D<> const coords1{1, 7, 2};
    Coordinate3D<> const coords2{1, 7, 2};
    Coordinate3D<> const coords3{4, 8, 1};

    SECTION("Same") { REQUIRE(hasher(coords1) == hasher(coords1)); }

    SECTION("Equal") { REQUIRE(hasher(coords1) == hasher(coords2)); }

    SECTION("Different") { REQUIRE(hasher(coords1) != hasher(coords3)); }
}
