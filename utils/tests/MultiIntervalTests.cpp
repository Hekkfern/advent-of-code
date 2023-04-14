#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/MultiInterval.hpp>

using namespace utils::interval;

TEST_CASE("[MultiInterval] Constructor", "[utils][MultiInterval]")
{
    const MultiInterval<int32_t> interval1{
        {Interval<int32_t>{1, 3},
         Interval<int32_t>{-1, 4},
         Interval<int32_t>{5, 7}}};
    const auto& result1{interval1.get()};
    REQUIRE(result1.size() == 1U);
    CHECK(result1[0] == Interval<int32_t>{-1, 7});
}

TEST_CASE("[MultiInterval] add() method", "[utils][MultiInterval]")
{
    SECTION("Interval")
    {
        SECTION("Already-contained interval")
        {
            MultiInterval<int32_t> interval1{{Interval<int32_t>{1, 5}}};
            interval1.add(Interval<int32_t>{1, 2});
            const auto result1{interval1.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval<int32_t>{1, 5});
        }
        SECTION("Contiguous interval")
        {
            MultiInterval<int32_t> interval1{{Interval<int32_t>{1, 5}}};
            interval1.add(Interval<int32_t>{4, 6});
            const auto result1{interval1.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval<int32_t>{1, 6});
        }
        SECTION("Append interval")
        {
            MultiInterval<int32_t> interval1{{Interval<int32_t>{1, 5}}};
            interval1.add(Interval<int32_t>{7, 9});
            const auto result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval<int32_t>{1, 5});
            CHECK(result1[1] == Interval<int32_t>{7, 9});
        }
        SECTION("Fill the gap")
        {
            MultiInterval<int32_t> interval1{
                {Interval<int32_t>{1, 5}, Interval<int32_t>{7, 9}}};
            interval1.add(Interval<int32_t>{4, 8});
            const auto result1{interval1.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval<int32_t>{1, 9});
        }
    }
    SECTION("Single value")
    {
        SECTION("Already-contained value")
        {
            MultiInterval<int32_t> interval1{
                {Interval<int32_t>{1, 5}, Interval<int32_t>{7, 9}}};
            interval1.add(4);
            const auto result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval<int32_t>{1, 5});
            CHECK(result1[1] == Interval<int32_t>{7, 9});
        }
        SECTION("New value")
        {
            MultiInterval<int32_t> interval2{
                {Interval<int32_t>{1, 5}, Interval<int32_t>{7, 9}}};
            interval2.add(6);
            const auto result2{interval2.get()};
            REQUIRE(result2.size() == 1U);
            CHECK(result2[0] == Interval<int32_t>{1, 9});
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
            MultiInterval<int32_t> interval1{{Interval<int32_t>{1, 5}}};
            interval1.remove(3);
            const auto result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval<int32_t>{1, 2});
            CHECK(result1[1] == Interval<int32_t>{4, 5});
        }
        SECTION("Non-contained value")
        {
            MultiInterval<int32_t> interval1{{Interval<int32_t>{1, 5}}};
            interval1.remove(7);
            const auto result1{interval1.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval<int32_t>{1, 5});
        }
        SECTION("Value in the border")
        {
            MultiInterval<int32_t> interval1{
                {Interval<int32_t>{1, 5}, Interval<int32_t>{7, 9}}};
            interval1.remove(5);
            const auto result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval<int32_t>{1, 4});
            CHECK(result1[1] == Interval<int32_t>{7, 9});
        }
    }
    SECTION("Interval")
    {
        SECTION("Delete a completely-contained interval")
        {
            MultiInterval<int32_t> interval1{{Interval<int32_t>{1, 5}}};
            interval1.remove(Interval<int32_t>{3, 4});
            const auto result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval<int32_t>{1, 2});
            CHECK(result1[1] == Interval<int32_t>{5, 5});
        }
        SECTION("Non-contained values")
        {
            MultiInterval<int32_t> interval1{{Interval<int32_t>{1, 5}}};
            interval1.remove(Interval<int32_t>{7, 8});
            const auto result1{interval1.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval<int32_t>{1, 5});
        }
        SECTION("Remove only contained values")
        {
            MultiInterval<int32_t> interval1{
                {Interval<int32_t>{1, 5}, Interval<int32_t>{7, 10}}};
            interval1.remove(Interval<int32_t>{4, 8});
            const auto result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval<int32_t>{1, 3});
            CHECK(result1[1] == Interval<int32_t>{9, 10});
        }
        SECTION("Remove values in several intervals")
        {
            MultiInterval<int32_t> interval1{
                {Interval<int32_t>{1, 3},
                 Interval<int32_t>{5, 6},
                 Interval<int32_t>{8, 10}}};
            interval1.remove(Interval<int32_t>{2, 8});
            const auto result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval<int32_t>{1, 1});
            CHECK(result1[1] == Interval<int32_t>{9, 10});
        }
    }
    SECTION("Single-value interval")
    {
        SECTION("Split in half")
        {
            MultiInterval<int32_t> interval1{{Interval<int32_t>{1, 5}}};
            interval1.remove(Interval<int32_t>{4, 4});
            const auto result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval<int32_t>{1, 3});
            CHECK(result1[1] == Interval<int32_t>{5, 5});
        }
        SECTION("Keep untouched intervals")
        {
            MultiInterval<int32_t> interval1{
                {Interval<int32_t>{1, 5}, Interval<int32_t>{7, 9}}};
            interval1.remove(Interval<int32_t>{4, 4});
            const auto result1{interval1.get()};
            REQUIRE(result1.size() == 3U);
            CHECK(result1[0] == Interval<int32_t>{1, 3});
            CHECK(result1[1] == Interval<int32_t>{5, 5});
            CHECK(result1[2] == Interval<int32_t>{7, 9});
        }
    }
}

TEST_CASE("[MultiInterval] count() method", "[utils][MultiInterval]")
{
    SECTION("With single-value intervals")
    {
        const MultiInterval<int32_t> interval1{{Interval<int32_t>{1, 1}}};
        CHECK(interval1.count() == 1U);
    }
    SECTION("With multiple intervals")
    {
        const MultiInterval<int32_t> interval1{
            {Interval<int32_t>{1, 2}, Interval<int32_t>{5, 7}}};
        CHECK(interval1.count() == 5U);
    }
}

TEST_CASE("[MultiInterval] extract() method", "[utils][MultiInterval]")
{
    SECTION("With multiple intervals")
    {
        MultiInterval<int32_t> interval1{
            {Interval<int32_t>{1, 2}, Interval<int32_t>{5, 7}}};
        MultiInterval<int32_t> interval2{interval1.extract(2, 5)};
        const auto result1{interval2.get()};
        REQUIRE(result1.size() == 2U);
        CHECK(result1[0] == Interval<int32_t>{2, 2});
        CHECK(result1[1] == Interval<int32_t>{5, 5});
    }
}
