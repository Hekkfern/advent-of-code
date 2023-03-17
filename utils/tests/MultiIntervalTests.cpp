#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/MultiInterval.hpp>

using namespace utils::interval;

TEST_CASE(
    "[MultiInterval - getters] Getters return correct values",
    "[MultiInterval, MultiInterval_getters]")
{
    const MultiInterval interval1{ { { 1, 3 }, { -1, 4 }, { 5, 7 } } };
    const auto result1{ interval1.get() };
    CHECK(result1.size() == 2U);
    CHECK(result1[0] == std::make_pair(-1, 4));
    CHECK(result1[1] == std::make_pair(5, 7));
}

TEST_CASE(
    "[MultiInterval - add] add() method does nothing when the interval is "
    "already contained",
    "[MultiInterval, MultiInterval_add]")
{
    MultiInterval interval1{ { { 1, 5 } } };
    interval1.add({ 1, 2 });
    const auto result1{ interval1.get() };
    CHECK(result1.size() == 1U);
    CHECK(result1[0] == std::make_pair(1, 5));
}

TEST_CASE(
    "[MultiInterval - add] add() method joins the interval if it is contiguous",
    "[MultiInterval, MultiInterval_add]")
{
    MultiInterval interval1{ { { 1, 5 } } };
    interval1.add({ 4, 6 });
    const auto result1{ interval1.get() };
    CHECK(result1.size() == 1U);
    CHECK(result1[0] == std::make_pair(1, 6));
}

TEST_CASE(
    "[MultiInterval - add] add() method appends the interval if it is not "
    "contained",
    "[MultiInterval, MultiInterval_add]")
{
    MultiInterval interval1{ { { 1, 5 } } };
    interval1.add({ 7, 9 });
    const auto result1{ interval1.get() };
    CHECK(result1.size() == 2U);
    CHECK(result1[0] == std::make_pair(1, 5));
    CHECK(result1[1] == std::make_pair(7, 9));
}

TEST_CASE(
    "[MultiInterval - add] add() method generates a larger interval if the "
    "added interval fills the gap",
    "[MultiInterval, MultiInterval_add]")
{
    MultiInterval interval1{ { { 1, 5 }, { 7, 9 } } };
    interval1.add({ 4, 8 });
    const auto result1{ interval1.get() };
    CHECK(result1.size() == 1U);
    CHECK(result1[0] == std::make_pair(1, 9));
}
