#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/Position2D.hpp>

TEST_CASE("[Position2D - getters] Works OK", "[Position2D, Position2D_getters]")
{
    utils::geometry2d::Position2D position2D{ 2, 3 };
    CHECK(position2D.getX() == 2);
    CHECK(position2D.getY() == 3);
    const auto coords{ position2D.get() };
    CHECK(coords.first == 2);
    CHECK(coords.second == 3);
}
