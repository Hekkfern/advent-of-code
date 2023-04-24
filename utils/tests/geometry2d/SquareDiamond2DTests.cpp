#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/SquareDiamond2D.hpp>

using namespace utils::geometry2d;

TEST_CASE(
    "[SquareDiamond2D - getter] Getters return correct values",
    "[SquareDiamond2D, SquareDiamond2D_getter]")
{
    const SquareDiamond2D shape{Point2D{10, 10}, 2};
    CHECK(shape.getCenter().getCoordinates() == Coord2D<>{10, 10});
    CHECK(shape.getDistance() == 2);
}

TEST_CASE(
    "[SquareDiamond2D - getVertexes] getVertexes() returns correct values",
    "[SquareDiamond2D, SquareDiamond2D_getVertexes]")
{
    const SquareDiamond2D shape{Point2D{10, 10}, 2};
    auto const vertexes{shape.getVertexes()};
    CHECK(vertexes[0] == (Point2D{10, 12}));
    CHECK(vertexes[1] == (Point2D{12, 10}));
    CHECK(vertexes[2] == (Point2D{10, 8}));
    CHECK(vertexes[3] == (Point2D{8, 10}));
}

TEST_CASE(
    "[SquareDiamond2D - isOutside] isOutside() returns true when the point is "
    "outside",
    "[SquareDiamond2D, SquareDiamond2D_isOutside]")
{
    const SquareDiamond2D shape{Point2D{10, 10}, 2};
    CHECK(shape.isOutside(Point2D{2, 2}));
}

TEST_CASE(
    "[SquareDiamond2D - isOutside] isOutside() returns false when the point is "
    "in the perimeter",
    "[SquareDiamond2D, SquareDiamond2D_isOutside]")
{
    const SquareDiamond2D shape{Point2D{10, 10}, 2};
    CHECK_FALSE(shape.isOutside(Point2D{8, 10}));
}

TEST_CASE(
    "[SquareDiamond2D - isOutside] isOutside() returns false when the point is "
    "in the inside",
    "[SquareDiamond2D, SquareDiamond2D_isOutside]")
{
    const SquareDiamond2D shape{Point2D{10, 10}, 2};
    CHECK_FALSE(shape.isOutside(Point2D{11, 10}));
}

TEST_CASE(
    "[SquareDiamond2D - isInside] isInside() returns false when the point is "
    "outside",
    "[SquareDiamond2D, SquareDiamond2D_isInside]")
{
    const SquareDiamond2D shape{Point2D{10, 10}, 2};
    CHECK_FALSE(shape.isInside(Point2D{2, 2}));
}

TEST_CASE(
    "[SquareDiamond2D - isInside] isInside() returns true when the point is "
    "in the perimeter",
    "[SquareDiamond2D, SquareDiamond2D_isInside]")
{
    const SquareDiamond2D shape{Point2D{10, 10}, 2};
    CHECK(shape.isInside(Point2D{8, 10}));
}

TEST_CASE(
    "[SquareDiamond2D - isInside] isInside() returns true when the point is "
    "in the inside",
    "[SquareDiamond2D, SquareDiamond2D_isInside]")
{
    const SquareDiamond2D shape{Point2D{10, 10}, 2};
    CHECK(shape.isInside(Point2D{11, 10}));
}

TEST_CASE(
    "[SquareDiamond2D - isInPerimeter] isInPerimeter() returns false when the "
    "point is outside",
    "[SquareDiamond2D, SquareDiamond2D_isInPerimeter]")
{
    const SquareDiamond2D shape{Point2D{10, 10}, 2};
    CHECK_FALSE(shape.isInPerimeter(Point2D{2, 2}));
}

TEST_CASE(
    "[SquareDiamond2D - isInPerimeter] isInPerimeter() returns true when the "
    "point is in the perimeter",
    "[SquareDiamond2D, SquareDiamond2D_isInPerimeter]")
{
    const SquareDiamond2D shape{Point2D{10, 10}, 2};
    CHECK(shape.isInPerimeter(Point2D{8, 10}));
}

TEST_CASE(
    "[SquareDiamond2D - isInPerimeter] isInPerimeter() returns true when the "
    "point is in the inside",
    "[SquareDiamond2D, SquareDiamond2D_isInPerimeter]")
{
    const SquareDiamond2D shape{Point2D{10, 10}, 2};
    CHECK_FALSE(shape.isInPerimeter(Point2D{11, 10}));
}

TEST_CASE(
    "[SquareDiamond2D - area] area() returns the correct value",
    "[SquareDiamond2D, SquareDiamond2D_area]")
{
    const SquareDiamond2D shape{Point2D{10, 10}, 2};
    CHECK(shape.area() == 13U);
}

TEST_CASE(
    "[SquareDiamond2D - stepAroundOutside] stepAroundOutside() returns the "
    "correct value",
    "[SquareDiamond2D, SquareDiamond2D_stepAroundOutside]")
{
    SquareDiamond2D shape{Point2D{10, 10}, 2};
    // start from top
    auto point{shape.stepAroundOutside()};
    REQUIRE(*point == Point2D{10, 13});
    // from top to right
    point = shape.stepAroundOutside();
    REQUIRE(*point == Point2D{11, 12});
    point = shape.stepAroundOutside();
    REQUIRE(*point == Point2D{12, 11});
    point = shape.stepAroundOutside();
    REQUIRE(*point == Point2D{13, 10});
    // from right to bottom
    point = shape.stepAroundOutside();
    REQUIRE(*point == Point2D{12, 9});
    point = shape.stepAroundOutside();
    REQUIRE(*point == Point2D{11, 8});
    point = shape.stepAroundOutside();
    REQUIRE(*point == Point2D{10, 7});
    // from bottom to left
    point = shape.stepAroundOutside();
    REQUIRE(*point == Point2D{9, 8});
    point = shape.stepAroundOutside();
    REQUIRE(*point == Point2D{8, 9});
    point = shape.stepAroundOutside();
    REQUIRE(*point == Point2D{7, 10});
    // from right to top
    point = shape.stepAroundOutside();
    REQUIRE(*point == Point2D{8, 11});
    point = shape.stepAroundOutside();
    REQUIRE(*point == Point2D{9, 12});
    point = shape.stepAroundOutside();
    REQUIRE_FALSE(point);
}
