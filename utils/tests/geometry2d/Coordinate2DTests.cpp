#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Coordinate2D.hpp>

using namespace utils::geometry2d;

TEST_CASE("[Coordinate2D] Constructor", "[utils][Coordinate2D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Default constructor")
        {
            Coordinate2D<> const coords;
            CHECK(coords.getX() == 0);
            CHECK(coords.getY() == 0);
        }
        SECTION("Parametrized constructor")
        {
            Coordinate2D const coords{1, 2};
            CHECK(coords.getX() == 1);
            CHECK(coords.getY() == 2);
        }
    }
    SECTION("Static tests")
    {
        SECTION("Default constructor")
        {
            constexpr Coordinate2D<> coords;
            STATIC_CHECK(coords.getX() == 0);
            STATIC_CHECK(coords.getY() == 0);
        }
        SECTION("Parametrized constructor")
        {
            constexpr Coordinate2D coords{1, 2};
            STATIC_CHECK(coords.getX() == 1);
            STATIC_CHECK(coords.getY() == 2);
        }
    }
}

TEST_CASE("[Coordinate2D] Equality operator", "[utils][Coordinate2D]")
{
    SECTION("Runtime tests")
    {
        SECTION("Equal")
        {
            Coordinate2D const coords1{1, 2};
            Coordinate2D const coords2{1, 2};
            CHECK(coords1 == coords2);
            CHECK_FALSE(coords1 != coords2);
        }
        SECTION("Different")
        {
            Coordinate2D const coords1{1, 2};
            Coordinate2D const coords2{7, 10};
            CHECK_FALSE(coords1 == coords2);
            CHECK(coords1 != coords2);
        }
    }
    SECTION("Static tests")
    {
        SECTION("Equal")
        {
            constexpr Coordinate2D coords1{1, 2};
            constexpr Coordinate2D coords2{1, 2};
            STATIC_CHECK(coords1 == coords2);
            STATIC_CHECK_FALSE(coords1 != coords2);
        }
        SECTION("Different")
        {
            constexpr Coordinate2D coords1{1, 2};
            constexpr Coordinate2D coords2{7, 10};
            STATIC_CHECK_FALSE(coords1 == coords2);
            STATIC_CHECK(coords1 != coords2);
        }
    }
}

TEST_CASE("[Coordinate2D] Structured binding", "[utils][Coordinate2D]")
{
    Coordinate2D const coords{1, 2};
    auto const [x, y]{coords};
    CHECK(x == 1);
    CHECK(y == 2);
}

TEST_CASE("[Coordinate2D] move() method", "[utils][Coordinate2D]")
{
    SECTION("Signed integer")
    {
        SECTION("Left limit")
        {
            Coordinate2D const coords{std::numeric_limits<int32_t>::min(), 0};
            auto const result{coords.move(Direction2D::Left)};
            REQUIRE_FALSE(result);
        }
        SECTION("Right limit")
        {
            Coordinate2D const coords{std::numeric_limits<int32_t>::max(), 0};
            auto const result{coords.move(Direction2D::Right)};
            REQUIRE_FALSE(result);
        }
        SECTION("Normal range")
        {
            Coordinate2D const coords{1, 7};
            auto const result{coords.move(Direction2D::Left)};
            REQUIRE(result);
            CHECK(*result == Coordinate2D{0, 7});
        }
    }
    SECTION("Unsigned integer")
    {
        SECTION("Left limit")
        {
            Coordinate2D<uint32_t> const coords{
                std::numeric_limits<uint32_t>::min(), 0U};
            auto const result{coords.move(Direction2D::Left)};
            REQUIRE_FALSE(result);
        }
        SECTION("Right limit")
        {
            Coordinate2D<uint32_t> const coords{
                std::numeric_limits<uint32_t>::max(), 0U};
            auto const result{coords.move(Direction2D::Right)};
            REQUIRE_FALSE(result);
        }
        SECTION("Normal range")
        {
            Coordinate2D<uint32_t> const coords{1U, 7U};
            auto const result{coords.move(Direction2D::Left)};
            REQUIRE(result);
            CHECK(*result == Coordinate2D<uint32_t>{0U, 7U});
        }
    }
}

TEST_CASE("[Coordinate2D] Hash calculation", "[utils][Coordinate2D]")
{
    std::hash<Coordinate2D<int32_t>> hasher;
    Coordinate2D const coords1{1, 7};
    Coordinate2D const coords2{1, 7};
    Coordinate2D const coords3{4, 8};

    SECTION("Same") { REQUIRE(hasher(coords1) == hasher(coords1)); }

    SECTION("Equal") { REQUIRE(hasher(coords1) == hasher(coords2)); }

    SECTION("Different") { REQUIRE(hasher(coords1) != hasher(coords3)); }
}
