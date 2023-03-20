#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/MultiInterval.hpp>

using namespace utils::interval;

TEST_CASE(
    "[MultiInterval - constructor] Constructor reduces contiguous intervals",
    "[MultiInterval, MultiInterval_getters]")
{
    const MultiInterval interval1{ { { 1, 3 }, { -1, 4 }, { 5, 7 } } };
    const auto& result1{ interval1.get() };
    REQUIRE(result1.size() == 1U);
    CHECK(result1[0] == Interval{ -1, 7 });
}

TEST_CASE(
    "[MultiInterval - add] add() method doesn't add any interval when it is "
    "already contained",
    "[MultiInterval, MultiInterval_add]")
{
    MultiInterval interval1{ { { 1, 5 } } };
    interval1.add({ 1, 2 });
    const auto result1{ interval1.get() };
    REQUIRE(result1.size() == 1U);
    CHECK(result1[0] == Interval{ 1, 5 });
}

TEST_CASE(
    "[MultiInterval - add] add() method joins the interval if it is contiguous",
    "[MultiInterval, MultiInterval_add]")
{
    MultiInterval interval1{ { { 1, 5 } } };
    interval1.add({ 4, 6 });
    const auto result1{ interval1.get() };
    REQUIRE(result1.size() == 1U);
    CHECK(result1[0] == Interval{ 1, 6 });
}

TEST_CASE(
    "[MultiInterval - add] add() method appends the interval if it is not "
    "contained",
    "[MultiInterval, MultiInterval_add]")
{
    MultiInterval interval1{ { { 1, 5 } } };
    interval1.add({ 7, 9 });
    const auto result1{ interval1.get() };
    REQUIRE(result1.size() == 2U);
    CHECK(result1[0] == Interval{ 1, 5 });
    CHECK(result1[1] == Interval{ 7, 9 });
}

TEST_CASE(
    "[MultiInterval - add] add() method generates a larger interval if the "
    "added interval fills the gap",
    "[MultiInterval, MultiInterval_add]")
{
    MultiInterval interval1{ { { 1, 5 }, { 7, 9 } } };
    interval1.add({ 4, 8 });
    const auto result1{ interval1.get() };
    REQUIRE(result1.size() == 1U);
    CHECK(result1[0] == Interval{ 1, 9 });
}

TEST_CASE(
    "[MultiInterval - add] add() method does nothing when adds an "
    "already-contained single value",
    "[MultiInterval, MultiInterval_add]")
{
    MultiInterval interval1{ { { 1, 5 }, { 7, 9 } } };
    interval1.add(4);
    const auto result1{ interval1.get() };
    REQUIRE(result1.size() == 2U);
    CHECK(result1[0] == Interval{ 1, 5 });
    CHECK(result1[1] == Interval{ 7, 9 });
}

TEST_CASE(
    "[MultiInterval - add] add() method adds a single value",
    "[MultiInterval, MultiInterval_add]")
{
    MultiInterval interval2{ { { 1, 5 }, { 7, 9 } } };
    interval2.add(6);
    const auto result2{ interval2.get() };
    REQUIRE(result2.size() == 1U);
    CHECK(result2[0] == Interval{ 1, 9 });
}

TEST_CASE(
    "[MultiInterval - remove] remove() splits an interval in half",
    "[MultiInterval, MultiInterval_remove]")
{
    MultiInterval interval1{ { { 1, 5 } } };
    interval1.remove(3);
    const auto result1{ interval1.get() };
    REQUIRE(result1.size() == 2U);
    CHECK(result1[0] == Interval{ 1, 2 });
    CHECK(result1[1] == Interval{ 4, 5 });
}

TEST_CASE(
    "[MultiInterval - remove] remove() does nothing if the value is not "
    "contained in the interval",
    "[MultiInterval, MultiInterval_remove]")
{
    MultiInterval interval1{ { { 1, 5 } } };
    interval1.remove(7);
    const auto result1{ interval1.get() };
    REQUIRE(result1.size() == 1U);
    CHECK(result1[0] == Interval{ 1, 5 });
}

TEST_CASE(
    "[MultiInterval - remove] remove() works correctly with a value in a "
    "border of a interval",
    "[MultiInterval, MultiInterval_remove]")
{
    MultiInterval interval1{ { { 1, 5 }, { 7, 9 } } };
    interval1.remove(5);
    const auto result1{ interval1.get() };
    REQUIRE(result1.size() == 2U);
    CHECK(result1[0] == Interval{ 1, 4 });
    CHECK(result1[1] == Interval{ 7, 9 });
}

TEST_CASE(
    "[MultiInterval - remove] remove() deletes a completely-contained interval",
    "[MultiInterval, MultiInterval_remove]")
{
    MultiInterval interval1{ { { 1, 5 } } };
    interval1.remove({ 3, 4 });
    const auto result1{ interval1.get() };
    REQUIRE(result1.size() == 2U);
    CHECK(result1[0] == Interval{ 1, 2 });
    CHECK(result1[1] == Interval{ 5, 5 });
}

TEST_CASE(
    "[MultiInterval - remove] remove() does nothing if the values of the "
    "selected interval are not contained",
    "[MultiInterval, MultiInterval_remove]")
{
    MultiInterval interval1{ { { 1, 5 } } };
    interval1.remove({ 7, 8 });
    const auto result1{ interval1.get() };
    REQUIRE(result1.size() == 1U);
    CHECK(result1[0] == Interval{ 1, 5 });
}

TEST_CASE(
    "[MultiInterval - remove] remove() only removes the contained values of "
    "the selected interval",
    "[MultiInterval, MultiInterval_remove]")
{
    MultiInterval interval1{ { { 1, 5 }, { 7, 10 } } };
    interval1.remove({ 4, 8 });
    const auto result1{ interval1.get() };
    REQUIRE(result1.size() == 2U);
    CHECK(result1[0] == Interval{ 1, 3 });
    CHECK(result1[1] == Interval{ 9, 10 });
}

TEST_CASE(
    "[MultiInterval - remove] remove() works with single-value intervals",
    "[MultiInterval, MultiInterval_remove]")
{
    MultiInterval interval1{ { { 1, 5 } } };
    interval1.remove({ 4, 4 });
    const auto result1{ interval1.get() };
    REQUIRE(result1.size() == 2U);
    CHECK(result1[0] == Interval{ 1, 3 });
    CHECK(result1[1] == Interval{ 5, 5 });
}
