#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/OrthogonalLine2D.h>

using namespace utils::geometry2d;

TEST_CASE("[OrthogonalLine2D] Constructor", "[utils][OrthogonalLine2D]")
{
    SECTION("Default constructor")
    {
        OrthogonalLine2D const line2D;
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
        SECTION("Horizontal")
        {
            OrthogonalLine2D const line2D{Point2D{1, 1}, Point2D{2, 1}};
            auto const thisSize{line2D.size()};
            CHECK(thisSize[0] == 1ULL);
            CHECK(thisSize[1] == 0ULL);
            CHECK(line2D.distance() == 1ULL);
            auto const vertexes{line2D.getVertexes()};
            CHECK(vertexes[0] == Point2D{1, 1});
            CHECK(vertexes[1] == Point2D{2, 1});
        }
        SECTION("Vertical")
        {
            OrthogonalLine2D const line2D{Point2D{-1, 1}, Point2D{-1, -3}};
            auto const thisSize{line2D.size()};
            CHECK(thisSize[0] == 0U);
            CHECK(thisSize[1] == 4U);
            CHECK(line2D.distance() == 4ULL);
            auto const vertexes{line2D.getVertexes()};
            CHECK(vertexes[0] == Point2D{-1, 1});
            CHECK(vertexes[1] == Point2D{-1, -3});
        }
    }
}

TEST_CASE("[OrthogonalLine2D] is() method", "[utils][OrthogonalLine2D]")
{
    SECTION("Zero")
    {
        OrthogonalLine2D const line2D{Point2D{1, 1}, Point2D{1, 1}};
        CHECK(line2D.is() == OrthogonalLine2DType::Zero);
    }
    SECTION("Horizontal")
    {
        SECTION("Right")
        {
            OrthogonalLine2D const line2D{Point2D{1, 1}, Point2D{6, 1}};
            CHECK(line2D.is() == OrthogonalLine2DType::Horizontal);
        }
        SECTION("Left")
        {
            OrthogonalLine2D const line2D{Point2D{1, 1}, Point2D{-6, 1}};
            CHECK(line2D.is() == OrthogonalLine2DType::Horizontal);
        }
    }
    SECTION("Vertical")
    {
        SECTION("Up")
        {
            OrthogonalLine2D const line2D{Point2D{1, 1}, Point2D{1, 6}};
            CHECK(line2D.is() == OrthogonalLine2DType::Vertical);
        }
        SECTION("Down")
        {
            OrthogonalLine2D const line2D{Point2D{1, 1}, Point2D{1, -6}};
            CHECK(line2D.is() == OrthogonalLine2DType::Vertical);
        }
    }
}

TEST_CASE("[OrthogonalLine2D] Equality operator", "[utils][OrthogonalLine2D]")
{
    OrthogonalLine2D const obj1{Point2D{2, 3}, Point2D{3, 3}};

    SECTION("Different")
    {
        OrthogonalLine2D const obj2{Point2D{3, 1}, Point2D{-2, 1}};
        CHECK_FALSE(obj1 == obj2);
        CHECK(obj1 != obj2);
    }
    SECTION("Equal")
    {
        CHECK(obj1 == obj1);
        CHECK_FALSE(obj1 != obj1);
    }
}

TEST_CASE("[OrthogonalLine2D] getPoints() method", "[utils][OrthogonalLine2D]")
{
    SECTION("Horizontal")
    {
        OrthogonalLine2D const line2D{Point2D{1, 1}, Point2D{6, 1}};
        auto const points{line2D.getPoints()};
        CHECK(points[0] == Point2D{1, 1});
        CHECK(points[1] == Point2D{2, 1});
        CHECK(points[2] == Point2D{3, 1});
        CHECK(points[3] == Point2D{4, 1});
        CHECK(points[4] == Point2D{5, 1});
        CHECK(points[5] == Point2D{6, 1});
    }
    SECTION("Vertical")
    {
        OrthogonalLine2D const line2D{Point2D{1, 1}, Point2D{1, 6}};
        auto const points{line2D.getPoints()};
        CHECK(points[0] == Point2D{1, 1});
        CHECK(points[1] == Point2D{1, 2});
        CHECK(points[2] == Point2D{1, 3});
        CHECK(points[3] == Point2D{1, 4});
        CHECK(points[4] == Point2D{1, 5});
        CHECK(points[5] == Point2D{1, 6});
    }
    SECTION("Zero")
    {
        OrthogonalLine2D const line2D{Point2D{1, 1}, Point2D{1, 1}};
        auto const points{line2D.getPoints()};
        CHECK(points[0] == Point2D{1, 1});
    }
}
