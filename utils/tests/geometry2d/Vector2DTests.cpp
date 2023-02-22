#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Vector2D.hpp>

using namespace utils::geometry2d;

TEST_CASE(
    "[Vector2D - factory] Factory returns a valid instance",
    "[Vector2D, Vector2D_factory]")
{
    auto vector2D{ Vector2D::create(2, 4) };
    CHECK(vector2D.getX() == 2);
    CHECK(vector2D.getY() == 4);
}

TEST_CASE(
    "[Vector2D - getters] Getters return correct values with default "
    "constructor",
    "[Vector2D, Vector2D_getters]")
{
    const Vector2D vector2D;
    CHECK(vector2D.getX() == 0);
    CHECK(vector2D.getY() == 0);
    const auto coords{ vector2D.get() };
    CHECK(coords.first == 0);
    CHECK(coords.second == 0);
}

TEST_CASE(
    "[Vector2D - getters] Getters return correct values with parametrized "
    "constructor",
    "[Vector2D, Vector2D_getters]")
{
    const Vector2D vector2D{ 2, 3 };
    CHECK(vector2D.getX() == 2);
    CHECK(vector2D.getY() == 3);
    const auto coords{ vector2D.get() };
    CHECK(coords.first == 2);
    CHECK(coords.second == 3);
}

TEST_CASE(
    "[Vector2D - getters] Getters return correct values with pair "
    "constructor",
    "[Vector2D, Vector2D_getters]")
{
    const Vector2D vector2D{ std::make_pair(2, 3) };
    CHECK(vector2D.getX() == 2);
    CHECK(vector2D.getY() == 3);
    const auto coords{ vector2D.get() };
    CHECK(coords.first == 2);
    CHECK(coords.second == 3);
}

TEST_CASE(
    "[Vector2D - distance] distance returns the correct values",
    "[Vector2D, Vector2D_distance]")
{
    const Vector2D v1;
    CHECK(v1.distance() == 0);
    const Vector2D v2{ 2, 3 };
    CHECK(v2.distance() == 3);
    const Vector2D v3{ -2, 1 };
    CHECK(v3.distance() == 2);
}

TEST_CASE(
    "[Vector2D - normalize] normalize returns the correct values",
    "[Vector2D, Vector2D_distance]")
{
    Vector2D v1;
    v1.normalize();
    CHECK(v1 == Vector2D{ 0, 0 });
    Vector2D v2{ 2, 3 };
    v2.normalize();
    CHECK(v2 == Vector2D{ 1, 1 });
    Vector2D v3{ -2, 1 };
    v3.normalize();
    CHECK(v3 == Vector2D{ -1, 1 });
    Vector2D v4{ -1, 0 };
    v4.normalize();
    CHECK(v4 == Vector2D{ -1, 0 });
}

TEST_CASE(
    "[Vector2D - getNormalized] getNormalized returns the correct values",
    "[Vector2D, Vector2D_getNormalized]")
{
    const Vector2D v1;
    CHECK(v1.getNormalized() == Vector2D{ 0, 0 });
    const Vector2D v2{ 2, 3 };
    CHECK(v2.getNormalized() == Vector2D{ 1, 1 });
    const Vector2D v3{ -2, 1 };
    CHECK(v3.getNormalized() == Vector2D{ -1, 1 });
    const Vector2D v4{ -1, 0 };
    CHECK(v4.getNormalized() == Vector2D{ -1, 0 });
}

TEST_CASE(
    "[Vector2D - isZero] isZero returns the correct values",
    "[Vector2D, Vector2D_isZero]")
{
    const Vector2D v1;
    CHECK(v1.isZero());
    const Vector2D v2{ 2, 3 };
    CHECK_FALSE(v2.isZero());
    const Vector2D v3{ -1, 2 };
    CHECK_FALSE(v3.isZero());
    const Vector2D v4{ 0, -1 };
    CHECK_FALSE(v4.isZero());
}

TEST_CASE(
    "[Vector2D - equality] Equality operator returns the correct values",
    "[Vector2D, Vector2D_equality]")
{
    const Vector2D v1{ 2, 3 };
    const Vector2D v2{ -4, 2 };
    CHECK_FALSE(v1 == v2);
    CHECK(v1 != v2);
    const Vector2D v3{ 2, 3 };
    CHECK(v1 == v3);
    CHECK_FALSE(v1 != v3);
}

TEST_CASE(
    "[Vector2D - addition] Addition operator returns the correct values",
    "[Vector2D, Vector2D_addition]")
{
    const Vector2D v1{ -2, 3 };
    const Vector2D v2{ 4, 2 };
    CHECK((v1 + v2) == Vector2D{ 2, 5 });
    CHECK((v2 + v1) == Vector2D{ 2, 5 });
}

TEST_CASE(
    "[Vector2D - negation] Negation operator returns the correct values",
    "[Vector2D, Vector2D_addition]")
{
    const Vector2D v1{ -2, 3 };
    const Vector2D v2{ 4, -2 };
    CHECK(-v1 == Vector2D{ 2, -3 });
    CHECK(-v2 == Vector2D{ -4, 2 });
}

TEST_CASE(
    "[Vector2D - subtraction] Subtraction operator returns the correct values",
    "[Vector2D, Vector2D_subtraction]")
{
    const Vector2D v1{ -2, 3 };
    const Vector2D v2{ 4, 2 };
    CHECK((v1 - v2) == Vector2D{ -6, 1 });
    CHECK((v2 - v1) == Vector2D{ 6, -1 });
}

TEST_CASE(
    "[Operations2D] Vector2D * scalar",
    "[Operations2D, Operations2D_vector2d]")
{
    const Vector2D vector2D{ 2, 3 };
    const auto newVector2D{ vector2D * 2 };
    CHECK(newVector2D.getX() == 4);
    CHECK(newVector2D.getY() == 6);
}

TEST_CASE(
    "[Operations2D] scalar * Vector2D",
    "[Operations2D, Operations2D_vector2d]")
{
    const Vector2D vector2D{ 2, 3 };
    const auto newVector2D{ 2 * vector2D };
    CHECK(newVector2D.getX() == 4);
    CHECK(newVector2D.getY() == 6);
}