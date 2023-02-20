#define CATCH_CONFIG_MAIN
#include "utils/geometry2d/Direction2D.hpp"
#include <catch.hpp>

using namespace utils::geometry2d;

TEST_CASE(
    "[Direction2D - constructor] Constructor initializes the value correctly",
    "[Direction2D, Direction2D_constructor]")
{
    Direction2D direction2D{ Direction2D::DownRight };
    REQUIRE(direction2D == Direction2D::DownRight);
}