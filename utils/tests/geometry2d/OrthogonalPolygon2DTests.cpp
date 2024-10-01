#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/OrthogonalPolygon2D.h>

using namespace utils::geometry2d;

TEST_CASE(
    "[OrthogonalPolygon2D] calculateNumberOfIntrinsicPoints() method",
    "[utils][OrthogonalPolygon2D]")
{
    std::vector<Point2D<>> const vertexes{
        Point2D{0, 0},
        Point2D{6, 0},
        Point2D{6, -5},
        Point2D{4, -5},
        Point2D{4, -7},
        Point2D{6, -7},
        Point2D{6, -9},
        Point2D{1, -9},
        Point2D{1, -7},
        Point2D{0, -7},
        Point2D{0, -5},
        Point2D{2, -5},
        Point2D{2, -2},
        Point2D{0, -2}};
    REQUIRE(vertexes.size() == 14ULL);
    OrthogonalPolygon2D const polygon{vertexes};
    CHECK(polygon.calculateNumberOfIntrinsicPoints() == 24ULL);
}

TEST_CASE(
    "[OrthogonalPolygon2D] perimeter() and calculateBoundaryPoints() methods",
    "[utils][OrthogonalPolygon2D]")
{
    std::vector<Point2D<>> const vertexes{
        Point2D{0, 0},
        Point2D{6, 0},
        Point2D{6, -5},
        Point2D{4, -5},
        Point2D{4, -7},
        Point2D{6, -7},
        Point2D{6, -9},
        Point2D{1, -9},
        Point2D{1, -7},
        Point2D{0, -7},
        Point2D{0, -5},
        Point2D{2, -5},
        Point2D{2, -2},
        Point2D{0, -2}};
    REQUIRE(vertexes.size() == 14ULL);
    OrthogonalPolygon2D const polygon{vertexes};
    CHECK(polygon.perimeter() == 38ULL);
    auto const boundaryPoints{polygon.calculateBoundaryPoints()};
    CHECK(boundaryPoints.size() == 38ULL);
}
