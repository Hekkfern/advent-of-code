#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Point2D.hpp>
#include <utils/geometry2d/Vector2D.hpp>

using namespace utils::geometry2d;

TEST_CASE(
    "[Point2D - getters] Getters return correct values with default "
    "constructor",
    "[Point2D, Point2D_getters]")
{
    const Point2D point2D;
    CHECK(point2D.getX() == 0);
    CHECK(point2D.getY() == 0);
    const auto coords{ point2D.get() };
    CHECK(coords.first == 0);
    CHECK(coords.second == 0);
}

TEST_CASE(
    "[Point2D - getters] Getters return correct values with parametrized "
    "constructor",
    "[Point2D, Point2D_getters]")
{
    const Point2D point2D{ 2, 3 };
    CHECK(point2D.getX() == 2);
    CHECK(point2D.getY() == 3);
    const auto coords{ point2D.get() };
    CHECK(coords.first == 2);
    CHECK(coords.second == 3);
}

TEST_CASE(
    "[Point2D - getters] Getters return correct values with pair "
    "constructor",
    "[Point2D, Point2D_getters]")
{
    const Point2D point2D{ std::make_pair(2, 3) };
    CHECK(point2D.getX() == 2);
    CHECK(point2D.getY() == 3);
    const auto coords{ point2D.get() };
    CHECK(coords.first == 2);
    CHECK(coords.second == 3);
}

TEST_CASE(
    "[Point2D - equality] Equality operator returns the correct values",
    "[Point2D, Point2D_equality]")
{
    const Point2D p1{ 2, 3 };
    const Point2D p2{ -4, 2 };
    CHECK_FALSE(p1 == p2);
    CHECK(p1 != p2);
    const Point2D p3{ 2, 3 };
    CHECK(p1 == p3);
    CHECK_FALSE(p1 != p3);
}

TEST_CASE(
    "[Point2D - addition] Addition operator returns the correct values",
    "[Point2D, Point2D_addition]")
{
    const Point2D p1{ -2, 3 };
    const Point2D p2{ 4, 2 };
    CHECK((p1 + p2) == Point2D{ 2, 5 });
    CHECK((p2 + p1) == Point2D{ 2, 5 });
}

TEST_CASE(
    "[Point2D - negation] Negation operator returns the correct values",
    "[Point2D, Point2D_addition]")
{
    const Point2D p1{ -2, 3 };
    const Point2D p2{ 4, -2 };
    CHECK(-p1 == Point2D{ 2, -3 });
    CHECK(-p2 == Point2D{ -4, 2 });
}

TEST_CASE(
    "[Point2D - subtraction] Subtraction operator returns the correct values",
    "[Point2D, Point2D_subtraction]")
{
    const Point2D p1{ -2, 3 };
    const Point2D p2{ 4, 2 };
    CHECK((p1 - p2) == Point2D{ -6, 1 });
    CHECK((p2 - p1) == Point2D{ 6, -1 });
}

TEST_CASE(
    "[Operations2D] Point2D + Vector2D",
    "[Operations2D, Operations2D_point2d]")
{
    const Point2D point2D{ 4, 1 };
    const Vector2D vector2D{ 2, 3 };
    const auto newPoint2D{ point2D + vector2D };
    CHECK(newPoint2D.getX() == 6);
    CHECK(newPoint2D.getY() == 4);
}

TEST_CASE(
    "[Operations2D] Vector2D + Point2D",
    "[Operations2D, Operations2D_point2d]")
{
    const Point2D point2D{ 4, 1 };
    const Vector2D vector2D{ 2, 3 };
    const auto newPoint2D{ vector2D + point2D };
    CHECK(newPoint2D.getX() == 6);
    CHECK(newPoint2D.getY() == 4);
}