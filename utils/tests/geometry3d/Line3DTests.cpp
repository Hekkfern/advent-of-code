#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry3d/Line3D.hpp>

using namespace utils::geometry3d;

TEST_CASE("[Line3D] Constructor", "[utils][Line3D]")
{
    SECTION("Default constructor")
    {
        Line3D const line3D;
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
        SECTION("Positive values")
        {
            Line3D const line3D{Point3D{1, 1}, Point3D{2, 3}};
            auto const thisSize{line3D.size()};
            CHECK(thisSize[0] == 1U);
            CHECK(thisSize[1] == 2U);
            CHECK(line3D.distance() == 3ULL);
            auto const vertexes{line3D.getVertexes()};
            CHECK(vertexes[0] == Point3D{1, 1});
            CHECK(vertexes[1] == Point3D{2, 3});
        }
        SECTION("Positive and negatives values")
        {
            Line3D const line3D{Point3D{-1, 1}, Point3D{2, -3}};
            auto const thisSize{line3D.size()};
            CHECK(thisSize[0] == 3U);
            CHECK(thisSize[1] == 4U);
            CHECK(line3D.distance() == 7ULL);
            auto const vertexes{line3D.getVertexes()};
            CHECK(vertexes[0] == Point3D{-1, 1});
            CHECK(vertexes[1] == Point3D{2, -3});
        }
    }
}

TEST_CASE("[Line3D] is() method", "[utils][Line3D]")
{
    SECTION("Zero")
    {
        Line3D const line3D{Point3D{1, 1}, Point3D{1, 1}};
        CHECK(line3D.is() == Line3DType::Zero);
    }
    SECTION("Horizontal")
    {
        SECTION("Right")
        {
            Line3D const line3D{Point3D{1, 1}, Point3D{6, 1}};
            CHECK(line3D.is() == Line3DType::Horizontal);
        }
        SECTION("Left")
        {
            Line3D const line3D{Point3D{1, 1}, Point3D{-6, 1}};
            CHECK(line3D.is() == Line3DType::Horizontal);
        }
    }
    SECTION("Vertical")
    {
        SECTION("Up")
        {
            Line3D const line3D{Point3D{1, 1}, Point3D{1, 6}};
            CHECK(line3D.is() == Line3DType::Vertical);
        }
        SECTION("Down")
        {
            Line3D const line3D{Point3D{1, 1}, Point3D{1, -6}};
            CHECK(line3D.is() == Line3DType::Vertical);
        }
    }
    SECTION("Diagonal")
    {
        SECTION("Up-Right")
        {
            Line3D const line3D{Point3D{1, 2}, Point3D{3, 4}};
            CHECK(line3D.is() == Line3DType::Diagonal);
        }
        SECTION("Down-Left")
        {
            Line3D const line3D{Point3D{1, 2}, Point3D{3, 0}};
            CHECK(line3D.is() == Line3DType::Diagonal);
        }
    }
    SECTION("Arbitrary")
    {
        Line3D const line3D{Point3D{1, 2}, Point3D{3, 5}};
        CHECK(line3D.is() == Line3DType::Arbitrary);
    }
}

TEST_CASE("[Line3D] Equality operator", "[utils][Line3D]")
{
    Line3D const obj1{Point3D{2, 3}, Point3D{1, 2}};

    SECTION("Different")
    {
        Line3D const obj2{Point3D{3, 1}, Point3D{-2, -2}};
        CHECK_FALSE(obj1 == obj2);
        CHECK(obj1 != obj2);
    }
    SECTION("Equal")
    {
        CHECK(obj1 == obj1);
        CHECK_FALSE(obj1 != obj1);
    }
}
