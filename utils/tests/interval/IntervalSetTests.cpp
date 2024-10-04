#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iostream>
#include <sstream>
#include <utils/interval/IntervalSet.hpp>

using namespace utils::interval;

TEST_CASE("[IntervalSet] Constructor", "[utils][IntervalSet]")
{
    SECTION("Default constructor")
    {
        IntervalSet<> const intervalSet;
        auto const result1{intervalSet.get()};
        REQUIRE(result1.empty());
    }
    SECTION("Parametrized constructor 1")
    {
        SECTION("Empty")
        {
            std::vector<Interval<>> const intervals;
            IntervalSet const intervalSet{intervals};
            auto const result1{intervalSet.get()};
            REQUIRE(result1.empty());
        }
        SECTION("Non-empty")
        {
            std::vector<Interval<>> const intervals{
                {Interval{1, 3}, Interval{-1, 4}, Interval{5, 7}}};
            IntervalSet const intervalSet{intervals};
            auto const result1{intervalSet.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval{-1, 7});
        }
    }
    SECTION("Parametrized constructor 2")
    {
        SECTION("Empty")
        {
            IntervalSet const interval1{std::vector<Interval<int32_t>>{}};
            auto const result1{interval1.get()};
            REQUIRE(result1.empty());
        }
        SECTION("Non-empty")
        {
            IntervalSet<> const interval1{std::vector<Interval<int32_t>>{
                Interval{1, 3}, Interval{-1, 4}, Interval{5, 7}}};
            auto const result1{interval1.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval{-1, 7});
        }
    }
}

TEST_CASE("[IntervalSet] add() method", "[utils][IntervalSet]")
{
    SECTION("Interval")
    {
        SECTION("Already-contained interval")
        {
            IntervalSet interval1{std::vector<Interval<>>{Interval{1, 5}}};
            interval1.add(Interval<>{1, 2});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval{1, 5});
        }
        SECTION("Contiguous interval")
        {
            IntervalSet interval1{std::vector<Interval<>>{Interval{1, 5}}};
            interval1.add(Interval{4, 6});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval{1, 6});
        }
        SECTION("Append interval")
        {
            IntervalSet interval1{std::vector<Interval<>>{Interval{1, 5}}};
            interval1.add(Interval{7, 9});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 5});
            CHECK(result1[1] == Interval{7, 9});
        }
        SECTION("Fill the gap")
        {
            IntervalSet interval1{
                std::vector<Interval<>>{Interval{1, 5}, Interval{7, 9}}};
            interval1.add(Interval{4, 8});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval{1, 9});
        }
    }
    SECTION("Single value")
    {
        SECTION("Already-contained value")
        {
            IntervalSet interval1{
                std::vector<Interval<>>{Interval{1, 5}, Interval{7, 9}}};
            interval1.add(4);
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 5});
            CHECK(result1[1] == Interval{7, 9});
        }
        SECTION("New value")
        {
            IntervalSet interval2{
                std::vector<Interval<>>{Interval{1, 5}, Interval{7, 9}}};
            interval2.add(6);
            auto const& result2{interval2.get()};
            REQUIRE(result2.size() == 1U);
            CHECK(result2[0] == Interval{1, 9});
        }
    }
}

TEST_CASE("[IntervalSet] remove() method", "[utils][IntervalSet]")
{
    SECTION("Single value")
    {
        SECTION("Splits in half")
        {
            IntervalSet interval1{std::vector<Interval<>>{Interval{1, 5}}};
            interval1.remove(3);
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 2});
            CHECK(result1[1] == Interval{4, 5});
        }
        SECTION("Non-contained value")
        {
            IntervalSet interval1{std::vector<Interval<>>{Interval{1, 5}}};
            interval1.remove(7);
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval{1, 5});
        }
        SECTION("Value in the border")
        {
            IntervalSet interval1{
                std::vector<Interval<>>{Interval{1, 5}, Interval{7, 9}}};
            interval1.remove(5);
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 4});
            CHECK(result1[1] == Interval{7, 9});
        }
    }
    SECTION("Normal interval")
    {
        SECTION("Delete a completely-contained interval")
        {
            IntervalSet interval1{std::vector<Interval<>>{Interval{1, 5}}};
            interval1.remove(Interval{3, 4});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 2});
            CHECK(result1[1] == Interval{5, 5});
        }
        SECTION("Non-contained values")
        {
            IntervalSet interval1{std::vector<Interval<>>{Interval{1, 5}}};
            interval1.remove(Interval{7, 8});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval{1, 5});
        }
        SECTION("Remove only contained values")
        {
            IntervalSet interval1{
                std::vector<Interval<>>{Interval{1, 5}, Interval{7, 10}}};
            interval1.remove(Interval{4, 8});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 3});
            CHECK(result1[1] == Interval{9, 10});
        }
        SECTION("Remove values in several intervals")
        {
            IntervalSet interval1{std::vector<Interval<>>{
                Interval{1, 3}, Interval{5, 6}, Interval{8, 10}}};
            interval1.remove(Interval{2, 8});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 1});
            CHECK(result1[1] == Interval{9, 10});
        }
    }
    SECTION("Single-value interval")
    {
        SECTION("Split in half")
        {
            IntervalSet interval1{std::vector<Interval<>>{Interval{1, 5}}};
            interval1.remove(Interval{4, 4});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 3});
            CHECK(result1[1] == Interval{5, 5});
        }
        SECTION("Keep untouched intervals")
        {
            IntervalSet interval1{
                std::vector<Interval<>>{Interval{1, 5}, Interval{7, 9}}};
            interval1.remove(Interval{4, 4});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 3U);
            CHECK(result1[0] == Interval{1, 3});
            CHECK(result1[1] == Interval{5, 5});
            CHECK(result1[2] == Interval{7, 9});
        }
    }
}

TEST_CASE("[IntervalSet] join() method", "[utils][IntervalSet]")
{
    SECTION("Non-overlapping intervals")
    {
        IntervalSet const intervalSet1{
            std::vector<Interval<>>{Interval{1, 1}, Interval{7, 8}}};
        IntervalSet const intervalSet2{std::vector<Interval<>>{Interval{3, 3}}};
        CHECK(
            intervalSet1.join(intervalSet2)
            == IntervalSet{std::vector<Interval<>>{
                Interval{1, 1}, Interval{3, 3}, Interval{7, 8}}});
    }
    SECTION("Overlapping intervals")
    {
        IntervalSet const intervalSet1{
            std::vector<Interval<>>{Interval{1, 4}, Interval{7, 8}}};
        IntervalSet const intervalSet2{std::vector<Interval<>>{Interval{3, 3}}};
        CHECK(
            intervalSet1.join(intervalSet2)
            == IntervalSet{
                std::vector<Interval<>>{Interval{1, 4}, Interval{7, 8}}});
    }
}

TEST_CASE("[IntervalSet] subsumes() method", "[utils][IntervalSet]")
{
    IntervalSet const intervalSet1{std::vector<Interval<>>{Interval{1, 2}}};
    SECTION("Another IntervalSet")
    {
        SECTION("Completely")
        {
            IntervalSet const intervalSet2{
                std::vector<Interval<>>{Interval{0, 4}}};
            CHECK_FALSE(intervalSet1.subsumes(intervalSet2));
            CHECK(intervalSet2.subsumes(intervalSet1));
        }
        SECTION("Equal intervals")
        {
            IntervalSet const intervalSet2{
                std::vector<Interval<>>{Interval{1, 2}}};
            CHECK(intervalSet1.subsumes(intervalSet2));
            CHECK(intervalSet2.subsumes(intervalSet1));
        }
        SECTION("Different intervals")
        {
            IntervalSet const intervalSet2{
                std::vector<Interval<>>{Interval{4, 4}}};
            CHECK_FALSE(intervalSet1.subsumes(intervalSet2));
            CHECK_FALSE(intervalSet2.subsumes(intervalSet1));
        }
    }
    SECTION("Another Interval")
    {
        SECTION("Completely")
        {
            Interval const interval2{0, 4};
            CHECK_FALSE(intervalSet1.subsumes(interval2));
        }
        SECTION("Equal intervals")
        {
            Interval const interval2{1, 2};
            CHECK(intervalSet1.subsumes(interval2));
        }
        SECTION("Different intervals")
        {
            Interval const interval2{4, 4};
            CHECK_FALSE(intervalSet1.subsumes(interval2));
        }
    }
}

TEST_CASE("[IntervalSet] overlaps() method", "[utils][IntervalSet]")
{
    IntervalSet const intervalSet1{std::vector<Interval<>>{Interval{1, 2}}};
    SECTION("Another IntervalSet")
    {
        SECTION("Completely")
        {
            IntervalSet const intervalSet2{
                std::vector<Interval<>>{Interval{0, 4}}};
            CHECK(intervalSet1.overlaps(intervalSet2));
            CHECK(intervalSet2.overlaps(intervalSet1));
        }
        SECTION("Equal intervals")
        {
            IntervalSet const intervalSet2{
                std::vector<Interval<>>{Interval{1, 2}}};
            CHECK(intervalSet1.overlaps(intervalSet2));
            CHECK(intervalSet2.overlaps(intervalSet1));
        }
        SECTION("Different intervals")
        {
            IntervalSet const intervalSet2{
                std::vector<Interval<>>{Interval{4, 4}}};
            CHECK_FALSE(intervalSet1.overlaps(intervalSet2));
            CHECK_FALSE(intervalSet2.overlaps(intervalSet1));
        }
        SECTION("Touch one boundary")
        {
            IntervalSet const intervalSet2{
                std::vector<Interval<>>{Interval{0, 1}}};
            CHECK(intervalSet1.overlaps(intervalSet2));
            CHECK(intervalSet2.overlaps(intervalSet1));
        }
    }
    SECTION("Another Interval")
    {
        SECTION("Completely")
        {
            Interval const interval2{0, 4};
            CHECK(intervalSet1.overlaps(interval2));
        }
        SECTION("Equal intervals")
        {
            Interval const interval2{1, 2};
            CHECK(intervalSet1.overlaps(interval2));
        }
        SECTION("Different intervals")
        {
            Interval const interval2{4, 4};
            CHECK_FALSE(intervalSet1.overlaps(interval2));
        }
        SECTION("Touch one boundary")
        {
            Interval const interval2{0, 1};
            CHECK(intervalSet1.overlaps(interval2));
        }
    }
}

TEST_CASE("[IntervalSet] contains() method", "[utils][IntervalSet]")
{
    IntervalSet const intervalSet1{std::vector<Interval<>>{Interval{1, 4}}};
    CHECK_FALSE(intervalSet1.contains(-1));
    CHECK(intervalSet1.contains(1));
    CHECK(intervalSet1.contains(2));
    CHECK(intervalSet1.contains(4));
    CHECK_FALSE(intervalSet1.contains(7));
}

TEST_CASE("[IntervalSet] count() method", "[utils][IntervalSet]")
{
    SECTION("With single-value intervals")
    {
        IntervalSet const interval1{std::vector<Interval<>>{Interval{1, 1}}};
        CHECK(interval1.count() == 1U);
    }
    SECTION("With multiple intervals")
    {
        IntervalSet const interval1{
            std::vector<Interval<>>{Interval{1, 2}, Interval{5, 7}}};
        CHECK(interval1.count() == 5U);
    }
}

TEST_CASE("[IntervalSet] extract() method", "[utils][IntervalSet]")
{
    SECTION("With multiple intervals")
    {
        IntervalSet interval1{
            std::vector<Interval<>>{Interval{1, 2}, Interval{5, 7}}};
        IntervalSet interval2{interval1.extract(2, 5)};
        auto const& result1{interval2.get()};
        REQUIRE(result1.size() == 2U);
        CHECK(result1[0] == Interval{2, 2});
        CHECK(result1[1] == Interval{5, 5});
    }
}

TEST_CASE("[IntervalSet] getIntervalFor() method", "[utils][IntervalSet]")
{
    IntervalSet const intervalSet1{
        std::vector<Interval<>>{Interval{1, 4}, Interval{7, 10}}};
    SECTION("Value is contained")
    {
        auto const result{intervalSet1.getIntervalFor(2)};
        REQUIRE(result);
        CHECK(*result == Interval{1, 4});
    }
    SECTION("Value is not contained")
    {
        auto const result{intervalSet1.getIntervalFor(-7)};
        REQUIRE_FALSE(result);
    }
}

TEST_CASE("[IntervalSet] intersect() method", "[utils][IntervalSet]")
{
    IntervalSet const intervalSet1{
        std::vector<Interval<>>{Interval{1, 4}, Interval{7, 10}}};
    SECTION("Subsumed")
    {
        Interval const interval2{8, 9};
        auto const result{intervalSet1.intersect(interval2)};
        REQUIRE_FALSE(result.empty());
        auto const& intersectedIntervals{result.get()};
        REQUIRE(intersectedIntervals.size() == 1);
        CHECK(intersectedIntervals[0] == Interval{8, 9});
    }
    SECTION("Equal intervals")
    {
        Interval const interval2{1, 4};
        auto const result{intervalSet1.intersect(interval2)};
        REQUIRE_FALSE(result.empty());
        auto const& intersectedIntervals{result.get()};
        REQUIRE(intersectedIntervals.size() == 1);
        CHECK(intersectedIntervals[0] == Interval{1, 4});
    }
    SECTION("Isolated")
    {
        Interval const interval2{5, 5};
        auto const result{intervalSet1.intersect(interval2)};
        REQUIRE(result.empty());
    }
    SECTION("Touch one boundary")
    {
        Interval const interval2{0, 1};
        auto const result{intervalSet1.intersect(interval2)};
        REQUIRE_FALSE(result.empty());
        auto const& intersectedIntervals{result.get()};
        REQUIRE(intersectedIntervals.size() == 1);
        CHECK(intersectedIntervals[0] == Interval{1, 1});
    }
}

TEST_CASE("[IntervalSet] empty() method", "[utils][IntervalSet]")
{
    SECTION("Empty")
    {
        IntervalSet<> const intervalSet1;
        CHECK(intervalSet1.empty());
    }
    SECTION("Non-empty")
    {
        IntervalSet const intervalSet1{
            std::vector<Interval<>>{Interval{1, 4}, Interval{7, 10}}};
        CHECK_FALSE(intervalSet1.empty());
    }
}

TEST_CASE("[IntervalSet] toString() method", "[utils][IntervalSet]")
{
    SECTION("Empty")
    {
        IntervalSet const interval1;
        CHECK(interval1.toString().empty());
    }
    SECTION("Non empty")
    {
        IntervalSet const interval1{
            std::vector<Interval<>>{Interval{1, 2}, Interval{5, 7}}};
        CHECK(interval1.toString() == "[1,2],[5,7]");
    }
}

TEST_CASE("[IntervalSet] Equality operator", "[utils][IntervalSet]")
{
    SECTION("Empty IntervalSet")
    {
        IntervalSet<> const interval1;
        IntervalSet<> const interval2;
        CHECK(interval1 == interval2);
        CHECK_FALSE(interval1 != interval2);
    }
    SECTION("Non-empty IntervalSet")
    {
        SECTION("Equal")
        {
            IntervalSet const interval1{
                std::vector<Interval<>>{Interval{1, 2}, Interval{5, 7}}};
            IntervalSet const interval2{
                std::vector<Interval<>>{Interval{1, 2}, Interval{5, 7}}};
            CHECK(interval1 == interval2);
            CHECK_FALSE(interval1 != interval2);
        }
        SECTION("Different")
        {
            IntervalSet const interval1{
                std::vector<Interval<>>{Interval{1, 2}, Interval{5, 7}}};
            IntervalSet const interval2{
                std::vector<Interval<>>{Interval{4, 7}}};
            CHECK_FALSE(interval1 == interval2);
            CHECK(interval1 != interval2);
        }
    }
}

TEST_CASE("[IntervalSet] Output stream operator", "[utils][IntervalSet]")
{
    std::ostringstream oss;

    SECTION("Empty")
    {
        IntervalSet interval1{};
        oss << interval1;

        // Use the string value of buffer to compare against expected output
        std::string text = oss.str();

        CHECK(text.empty());
    }
    SECTION("Non empty")
    {
        IntervalSet interval1{
            std::vector<Interval<>>{Interval{1, 2}, Interval{5, 7}}};
        oss << interval1;

        // Use the string value of buffer to compare against expected output
        std::string text = oss.str();

        CHECK(text == "[1,2],[5,7]");
    }
}

TEST_CASE("[IntervalSet] Iterators", "[utils][IntervalSet]")
{
    SECTION("Non-const")
    {
        IntervalSet interval1{
            std::vector<Interval<>>{Interval{1, 2}, Interval{5, 7}}};
        int count{0};
        SECTION("With FOR-RANGE loop")
        {
            for (auto& item : interval1) {
                (void)item;
                ++count;
            }
        }
        SECTION("With normal FOR loop")
        {
            for (auto it = interval1.begin(), end = interval1.end(); it != end;
                 ++it) {
                ++count;
            }
        }
        REQUIRE(count == 2);
    }
    SECTION("Const")
    {
        IntervalSet const interval1{
            std::vector<Interval<>>{Interval{1, 2}, Interval{5, 7}}};
        int count{0};
        SECTION("With FOR-RANGE loop")
        {
            for (auto const& item : interval1) {
                (void)item;
                ++count;
            }
        }
        SECTION("With normal FOR loop")
        {
            for (
                auto it = interval1.cbegin(), end = interval1.cend(); it != end;
                ++it) {
                ++count;
            }
        }
        REQUIRE(count == 2);
    }
}
