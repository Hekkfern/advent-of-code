#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/CircularList.hpp>

using namespace utils::containers;

TEST_CASE("[CircularList] size() method", "[utils][CircularList]")
{
    SECTION("Empty list")
    {
        CircularList const circularList;
        REQUIRE(circularList.size() == 0U);
        REQUIRE(circularList.empty());
    }
    SECTION("Non empty list")
    {
        SECTION("Copying a list")
        {
            std::list<int32_t> list{123};
            CircularList<int32_t> const circularList{list};
            REQUIRE(circularList.size() == 1U);
            REQUIRE(!circularList.empty());
        }
        SECTION("Moving a list")
        {
            CircularList<int32_t> const circularList{std::list<int32_t>{123}};
            REQUIRE(circularList.size() == 1U);
            REQUIRE(!circularList.empty());
        }
    }
}