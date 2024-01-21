#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Line2D.hpp>

using namespace utils::geometry2d;

TEST_CASE("[Line2D] Constructor", "[utils][Line2D]")
{
    SECTION("Default constructor")
    {
        Line2D<> const line2D;
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
            Line2D<> const line2D{Point2D<>{1, 1}, Point2D<>{2, 3}};
            auto const thisSize{line2D.size()};
            CHECK(thisSize[0] == 0U);
            CHECK(thisSize[1] == 0U);
            CHECK(line2D.distance() == 0ULL);
            auto const vertexes{line2D.getVertexes()};
            CHECK(vertexes[0] == Point2D{});
            CHECK(vertexes[1] == Point2D{});
        }
        SECTION("Positive and negatives values")
        {
            Line2D<> const line2D;
            auto const thisSize{line2D.size()};
            CHECK(thisSize[0] == 0U);
            CHECK(thisSize[1] == 0U);
            CHECK(line2D.distance() == 0ULL);
            auto const vertexes{line2D.getVertexes()};
            CHECK(vertexes[0] == Point2D{});
            CHECK(vertexes[1] == Point2D{});
        }
    }
}
