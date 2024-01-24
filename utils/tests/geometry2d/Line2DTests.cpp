#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Line2D.hpp>

using namespace utils::geometry2d;

TEST_CASE("[Line2D] Constructor", "[utils][Line2D]")
{
    SECTION("Default constructor")
    {
        Line2D const line2D;
        auto const thisSize{line2D.size()};
        CHECK(thisSize[0] == 0U);
        CHECK(thisSize[1] == 0U);
        CHECK(line2D.distance() == 0ULL);
        auto const vertexes{line2D.getVertexes()};
        CHECK(vertexes[0] == Point2D{});
        CHECK(vertexes[1] == Point2D{});
    }
    SECTION("Parametrized constructor")
    {
        SECTION("Positive values")
        {
            Line2D const line2D{Point2D{1, 1}, Point2D{2, 3}};
            auto const thisSize{line2D.size()};
            CHECK(thisSize[0] == 1U);
            CHECK(thisSize[1] == 2U);
            CHECK(line2D.distance() == 3ULL);
            auto const vertexes{line2D.getVertexes()};
            CHECK(vertexes[0] == Point2D{1, 1});
            CHECK(vertexes[1] == Point2D{2, 3});
        }
        SECTION("Positive and negatives values")
        {
            Line2D const line2D{Point2D{-1, 1}, Point2D{2, -3}};
            auto const thisSize{line2D.size()};
            CHECK(thisSize[0] == 3U);
            CHECK(thisSize[1] == 4U);
            CHECK(line2D.distance() == 7ULL);
            auto const vertexes{line2D.getVertexes()};
            CHECK(vertexes[0] == Point2D{-1, 1});
            CHECK(vertexes[1] == Point2D{2, -3});
        }
    }
}

TEST_CASE("[Line2D] isHorizontal, isVertical and isDiagonal", "[utils][Line2D]")
{
    SECTION("Horizontal")
    {
        Line2D const line2D{Point2D{1, 1}, Point2D{5, 1}};
        CHECK(line2D.isHorizontal());
        CHECK_FALSE(line2D.isVertical());
        CHECK_FALSE(line2D.isDiagonal());
    }
    SECTION("Vertical")
    {
        Line2D const line2D{Point2D{1, 1}, Point2D{1, 6}};
        CHECK_FALSE(line2D.isHorizontal());
        CHECK(line2D.isVertical());
        CHECK_FALSE(line2D.isDiagonal());
    }
    SECTION("Diagonal")
    {
        SECTION("Ascending")
        {
            Line2D const line2D{Point2D{1, 2}, Point2D{3, 4}};
            CHECK_FALSE(line2D.isHorizontal());
            CHECK_FALSE(line2D.isVertical());
            CHECK(line2D.isDiagonal());
        }
        SECTION("Ascending")
        {
            Line2D const line2D{Point2D{1, 2}, Point2D{3, 0}};
            CHECK_FALSE(line2D.isHorizontal());
            CHECK_FALSE(line2D.isVertical());
            CHECK(line2D.isDiagonal());
        }
    }
}

TEST_CASE("[Line2D] Equality operator", "[utils][Line2D]")
{
    SECTION("Different")
    {
        Line2D const v1{Point2D{2, 3}, Point2D{1, 2}};
        Line2D const v2{Point2D{3, 1}, Point2D{-2, -2}};
        CHECK_FALSE(v1 == v2);
        CHECK(v1 != v2);
    }
    SECTION("Equal")
    {
        Line2D const v1{Point2D{2, 3}, Point2D{1, 2}};
        Line2D const v2{Point2D{2, 3}, Point2D{1, 2}};
        CHECK(v1 == v2);
        CHECK_FALSE(v1 != v2);
    }
}
