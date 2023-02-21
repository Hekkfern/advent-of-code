#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Vector2D.hpp>

using namespace utils::geometry2d;



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