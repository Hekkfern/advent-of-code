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
        REQUIRE(thisSize.size() == 3ULL);
        CHECK(thisSize[0] == 0ULL);
        CHECK(thisSize[1] == 0ULL);
        CHECK(thisSize[2] == 0ULL);
        CHECK(line3D.distance() == 0ULL);
        auto const vertexes{line3D.getVertexes()};
        REQUIRE(vertexes.size() == 2ULL);
        CHECK(vertexes[0] == Point3D<>{});
        CHECK(vertexes[1] == Point3D<>{});
    }
    SECTION("Parametrized constructor")
    {
        SECTION("Positive values")
        {
            Line3D const line3D{Point3D<>{1, 1, 1}, Point3D<>{2, 3, 4}};
            auto const thisSize{line3D.size()};
            REQUIRE(thisSize.size() == 3ULL);
            CHECK(thisSize[0] == 1U);
            CHECK(thisSize[1] == 2U);
            CHECK(thisSize[2] == 3U);
            CHECK(line3D.distance() == 6ULL);
            auto const vertexes{line3D.getVertexes()};
            REQUIRE(vertexes.size() == 2ULL);
            CHECK(vertexes[0] == Point3D<>{1, 1, 1});
            CHECK(vertexes[1] == Point3D<>{2, 3, 4});
        }
        SECTION("Positive and negatives values")
        {
            Line3D const line3D{Point3D<>{-1, 1, 1}, Point3D<>{2, -3, 4}};
            auto const thisSize{line3D.size()};
            REQUIRE(thisSize.size() == 3ULL);
            CHECK(thisSize[0] == 3U);
            CHECK(thisSize[1] == 4U);
            CHECK(thisSize[2] == 3U);
            CHECK(line3D.distance() == 10ULL);
            auto const vertexes{line3D.getVertexes()};
            REQUIRE(vertexes.size() == 2ULL);
            CHECK(vertexes[0] == Point3D<>{-1, 1, 1});
            CHECK(vertexes[1] == Point3D<>{2, -3, 4});
        }
    }
}

TEST_CASE("[Line3D] is() method", "[utils][Line3D]")
{
    SECTION("Zero")
    {
        Line3D const line3D{Point3D<>{1, 1, 1}, Point3D<>{1, 1, 1}};
        CHECK(line3D.is() == Line3DType::Zero);
    }
    SECTION("AcrossXAxis")
    {
        SECTION("Right")
        {
            Line3D const line3D{Point3D<>{1, 1, 1}, Point3D<>{6, 1, 1}};
            CHECK(line3D.is() == Line3DType::AcrossXAxis);
        }
        SECTION("Left")
        {
            Line3D const line3D{Point3D<>{1, 1, 1}, Point3D<>{-6, 1, 1}};
            CHECK(line3D.is() == Line3DType::AcrossXAxis);
        }
    }
    SECTION("AcrossYAxis")
    {
        SECTION("Right")
        {
            Line3D const line3D{Point3D<>{1, 1, 1}, Point3D<>{1, 6, 1}};
            CHECK(line3D.is() == Line3DType::AcrossYAxis);
        }
        SECTION("Left")
        {
            Line3D const line3D{Point3D<>{1, 1, 1}, Point3D<>{1, -6, 1}};
            CHECK(line3D.is() == Line3DType::AcrossYAxis);
        }
    }
    SECTION("AcrossZAxis")
    {
        SECTION("Right")
        {
            Line3D const line3D{Point3D<>{1, 1, 1}, Point3D<>{1, 1, 6}};
            CHECK(line3D.is() == Line3DType::AcrossZAxis);
        }
        SECTION("Left")
        {
            Line3D const line3D{Point3D<>{1, 1, 1}, Point3D<>{1, 1, -6}};
            CHECK(line3D.is() == Line3DType::AcrossZAxis);
        }
    }
    SECTION("Arbitrary")
    {
        Line3D const line3D{Point3D<>{1, 2, 1}, Point3D<>{3, 5, 2}};
        CHECK(line3D.is() == Line3DType::Arbitrary);
    }
}

TEST_CASE("[Line3D] Equality operator", "[utils][Line3D]")
{
    Line3D const obj1{Point3D<>{2, 3, 1}, Point3D<>{1, 2, 3}};

    SECTION("Different")
    {
        Line3D const obj2{Point3D<>{3, 1, 1}, Point3D<>{-2, -2, 2}};
        CHECK_FALSE(obj1 == obj2);
        CHECK(obj1 != obj2);
    }
    SECTION("Equal")
    {
        CHECK(obj1 == obj1);
        CHECK_FALSE(obj1 != obj1);
    }
}
