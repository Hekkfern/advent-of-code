#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/SquareDiamond2D.hpp>

using namespace utils::geometry2d;

TEST_CASE(
    "[SquareDiamond2D - getter] Getters return correct values",
    "[SquareDiamond2D, SquareDiamond2D_getter]")
{
    SquareDiamond2D shape{ { 10, 10 }, 2 };
    CHECK(shape.getCenter().getCoordinates() == std::make_pair(10, 10));
    CHECK(shape.getDistance() == 2);
}