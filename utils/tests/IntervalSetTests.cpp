#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <sstream>
#include <utils/IntervalSet.hpp>

using namespace utils::interval;

TEST_CASE("[IntervalSet] Constructor", "[utils][IntervalSet]")
{
    SECTION("Normal constructor")
    {
        std::vector<Interval<int32_t>> const intervals{
            {Interval{1, 3}, Interval{-1, 4}, Interval{5, 7}}};
        IntervalSet const intervalSet{intervals};
        auto const& result1{intervalSet.get()};
        REQUIRE(result1.size() == 1U);
        CHECK(result1[0] == Interval{-1, 7});
    }
    SECTION("Move constructor")
    {
        IntervalSet const interval1{
            {Interval{1, 3}, Interval{-1, 4}, Interval{5, 7}}};
        auto const& result1{interval1.get()};
        REQUIRE(result1.size() == 1U);
        CHECK(result1[0] == Interval{-1, 7});
    }
}

TEST_CASE("[IntervalSet] add() method", "[utils][IntervalSet]")
{
    SECTION("Interval")
    {
        SECTION("Already-contained interval")
        {
            IntervalSet interval1{{Interval{1, 5}}};
            interval1.add(Interval{1, 2});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval{1, 5});
        }
        SECTION("Contiguous interval")
        {
            IntervalSet interval1{{Interval{1, 5}}};
            interval1.add(Interval{4, 6});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval{1, 6});
        }
        SECTION("Append interval")
        {
            IntervalSet interval1{{Interval{1, 5}}};
            interval1.add(Interval{7, 9});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 5});
            CHECK(result1[1] == Interval{7, 9});
        }
        SECTION("Fill the gap")
        {
            IntervalSet interval1{{Interval{1, 5}, Interval{7, 9}}};
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
            IntervalSet interval1{{Interval{1, 5}, Interval{7, 9}}};
            interval1.add(4);
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 5});
            CHECK(result1[1] == Interval{7, 9});
        }
        SECTION("New value")
        {
            IntervalSet interval2{{Interval{1, 5}, Interval{7, 9}}};
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
            IntervalSet interval1{{Interval{1, 5}}};
            interval1.remove(3);
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 2});
            CHECK(result1[1] == Interval{4, 5});
        }
        SECTION("Non-contained value")
        {
            IntervalSet interval1{{Interval{1, 5}}};
            interval1.remove(7);
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval{1, 5});
        }
        SECTION("Value in the border")
        {
            IntervalSet interval1{{Interval{1, 5}, Interval{7, 9}}};
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
            IntervalSet interval1{{Interval{1, 5}}};
            interval1.remove(Interval{3, 4});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 2});
            CHECK(result1[1] == Interval{5, 5});
        }
        SECTION("Non-contained values")
        {
            IntervalSet interval1{{Interval{1, 5}}};
            interval1.remove(Interval{7, 8});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 1U);
            CHECK(result1[0] == Interval{1, 5});
        }
        SECTION("Remove only contained values")
        {
            IntervalSet interval1{{Interval{1, 5}, Interval{7, 10}}};
            interval1.remove(Interval{4, 8});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 3});
            CHECK(result1[1] == Interval{9, 10});
        }
        SECTION("Remove values in several intervals")
        {
            IntervalSet interval1{
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
            IntervalSet interval1{{Interval{1, 5}}};
            interval1.remove(Interval{4, 4});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 2U);
            CHECK(result1[0] == Interval{1, 3});
            CHECK(result1[1] == Interval{5, 5});
        }
        SECTION("Keep untouched intervals")
        {
            IntervalSet interval1{{Interval{1, 5}, Interval{7, 9}}};
            interval1.remove(Interval{4, 4});
            auto const& result1{interval1.get()};
            REQUIRE(result1.size() == 3U);
            CHECK(result1[0] == Interval{1, 3});
            CHECK(result1[1] == Interval{5, 5});
            CHECK(result1[2] == Interval{7, 9});
        }
    }
}

TEST_CASE("[IntervalSet] count() method", "[utils][IntervalSet]")
{
    SECTION("With single-value intervals")
    {
        IntervalSet const interval1{{Interval{1, 1}}};
        CHECK(interval1.count() == 1U);
    }
    SECTION("With multiple intervals")
    {
        IntervalSet const interval1{{Interval{1, 2}, Interval{5, 7}}};
        CHECK(interval1.count() == 5U);
    }
}

TEST_CASE("[IntervalSet] extract() method", "[utils][IntervalSet]")
{
    SECTION("With multiple intervals")
    {
        IntervalSet interval1{{Interval{1, 2}, Interval{5, 7}}};
        IntervalSet interval2{interval1.extract(2, 5)};
        auto const& result1{interval2.get()};
        REQUIRE(result1.size() == 2U);
        CHECK(result1[0] == Interval{2, 2});
        CHECK(result1[1] == Interval{5, 5});
    }
}

TEST_CASE(
    "[IntervalSet] std::string Implicit conversion operator",
    "[utils][IntervalSet]")
{
    IntervalSet const interval1{{Interval{1, 2}, Interval{5, 7}}};
    CHECK(static_cast<std::string>(interval1) == "[1,2],[5,7]");
}

TEST_CASE("[IntervalSet] Output stream operator", "[utils][IntervalSet]")
{
    std::stringstream buffer;
    // Redirect std::cout to buffer
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    SECTION("Empty")
    {
        IntervalSet interval1{};
        std::cout << interval1;

        // Use the string value of buffer to compare against expected output
        std::string text = buffer.str();

        // Restore original buffer before exiting
        std::cout.rdbuf(prevcoutbuf);

        CHECK(text == "[]");
    }
    SECTION("Non empty")
    {
        IntervalSet interval1{{Interval{1, 2}, Interval{5, 7}}};
        std::cout << interval1;

        // Use the string value of buffer to compare against expected output
        std::string text = buffer.str();

        // Restore original buffer before exiting
        std::cout.rdbuf(prevcoutbuf);

        CHECK(text == "[1,2],[5,7]");
    }
}
