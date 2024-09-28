#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Rectangle2D.hpp>

using namespace utils::geometry2d;

TEST_CASE(
    "[Rectangle2D - getter] Getters return correct values",
    "[Rectangle2D, Rectangle2D_getter]")
{
    Rectangle2D<> const shape{Point2D<>{0, 0}, Point2D<>{10, 5}};
    CHECK(shape.getHeight() == 5U);
    CHECK(shape.getWidth() == 10U);
}

TEST_CASE(
    "[Rectangle2D - getVertexes] getVertexes() returns correct values",
    "[Rectangle2D, Rectangle2D_getVertexes]")
{
    Rectangle2D<> const shape{Point2D<>{0, 0}, Point2D<>{10, 5}};
    auto const vertexes{shape.getVertexes()};
    CHECK(vertexes[0] == (Point2D<>{0, 0}));
    CHECK(vertexes[1] == (Point2D<>{10, 0}));
    CHECK(vertexes[2] == (Point2D<>{10, 5}));
    CHECK(vertexes[3] == (Point2D<>{0, 5}));
}

TEST_CASE(
    "[Rectangle2D - isOutside] isOutside() returns true when the point is "
    "outside",
    "[Rectangle2D, Rectangle2D_isOutside]")
{
    Rectangle2D<> const shape{Point2D<>{0, 0}, Point2D<>{10, 5}};
    CHECK(shape.isOutside(Point2D<>{12, 12}));
}

TEST_CASE(
    "[Rectangle2D - isOutside] isOutside() returns false when the point is "
    "in the perimeter",
    "[Rectangle2D, Rectangle2D_isOutside]")
{
    Rectangle2D<> const shape{Point2D<>{0, 0}, Point2D<>{10, 5}};
    CHECK_FALSE(shape.isOutside(Point2D<>{0, 5}));
}

TEST_CASE(
    "[Rectangle2D - isOutside] isOutside() returns false when the point is "
    "in the inside",
    "[Rectangle2D, Rectangle2D_isOutside]")
{
    Rectangle2D<> const shape{Point2D<>{0, 0}, Point2D<>{10, 5}};
    CHECK_FALSE(shape.isOutside(Point2D<>{2, 2}));
}

TEST_CASE(
    "[Rectangle2D - isInside] isInside() returns false when the point is "
    "outside",
    "[Rectangle2D, Rectangle2D_isInside]")
{
    Rectangle2D<> const shape{Point2D<>{0, 0}, Point2D<>{10, 5}};
    CHECK_FALSE(shape.isInside(Point2D<>{12, 12}));
}

TEST_CASE(
    "[Rectangle2D - isInside] isInside() returns true when the point is "
    "in the perimeter",
    "[Rectangle2D, Rectangle2D_isInside]")
{
    Rectangle2D<> const shape{Point2D<>{0, 0}, Point2D<>{10, 5}};
    CHECK(shape.isInside(Point2D<>{0, 5}));
}

TEST_CASE(
    "[Rectangle2D - isInside] isInside() returns true when the point is "
    "in the inside",
    "[Rectangle2D, Rectangle2D_isInside]")
{
    Rectangle2D<> const shape{Point2D<>{0, 0}, Point2D<>{10, 5}};
    CHECK(shape.isInside(Point2D<>{2, 2}));
}

TEST_CASE(
    "[Rectangle2D - isInPerimeter] isInPerimeter() returns false when the "
    "point is outside",
    "[Rectangle2D, Rectangle2D_isInPerimeter]")
{
    Rectangle2D<> const shape{Point2D<>{0, 0}, Point2D<>{10, 5}};
    CHECK_FALSE(shape.isInPerimeter(Point2D<>{12, 12}));
}

TEST_CASE(
    "[Rectangle2D - isInPerimeter] isInPerimeter() returns true when the "
    "point is in the perimeter",
    "[Rectangle2D, Rectangle2D_isInPerimeter]")
{
    Rectangle2D<> const shape{Point2D<>{0, 0}, Point2D<>{10, 5}};
    CHECK(shape.isInPerimeter(Point2D<>{0, 5}));
}

TEST_CASE(
    "[Rectangle2D - isInPerimeter] isInPerimeter() returns true when the "
    "point is in the inside",
    "[Rectangle2D, Rectangle2D_isInPerimeter]")
{
    Rectangle2D<> const shape{Point2D<>{0, 0}, Point2D<>{10, 5}};
    CHECK_FALSE(shape.isInPerimeter(Point2D<>{2, 2}));
}

TEST_CASE(
    "[Rectangle2D - area] area() returns the correct value",
    "[Rectangle2D, Rectangle2D_area]")
{
    Rectangle2D<> const shape{Point2D<>{0, 0}, Point2D<>{10, 5}};
    CHECK(shape.area() == 50U);
}
