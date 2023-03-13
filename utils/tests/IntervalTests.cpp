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
    "[Interval - join] join() method returns correct values",
    "[Interval, Interval_join]")
{
    const Interval interval1{ 2, 3 };
    const Interval interval2{ -3, 1 };
    const Interval interval3{ interval1.join(interval2) };
    CHECK(interval3.get() == std::make_pair(-3, 3));
}

TEST_CASE(
    "[Interval - operator+] operator+() method returns correct values",
    "[Interval, Interval_operator+]")
{
    const Interval interval1{ 2, 3 };
    const Interval interval2{ -3, 1 };
    const Interval interval3{ interval1 + interval2 };
    CHECK(interval3.get() == std::make_pair(-3, 3));
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
    const Interval interval1{ 2, 4 };
    const Interval interval2{ -3, 1 };
    const Interval interval3{ -1, 3 };
    const Interval interval4{ 1, 2 };
    CHECK_FALSE(interval1.overlaps(interval2));
    CHECK_FALSE(interval2.overlaps(interval1));
    CHECK(interval1.overlaps(interval3));
    CHECK(interval3.overlaps(interval1));
    CHECK(interval2.overlaps(interval3));
    CHECK(interval3.overlaps(interval2));
    CHECK(interval4.overlaps(interval1));
    CHECK(interval1.overlaps(interval4));
}
