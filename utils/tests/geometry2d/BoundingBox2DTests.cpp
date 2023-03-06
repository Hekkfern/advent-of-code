#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/geometry2d/BoundingBox2D.hpp>

using namespace utils::geometry2d;

TEST_CASE(
    "[BoundingBox2D - constructor] Constructor initializes the values correctly",
    "[BoundingBox2D, BoundingBox2D_constructor]")
{
    const BoundingBox2D boundingBox2D{  };
    CHECK(boundingBox2D.getMaxX() == std::numeric_limits<int32_t>::min());
    CHECK(boundingBox2D.getMinX() == std::numeric_limits<int32_t>::max());
    CHECK(boundingBox2D.getMaxY() == std::numeric_limits<int32_t>::min());
    CHECK(boundingBox2D.getMinY() == std::numeric_limits<int32_t>::max());
}
