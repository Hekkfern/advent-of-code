#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry3d/OrthogonalLine3D.hpp>

using namespace utils::geometry3d;

TEST_CASE("[OrthogonalLine3D] Constructor", "[utils][OrthogonalLine3D]")
{
    SECTION("Default constructor")
    {
        OrthogonalLine3D const line3D;
        auto const thisSize{line3D.size()};
        CHECK(thisSize[0] == 0U);
        CHECK(thisSize[1] == 0U);
        CHECK(line3D.distance() == 0ULL);
        auto const vertexes{line3D.getVertexes()};
        CHECK(vertexes[0] == Point3D{});
        CHECK(vertexes[1] == Point3D{});
    }
    SECTION("Parametrized constructor")
    {
        SECTION("Horizontal")
        {
            OrthogonalLine3D const line3D{Point3D{1, 1}, Point3D{2, 1}};
            auto const thisSize{line3D.size()};
            CHECK(thisSize[0] == 1ULL);
            CHECK(thisSize[1] == 0ULL);
            CHECK(line3D.distance() == 1ULL);
            auto const vertexes{line3D.getVertexes()};
            CHECK(vertexes[0] == Point3D{1, 1});
            CHECK(vertexes[1] == Point3D{2, 1});
        }
        SECTION("Vertical")
        {
            OrthogonalLine3D const line3D{Point3D{-1, 1}, Point3D{-1, -3}};
            auto const thisSize{line3D.size()};
            CHECK(thisSize[0] == 0U);
            CHECK(thisSize[1] == 4U);
            CHECK(line3D.distance() == 4ULL);
            auto const vertexes{line3D.getVertexes()};
            CHECK(vertexes[0] == Point3D{-1, 1});
            CHECK(vertexes[1] == Point3D{-1, -3});
        }
    }
}

TEST_CASE("[OrthogonalLine3D] is() method", "[utils][OrthogonalLine3D]")
{
    SECTION("Zero")
    {
        OrthogonalLine3D const line3D{Point3D{1, 1}, Point3D{1, 1}};
        CHECK(line3D.is() == OrthogonalLine3DType::Zero);
    }
    SECTION("Horizontal")
    {
        SECTION("Right")
        {
            OrthogonalLine3D const line3D{Point3D{1, 1}, Point3D{6, 1}};
            CHECK(line3D.is() == OrthogonalLine3DType::Horizontal);
        }
        SECTION("Left")
        {
            OrthogonalLine3D const line3D{Point3D{1, 1}, Point3D{-6, 1}};
            CHECK(line3D.is() == OrthogonalLine3DType::Horizontal);
        }
    }
    SECTION("Vertical")
    {
        SECTION("Up")
        {
            OrthogonalLine3D const line3D{Point3D{1, 1}, Point3D{1, 6}};
            CHECK(line3D.is() == OrthogonalLine3DType::Vertical);
        }
        SECTION("Down")
        {
            OrthogonalLine3D const line3D{Point3D{1, 1}, Point3D{1, -6}};
            CHECK(line3D.is() == OrthogonalLine3DType::Vertical);
        }
    }
}

TEST_CASE("[OrthogonalLine3D] Equality operator", "[utils][OrthogonalLine3D]")
{
    OrthogonalLine3D const obj1{Point3D{2, 3}, Point3D{3, 3}};

    SECTION("Different")
    {
        OrthogonalLine3D const obj2{Point3D{3, 1}, Point3D{-2, 1}};
        CHECK_FALSE(obj1 == obj2);
        CHECK(obj1 != obj2);
    }
    SECTION("Equal")
    {
        CHECK(obj1 == obj1);
        CHECK_FALSE(obj1 != obj1);
    }
}

TEST_CASE("[OrthogonalLine3D] getPoints() method", "[utils][OrthogonalLine3D]")
{
    SECTION("Horizontal")
    {
        OrthogonalLine3D const line3D{Point3D{1, 1}, Point3D{6, 1}};
        auto const points{line3D.getPoints()};
        CHECK(points[0] == Point3D{1, 1});
        CHECK(points[1] == Point3D{2, 1});
        CHECK(points[2] == Point3D{3, 1});
        CHECK(points[3] == Point3D{4, 1});
        CHECK(points[4] == Point3D{5, 1});
        CHECK(points[5] == Point3D{6, 1});
    }
    SECTION("Vertical")
    {
        OrthogonalLine3D const line3D{Point3D{1, 1}, Point3D{1, 6}};
        auto const points{line3D.getPoints()};
        CHECK(points[0] == Point3D{1, 1});
        CHECK(points[1] == Point3D{1, 2});
        CHECK(points[2] == Point3D{1, 3});
        CHECK(points[3] == Point3D{1, 4});
        CHECK(points[4] == Point3D{1, 5});
        CHECK(points[5] == Point3D{1, 6});
    }
    SECTION("Zero")
    {
        OrthogonalLine3D const line3D{Point3D{1, 1}, Point3D{1, 1}};
        auto const points{line3D.getPoints()};
        CHECK(points[0] == Point3D{1, 1});
    }
}
