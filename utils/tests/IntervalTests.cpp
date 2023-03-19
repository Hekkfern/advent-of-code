#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/Interval.hpp>

using namespace utils::interval;

TEST_CASE(
    "[Interval - getters] Getters return correct values",
    "[Interval, Interval_getters]")
{
    const Interval interval1{ 2, 3 };
    CHECK(interval1.getMin() == 2);
    CHECK(interval1.getMax() == 3);
    CHECK(interval1.get() == std::make_pair(2, 3));
    const Interval interval2{ -3, 1 };
    CHECK(interval2.getMin() == -3);
    CHECK(interval2.getMax() == 1);
    CHECK(interval2.get() == std::make_pair(-3, 1));
}

TEST_CASE(
    "[Interval - constructor] Construct fails when the min and max values are "
    "wrong",
    "[Interval, Interval_constructor]")
{
    CHECK_THROWS(Interval{ 2, -3 });
}

TEST_CASE(
    "[Interval - length] length() method returns correct values",
    "[Interval, Interval_length]")
{
    const Interval interval1{ 2, 3 };
    CHECK(interval1.length() == 1U);
    const Interval interval2{ -3, 1 };
    CHECK(interval2.length() == 4U);
}

TEST_CASE(
    "[Interval - join] join() method returns a valid interval when they "
    "overlap",
    "[Interval, Interval_join]")
{
    const Interval interval1{ 2, 4 };
    const Interval interval2{ -3, 1 };
    const std::optional<Interval> result1{ interval1.join(interval2) };
    CHECK_FALSE(result1);
}

TEST_CASE(
    "[Interval - join] join() method returns nothing when they don't overlap",
    "[Interval, Interval_join]")
{
    const Interval interval1{ 2, 4 };
    const Interval interval2{ -3, 3 };
    const std::optional<Interval> result1{ interval1.join(interval2) };
    CHECK(result1);
    CHECK(result1->get() == std::make_pair(-3, 4));
}

TEST_CASE(
    "[Interval - join] join() method works with single-value intervals",
    "[Interval, Interval_join]")
{
    const Interval interval1{ 2, 4 };
    const Interval interval2{ 2, 2 };
    const std::optional<Interval> result1{ interval1.join(interval2) };
    CHECK(result1);
    CHECK(result1->get() == std::make_pair(2, 4));
    const Interval interval3{ 1, 1 };
    const std::optional<Interval> result2{ interval1.join(interval3) };
    CHECK(result2);
    CHECK(result2->get() == std::make_pair(1, 4));
    const Interval interval4{ 5, 5 };
    const std::optional<Interval> result3{ interval1.join(interval4) };
    CHECK(result3);
    CHECK(result3->get() == std::make_pair(2, 5));
    const Interval interval5{ 7, 7 };
    const std::optional<Interval> result4{ interval1.join(interval5) };
    CHECK_FALSE(result4);
}

TEST_CASE(
    "[Interval - intersect] intersect() method returns correct values",
    "[Interval, Interval_intersect]")
{
    const Interval interval1{ 2, 3 };
    const Interval interval2{ -3, 1 };
    const Interval interval3{ -3, 4 };
    const Interval interval4{ -5, -1 };
    const auto result1{ interval1.intersect(interval2) };
    CHECK(!result1);
    const auto result2{ interval1.intersect(interval3) };
    CHECK(result2);
    CHECK(result2->get() == std::make_pair(2, 3));
    const auto result3{ interval3.intersect(interval4) };
    CHECK(result3);
    CHECK(result3->get() == std::make_pair(-3, -1));
    const auto result4{ interval2.intersect(interval3) };
    CHECK(result4);
    CHECK(result4->get() == std::make_pair(-3, 1));
    const auto result5{ interval3.intersect(interval1) };
    CHECK(result5);
    CHECK(result5->get() == std::make_pair(2, 3));
}

TEST_CASE(
    "[Interval - subsumes] subsumes() method returns correct values",
    "[Interval, Interval_subsumes]")
{
    const Interval interval1{ 2, 3 };
    const Interval interval2{ -3, 1 };
    const Interval interval3{ -3, 3 };
    CHECK_FALSE(interval1.subsumes(interval2));
    CHECK(interval3.subsumes(interval1));
    CHECK_FALSE(interval1.subsumes(interval3));
}

TEST_CASE(
    "[Interval - overlaps] overlaps() method returns correct values",
    "[Interval, Interval_overlaps]")
{
    const Interval interval1{ 2, 6 };
    const Interval interval2{ 1, 3 };
    CHECK(interval1.overlaps(interval2));
    CHECK(interval2.overlaps(interval1));
    const Interval interval3{ 5, 7 };
    CHECK(interval1.overlaps(interval3));
    CHECK(interval3.overlaps(interval1));
    const Interval interval4{ 4, 5 };
    CHECK(interval4.overlaps(interval1));
    CHECK(interval1.overlaps(interval4));
    const Interval interval5{ 1, 2 };
    CHECK(interval1.overlaps(interval5));
    CHECK(interval5.overlaps(interval1));
    const Interval interval6{ 6, 7 };
    CHECK(interval1.overlaps(interval6));
    CHECK(interval6.overlaps(interval1));
}

TEST_CASE(
    "[Interval - contains] contains() method returns correct values",
    "[Interval, Interval_contains]")
{
    const Interval interval1{ 2, 7 };
    CHECK(interval1.contains(2));
    CHECK(interval1.contains(5));
    CHECK(interval1.contains(7));
    CHECK_FALSE(interval1.contains(21));
    CHECK_FALSE(interval1.contains(-2));
}

TEST_CASE(
    "[Interval - hasOneValue] hasOneValue() method returns correct values",
    "[Interval, Interval_hasOneValue]")
{
    const Interval interval1{ 2, 7 };
    CHECK_FALSE(interval1.hasOneValue());
    const Interval interval2{ 3, 3 };
    CHECK(interval2.hasOneValue());
}

TEST_CASE(
    "[Interval - areContiguous] areContiguous() method returns correct values",
    "[Interval, Interval_areContiguous]")
{
    const Interval interval1{ 2, 7 };
    const Interval interval2{ -1, 1 };
    CHECK(interval1.areContiguous(interval2));
    CHECK(interval2.areContiguous(interval1));
    const Interval interval3{ 3, 3 };
    CHECK_FALSE(interval1.areContiguous(interval3));
    CHECK_FALSE(interval3.areContiguous(interval1));
    const Interval interval4{ 8, 9 };
    CHECK(interval1.areContiguous(interval4));
    CHECK(interval4.areContiguous(interval1));
}
