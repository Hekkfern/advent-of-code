#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Calculations2D.hpp>

using namespace utils::geometry2d;

TEST_CASE(
    "[Operations2D] calculateArbitraryPolygonArea() method",
    "[utils][Operations2D]")
{
    std::vector<Point2D<>> const points{
        Point2D{1, 6},
        Point2D{3, 1},
        Point2D{7, 2},
        Point2D{4, 4},
        Point2D{8, 5}};
    CHECK_THAT(
        calculateArbitraryPolygonArea(points),
        Catch::Matchers::WithinRel(16.5, 0.001));
}

TEST_CASE(
    "[Operations2D] calculateNumberOfIntrinsicPointsInsidePolygon() method",
    "[utils][Operations2D]")
{
    std::vector<Point2D<>> const points{
        Point2D{1, 0},
        Point2D{2, 1},
        Point2D{3, 2},
        Point2D{4, 3},
        Point2D{4, 4},
        Point2D{4, 5},
        Point2D{2, 4},
        Point2D{0, 3}};
    CHECK(calculateNumberOfIntrinsicPointsInsidePolygon(points) == 7ULL);
}

TEST_CASE(
    "[Operations2D] calculateAngleBetweenTwoVectors() method",
    "[utils][Operations2D]")
{
    SECTION("Same vector")
    {
        Vector2D<> const v1{1, 1};
        CHECK_THAT(
            calculateAngleBetweenTwoVectors(v1, v1),
            Catch::Matchers::WithinRel(0.0, 0.001));
    }
    SECTION("Both up")
    {
        Vector2D<> const v1{1, 1};
        Vector2D<> const v2{-1, 1};
        SECTION("From v1 to v2")
        {
            CHECK_THAT(
                calculateAngleBetweenTwoVectors(v1, v2),
                Catch::Matchers::WithinRel(std::numbers::pi / 2.0, 0.001));
        }
        SECTION("From v2 to v1")
        {
            CHECK_THAT(
                calculateAngleBetweenTwoVectors(v2, v1),
                Catch::Matchers::WithinRel(-std::numbers::pi / 2.0, 0.001));
        }
    }
    SECTION("Opposite directions")
    {
        Vector2D<> const v1{1, 1};
        Vector2D<> const v2{-1, -1};
        CHECK_THAT(
            calculateAngleBetweenTwoVectors(v1, v2),
            Catch::Matchers::WithinRel(std::numbers::pi, 0.001)
                || Catch::Matchers::WithinRel(-std::numbers::pi, 0.001));
    }
}
