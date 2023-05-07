#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/CircularList.hpp>

using namespace utils::containers;

TEST_CASE("[CircularList] size() method", "[utils][CircularList]")
{
    SECTION("Empty list")
    {
        const CircularList circularList;
        REQUIRE(circularList.size() == 0U);
        REQUIRE(circularList.empty());
    }
}