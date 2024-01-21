#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/MultiInterval.hpp>

using namespace utils::interval;

TEST_CASE("[MultiInterval] Constructor", "[utils][MultiInterval]")
{
    SECTION("Normal constructor")
    {
        std::vector<Interval<int32_t>> const intervals{
            {Interval{1, 3}, Interval{-1, 4}, Interval{5, 7}}};
        MultiInterval const multiInterval{intervals};
        auto const& result1{multiInterval.get()};
        REQUIRE(result1.size() == 1U);
        CHECK(result1[0] == Interval{-1, 7});
    }
    SECTION("Move constructor")
    {
        MultiInterval const interval1{
            {Interval{1, 3}, Interval{-1, 4}, Interval{5, 7}}};
        auto const& result1{interval1.get()};
        REQUIRE(result1.size() == 1U);
        CHECK(result1[0] == Interval{-1, 7});
    }
}

TEST_CASE("[MultiInterval] add() method", "[utils][MultiInterval]")
{
    SECTION("Interval")
    {
        SECTION("Already-contained interval")
        {
            MultiInterval interval1{{Interval{1, 5}}};
            interval1.add(Interval{1, 2});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval{1, 5});
        }
        SECTION("Contiguous interval")
        {
            MultiInterval interval1{{Interval{1, 5}}};
            interval1.add(Interval{4, 6});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval{1, 6});
        }
        SECTION("Append interval")
        {
            MultiInterval interval1{{Interval{1, 5}}};
            interval1.add(Interval{7, 9});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 5});
            CHECK(result1[1] == Interval{7, 9});
        }
        SECTION("Fill the gap")
        {
            MultiInterval interval1{{Interval{1, 5}, Interval{7, 9}}};
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
            MultiInterval interval1{{Interval{1, 5}, Interval{7, 9}}};
            interval1.add(4);
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 5});
            CHECK(result1[1] == Interval{7, 9});
        }
        SECTION("New value")
        {
            MultiInterval interval2{{Interval{1, 5}, Interval{7, 9}}};
            interval2.add(6);
            auto const& result2{interval2.get()};
            REQUIRE(result2.size() == 1U);
            CHECK(result2[0] == Interval{1, 9});
        }
    }
}

TEST_CASE(
    "[MultiInterval] remove() method"
    "[utils][MultiInterval]")
{
    SECTION("Single value")
    {
        SECTION("Splits in half")
        {
            MultiInterval interval1{{Interval{1, 5}}};
            interval1.remove(3);
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 2});
            CHECK(result1[1] == Interval{4, 5});
        }
        SECTION("Non-contained value")
        {
            MultiInterval interval1{{Interval{1, 5}}};
            interval1.remove(7);
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval{1, 5});
        }
        SECTION("Value in the border")
        {
            MultiInterval interval1{{Interval{1, 5}, Interval{7, 9}}};
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
            MultiInterval interval1{{Interval{1, 5}}};
            interval1.remove(Interval{3, 4});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 2});
            CHECK(result1[1] == Interval{5, 5});
        }
        SECTION("Non-contained values")
        {
            MultiInterval interval1{{Interval{1, 5}}};
            interval1.remove(Interval{7, 8});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval{1, 5});
        }
        SECTION("Remove only contained values")
        {
            MultiInterval interval1{{Interval{1, 5}, Interval{7, 10}}};
            interval1.remove(Interval{4, 8});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 3});
            CHECK(result1[1] == Interval{9, 10});
        }
        SECTION("Remove values in several intervals")
        {
            MultiInterval interval1{
                {Interval{1, 3}, Interval{5, 6}, Interval{8, 10}}};
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
            MultiInterval interval1{{Interval{1, 5}}};
            interval1.remove(Interval{4, 4});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 3});
            CHECK(result1[1] == Interval{5, 5});
        }
        SECTION("Keep untouched intervals")
        {
            MultiInterval interval1{{Interval{1, 5}, Interval{7, 9}}};
            interval1.remove(Interval{4, 4});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 3U);
            CHECK(result1[0] == Interval{1, 3});
            CHECK(result1[1] == Interval{5, 5});
            CHECK(result1[2] == Interval{7, 9});
        }
    }
}

TEST_CASE("[MultiInterval] count() method", "[utils][MultiInterval]")
{
    SECTION("With single-value intervals")
    {
        MultiInterval const interval1{{Interval{1, 1}}};
        CHECK(interval1.count() == 1U);
    }
    SECTION("With multiple intervals")
    {
        MultiInterval const interval1{{Interval{1, 2}, Interval{5, 7}}};
        CHECK(interval1.count() == 5U);
    }
}

TEST_CASE("[MultiInterval] extract() method", "[utils][MultiInterval]")
{
    SECTION("With multiple intervals")
    {
        MultiInterval interval1{{Interval{1, 2}, Interval{5, 7}}};
        MultiInterval interval2{interval1.extract(2, 5)};
        auto const& result1{interval2.get()};
        REQUIRE(result1.size() == 2U);
        CHECK(result1[0] == Interval{2, 2});
        CHECK(result1[1] == Interval{5, 5});
    }
}
