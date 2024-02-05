#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <sstream>
#include <utils/interval/Interval.hpp>

using namespace utils::interval;

TEST_CASE("[Interval] Constructor", "[utils][Interval]")
{
    SECTION("Positive values")
    {
        Interval const interval1{2, 3};
        CHECK(interval1.getMin() == 2);
        CHECK(interval1.getMax() == 3);
        CHECK(interval1.get() == std::make_pair(2, 3));
    }
    SECTION("Positive and negatives values")
    {
        Interval const interval2{-3, 1};
        CHECK(interval2.getMin() == -3);
        CHECK(interval2.getMax() == 1);
        CHECK(interval2.get() == std::make_pair(-3, 1));
    }
    SECTION("Static tests")
    {
        SECTION("Positive values")
        {
            constexpr Interval interval1{2, 3};
            STATIC_CHECK(interval1.get() == std::make_pair(2, 3));
            STATIC_CHECK(interval1.getMin() == 2);
            STATIC_CHECK(interval1.getMax() == 3);
        }
        SECTION("Positive and negatives values")
        {
            constexpr Interval interval1{std::make_pair(-3, 1)};
            STATIC_CHECK(interval1.get() == std::make_pair(-3, 1));
            STATIC_CHECK(interval1.getMin() == -3);
            STATIC_CHECK(interval1.getMax() == 1);
        }
    }
}

TEST_CASE("[Interval] length() method", "[utils][Interval]")
{
    SECTION("Positive values")
    {
        Interval const interval1{2, 3};
        CHECK(interval1.length() == 2ULL);
    }
    SECTION("Positive and negatives values")
    {
        Interval const interval2{-3, 1};
        CHECK(interval2.length() == 5ULL);
    }
    SECTION("Static tests")
    {
        STATIC_CHECK(Interval{2, 3}.length() == 2ULL);
        STATIC_CHECK(Interval{-3, 1}.length() == 5ULL);
    }
}

TEST_CASE("[Interval] join() method", "[utils][Interval]")
{
    SECTION("Both intervals are contiguous, but they don't overlap")
    {
        Interval const interval1{2, 4};
        Interval const interval2{-3, 1};
        std::optional<Interval<>> const result1{interval1.join(interval2)};
        CHECK(result1);
        CHECK(result1->get() == std::make_pair(-3, 4));
    }
    SECTION("One interval contains the other")
    {
        Interval const interval1{2, 4};
        Interval const interval2{3, 6};
        std::optional<Interval<>> const result2{interval1.join(interval2)};
        CHECK(result2);
        CHECK(result2->get() == std::make_pair(2, 6));
    }
    SECTION("Left overlap")
    {
        Interval const interval1{2, 4};
        Interval const interval2{-3, 1};
        std::optional<Interval<>> const result1{interval1.join(interval2)};
        CHECK(result1);
        CHECK(result1->get() == std::make_pair(-3, 4));
    }
    SECTION("Right overlap")
    {
        Interval const interval1{2, 4};
        Interval const interval2{3, 6};
        std::optional<Interval<>> const result2{interval1.join(interval2)};
        CHECK(result2);
        CHECK(result2->get() == std::make_pair(2, 6));
    }
    SECTION("They don't overlap")
    {
        Interval const interval1{2, 4};
        Interval const interval2{-3, 3};
        std::optional<Interval<>> const result1{interval1.join(interval2)};
        CHECK(result1);
        CHECK(result1->get() == std::make_pair(-3, 4));
    }
    SECTION("The other interval is a single-value interval")
    {
        SECTION("Left extreme")
        {
            Interval const interval1{2, 4};
            Interval const interval2{2, 2};
            std::optional<Interval<>> const result1{interval1.join(interval2)};
            CHECK(result1);
            CHECK(result1->get() == std::make_pair(2, 4));
        }
        SECTION("Right extreme")
        {
            Interval const interval1{2, 4};
            Interval const interval2{4, 4};
            std::optional<Interval<>> const result1{interval1.join(interval2)};
            CHECK(result1);
            CHECK(result1->get() == std::make_pair(2, 4));
        }
        SECTION("In the middle")
        {
            Interval const interval1{-1, 4};
            Interval const interval2{2, 2};
            std::optional<Interval<>> const result1{interval1.join(interval2)};
            CHECK(result1);
            CHECK(result1->get() == std::make_pair(-1, 4));
        }
        SECTION("Outside on the left side")
        {
            SECTION("Contiguous")
            {
                Interval const interval1{2, 4};
                Interval const interval2{1, 1};
                std::optional<Interval<>> const result2{
                    interval1.join(interval2)};
                CHECK(result2);
                CHECK(result2->get() == std::make_pair(1, 4));
            }
            SECTION("Non-contiguous")
            {
                Interval const interval1{2, 4};
                Interval const interval2{-1, -1};
                std::optional<Interval<>> const result2{
                    interval1.join(interval2)};
                CHECK_FALSE(result2);
            }
        }
        SECTION("Outside on the right side")
        {
            SECTION("Contiguous")
            {
                Interval const interval1{2, 4};
                Interval const interval2{5, 5};
                std::optional<Interval<>> const result2{
                    interval1.join(interval2)};
                CHECK(result2);
                CHECK(result2->get() == std::make_pair(2, 5));
            }
            SECTION("Non-contiguous")
            {
                Interval const interval1{2, 4};
                Interval const interval2{7, 7};
                std::optional<Interval<>> const result2{
                    interval1.join(interval2)};
                CHECK_FALSE(result2);
            }
        }
    }
    SECTION("Static tests")
    {
        STATIC_CHECK(Interval{2, 3}.join(Interval{4, 6}) == Interval{2, 6});
        STATIC_CHECK(Interval{2, 5}.join(Interval{3, 4}) == Interval{2, 5});
    }
}

TEST_CASE("[Interval] intersect() method", "[utils][Interval]")
{
    SECTION("No overlap")
    {
        Interval const interval1{2, 3};
        Interval const interval2{-3, 1};
        auto const result{interval1.intersect(interval2)};
        CHECK_FALSE(result);
        auto const result2{interval2.intersect(interval1)};
        CHECK_FALSE(result2);
    }
    SECTION("One interval is contained in the other one")
    {
        Interval const interval1{2, 3};
        Interval const interval2{-3, 4};
        auto const result{interval1.intersect(interval2)};
        CHECK(result);
        CHECK(result->get() == std::make_pair(2, 3));
        auto const result2{interval2.intersect(interval1)};
        CHECK(result2);
        CHECK(result2->get() == std::make_pair(2, 3));
    }
    SECTION("Left overlap")
    {
        Interval const interval1{-3, 4};
        Interval const interval2{-5, -1};
        auto const result{interval1.intersect(interval2)};
        CHECK(result);
        CHECK(result->get() == std::make_pair(-3, -1));
        auto const result2{interval2.intersect(interval1)};
        CHECK(result2);
        CHECK(result2->get() == std::make_pair(-3, -1));
    }
    SECTION("Right overlap")
    {
        Interval const interval1{-3, 4};
        Interval const interval2{2, 7};
        auto const result{interval1.intersect(interval2)};
        CHECK(result);
        CHECK(result->get() == std::make_pair(2, 4));
        auto const result2{interval2.intersect(interval1)};
        CHECK(result2);
        CHECK(result2->get() == std::make_pair(2, 4));
    }
    SECTION("Intervals share one extreme value")
    {
        SECTION("Left extreme")
        {
            Interval const interval1{-3, 1};
            Interval const interval2{-3, 4};
            auto const result{interval1.intersect(interval2)};
            CHECK(result);
            CHECK(result->get() == std::make_pair(-3, 1));
            auto const result2{interval2.intersect(interval1)};
            CHECK(result2);
            CHECK(result2->get() == std::make_pair(-3, 1));
        }
        SECTION("Right extreme")
        {
            Interval const interval1{1, 4};
            Interval const interval2{-3, 4};
            auto const result{interval1.intersect(interval2)};
            CHECK(result);
            CHECK(result->get() == std::make_pair(1, 4));
            auto const result2{interval2.intersect(interval1)};
            CHECK(result2);
            CHECK(result2->get() == std::make_pair(1, 4));
        }
    }
    SECTION("Static tests")
    {
        STATIC_CHECK_FALSE(Interval{2, 3}.intersect(Interval{-3, 1}));
        STATIC_CHECK(
            Interval{2, 3}.intersect(Interval{-3, 4}) == Interval{2, 3});
    }
}

TEST_CASE("[Interval] subsumes() method", "[utils][Interval]")
{
    SECTION("One interval includes the other one totally")
    {
        Interval const interval1{2, 3};
        Interval const interval2{-3, 6};
        CHECK_FALSE(interval1.subsumes(interval2));
        CHECK(interval2.subsumes(interval1));
    }
    SECTION("Contiguous intervals")
    {
        Interval const interval1{2, 3};
        Interval const interval2{-3, 1};
        CHECK_FALSE(interval1.subsumes(interval2));
        CHECK_FALSE(interval2.subsumes(interval1));
    }
    SECTION("Intervals share one extreme value")
    {
        SECTION("Left extreme")
        {
            Interval const interval1{1, 3};
            Interval const interval2{1, 5};
            CHECK(interval2.subsumes(interval1));
            CHECK_FALSE(interval1.subsumes(interval2));
        }
        SECTION("Right extreme")
        {
            Interval const interval1{2, 3};
            Interval const interval2{-3, 3};
            CHECK(interval2.subsumes(interval1));
            CHECK_FALSE(interval1.subsumes(interval2));
        }
    }
    SECTION("Static tests")
    {
        STATIC_CHECK_FALSE(Interval{2, 3}.subsumes(Interval{-3, 6}));
        STATIC_CHECK(Interval{-3, 6}.subsumes(Interval{2, 3}));
    }
}

TEST_CASE("[Interval] overlaps() method", "[utils][Interval]")
{
    SECTION("Left overlap")
    {
        Interval const interval1{2, 6};
        Interval const interval2{1, 3};
        CHECK(interval1.overlaps(interval2));
        CHECK(interval2.overlaps(interval1));
    }
    SECTION("Right overlap")
    {
        Interval const interval1{2, 6};
        Interval const interval2{5, 7};
        CHECK(interval1.overlaps(interval2));
        CHECK(interval2.overlaps(interval1));
    }
    SECTION("One interval includes the other one totally")
    {
        Interval const interval1{2, 6};
        Interval const interval2{4, 5};
        CHECK(interval2.overlaps(interval1));
        CHECK(interval1.overlaps(interval2));
    }
    SECTION("Their left extremes touch")
    {
        Interval const interval1{2, 6};
        Interval const interval2{1, 2};
        CHECK(interval1.overlaps(interval2));
        CHECK(interval2.overlaps(interval1));
    }
    SECTION("Their right extremes touch")
    {
        Interval const interval1{2, 6};
        Interval const interval2{6, 7};
        CHECK(interval1.overlaps(interval2));
        CHECK(interval2.overlaps(interval1));
    }
    SECTION("Static tests")
    {
        STATIC_CHECK(Interval{2, 6}.overlaps(Interval{1, 3}));
        STATIC_CHECK(Interval{1, 3}.overlaps(Interval{2, 6}));
    }
}

TEST_CASE("[Interval] contains() method", "[utils][Interval]")
{
    Interval const interval1{2, 7};

    SECTION("Left extreme value") { CHECK(interval1.contains(2)); }
    SECTION("Intermediate value") { CHECK(interval1.contains(5)); }
    SECTION("Right extreme value") { CHECK(interval1.contains(7)); }
    SECTION("Outside on the right side")
    {
        CHECK_FALSE(interval1.contains(21));
    }
    SECTION("Outside on the left side") { CHECK_FALSE(interval1.contains(-2)); }
    SECTION("Static tests") { STATIC_CHECK(Interval{2, 7}.contains(2)); }
}

TEST_CASE("[Interval] hasOneValue() method", "[utils][Interval]")
{
    SECTION("False")
    {
        Interval const interval1{2, 7};
        CHECK_FALSE(interval1.hasOneValue());
    }
    SECTION("True")
    {
        Interval const interval1{3, 3};
        CHECK(interval1.hasOneValue());
    }
    SECTION("Static tests")
    {
        STATIC_CHECK_FALSE(Interval{2, 7}.hasOneValue());
        STATIC_CHECK(Interval{3, 3}.hasOneValue());
    }
}

TEST_CASE("[Interval] areContiguous() method", "[utils][Interval]")
{
    SECTION("Contiguous on the left side")
    {
        Interval const interval1{2, 7};
        Interval const interval2{-1, 1};
        CHECK(interval1.areContiguous(interval2));
        CHECK(interval2.areContiguous(interval1));
    }
    SECTION("Contiguous on the right side")
    {
        Interval const interval1{2, 7};
        Interval const interval2{8, 9};
        CHECK(interval1.areContiguous(interval2));
        CHECK(interval2.areContiguous(interval1));
    }
    SECTION("One interval includes the other one totally")
    {
        Interval const interval1{2, 7};
        Interval const interval2{3, 3};
        CHECK_FALSE(interval1.areContiguous(interval2));
        CHECK_FALSE(interval2.areContiguous(interval1));
    }
    SECTION("Static tests")
    {
        STATIC_CHECK(Interval{2, 7}.areContiguous(Interval{-1, 1}));
    }
}

TEST_CASE("[Interval] Comparison operators", "[utils][Interval]")
{
    SECTION("Equality")
    {
        CHECK(Interval{1, 3} == Interval{1, 3});
        CHECK_FALSE(Interval{1, 3} == Interval{1, 5});
        CHECK_FALSE(Interval{1, 3} == Interval{2, 3});
    }
    SECTION("Inequality")
    {
        CHECK_FALSE(Interval{1, 3} != Interval{1, 3});
        CHECK(Interval{1, 3} != Interval{1, 5});
        CHECK(Interval{1, 3} != Interval{2, 3});
    }
    SECTION("Greater and less than")
    {
        CHECK_FALSE(Interval{1, 3} > Interval{1, 3});
        CHECK(Interval{1, 3} < Interval{1, 5});
        CHECK(Interval{1, 3} < Interval{2, 3});
        CHECK(Interval{1, 5} > Interval{1, 3});
        CHECK(Interval{1, 5} < Interval{2, 3});
    }
    SECTION("Static tests")
    {
        SECTION("Equality")
        {
            STATIC_CHECK(Interval{2, 7} == Interval{2, 7});
            STATIC_CHECK_FALSE(Interval{2, 7} == Interval{1, 5});
        }
        SECTION("Inequality")
        {
            STATIC_CHECK_FALSE(Interval{2, 7} != Interval{2, 7});
            STATIC_CHECK(Interval{2, 7} != Interval{1, 5});
        }
    }
}

TEST_CASE("[Interval] where() method", "[utils][Interval]")
{
    Interval const interval1{2, 7};
    SECTION("Outside left") { CHECK(interval1.where(-4) == Location::Less); }
    SECTION("Outside right")
    {
        CHECK(interval1.where(10) == Location::Greater);
    }
    SECTION("Within") { CHECK(interval1.where(3) == Location::Within); }
    SECTION("Static tests")
    {
        SECTION("Outside left")
        {
            STATIC_CHECK(interval1.where(-4) == Location::Less);
        }
        SECTION("Outside right")
        {
            STATIC_CHECK(interval1.where(10) == Location::Greater);
        }
        SECTION("Within")
        {
            STATIC_CHECK(interval1.where(3) == Location::Within);
        }
    }
}

TEST_CASE("[Interval] move() method", "[utils][Interval]")
{
    Interval const interval1{2, 7};
    SECTION("Positive movement")
    {
        auto const interval2{interval1.move(2)};
        CHECK(interval2.get() == std::make_pair(4, 9));
    }
    SECTION("Negative movement")
    {
        auto const interval2{interval1.move(-3)};
        CHECK(interval2.get() == std::make_pair(-1, 4));
    }
    SECTION("Zero movement")
    {
        auto const interval2{interval1.move(0)};
        CHECK(interval2.get() == std::make_pair(2, 7));
    }
}

TEST_CASE("[Interval] expand() method", "[utils][Interval]")
{
    constexpr Interval interval1{2, 7};
    SECTION("Equal offset")
    {
        auto const interval2{interval1.expand(2)};
        CHECK(interval2.get() == std::make_pair(0, 9));
    }
    SECTION("Different offset")
    {
        auto const interval2{interval1.expand(2, 3)};
        CHECK(interval2.get() == std::make_pair(0, 10));
    }
    SECTION("Zero offset")
    {
        auto const interval2{interval1.expand(0)};
        CHECK(interval2.get() == std::make_pair(2, 7));
    }
}

TEST_CASE("[Interval] getRelativePosition() method", "[utils][Interval]")
{
    constexpr Interval interval1{2, 7};
    SECTION("Runtime tests")
    {
        SECTION("Outside left")
        {
            CHECK(interval1.getRelativePosition(Boundary::Start, -4) == -6);
            CHECK(interval1.getRelativePosition(Boundary::End, -4) == -11);
        }
        SECTION("Outside right")
        {
            CHECK(interval1.getRelativePosition(Boundary::Start, 10) == 8);
            CHECK(interval1.getRelativePosition(Boundary::End, 10) == 3);
        }
        SECTION("Within")
        {
            CHECK(interval1.getRelativePosition(Boundary::Start, 3) == 1);
            CHECK(interval1.getRelativePosition(Boundary::End, 3) == -4);
        }
    }
    SECTION("Static tests")
    {
        SECTION("Outside left")
        {
            STATIC_CHECK(
                interval1.getRelativePosition(Boundary::Start, -4) == -6);
            STATIC_CHECK(
                interval1.getRelativePosition(Boundary::End, -4) == -11);
        }
        SECTION("Outside right")
        {
            STATIC_CHECK(
                interval1.getRelativePosition(Boundary::Start, 10) == 8);
            STATIC_CHECK(interval1.getRelativePosition(Boundary::End, 10) == 3);
        }
        SECTION("Within")
        {
            STATIC_CHECK(
                interval1.getRelativePosition(Boundary::Start, 3) == 1);
            STATIC_CHECK(interval1.getRelativePosition(Boundary::End, 3) == -4);
        }
    }
}

TEST_CASE("[Interval] createWithBounds() method", "[utils][Interval]")
{
    SECTION("Runtime tests")
    {
        auto const interval1{Interval<int>::createWithBounds(2, 3)};
        CHECK(interval1.getMin() == 2);
        CHECK(interval1.getMax() == 3);
        CHECK(interval1.get() == std::make_pair(2, 3));
    }
    SECTION("Static tests")
    {
        constexpr auto interval1{Interval<int>::createWithBounds(2, 3)};
        STATIC_CHECK(interval1.getMin() == 2);
        STATIC_CHECK(interval1.getMax() == 3);
        STATIC_CHECK(interval1.get() == std::make_pair(2, 3));
    }
}

TEST_CASE("[Interval] createWithLength() method", "[utils][Interval]")
{
    SECTION("Runtime tests")
    {
        auto const interval1{Interval<int>::createWithLength(2, 3)};
        CHECK(interval1.getMin() == 2);
        CHECK(interval1.getMax() == 5);
        CHECK(interval1.get() == std::make_pair(2, 5));
    }
    SECTION("Static tests")
    {
        constexpr auto interval1{Interval<int>::createWithLength(2, 3)};
        STATIC_CHECK(interval1.getMin() == 2);
        STATIC_CHECK(interval1.getMax() == 5);
        STATIC_CHECK(interval1.get() == std::make_pair(2, 5));
    }
}

TEST_CASE("[Interval] createWhole() method", "[utils][Interval]")
{
    SECTION("Runtime tests")
    {
        auto const interval1{Interval<int>::createWhole()};
        CHECK(interval1.getMin() == std::numeric_limits<int>::min());
        CHECK(interval1.getMax() == std::numeric_limits<int>::max());
        CHECK(
            interval1.get()
            == std::make_pair(
                std::numeric_limits<int>::min(),
                std::numeric_limits<int>::max()));
    }
    SECTION("Static tests")
    {
        constexpr auto interval1{Interval<int>::createWhole()};
        STATIC_CHECK(interval1.getMin() == std::numeric_limits<int>::min());
        STATIC_CHECK(interval1.getMax() == std::numeric_limits<int>::max());
        STATIC_CHECK(
            interval1.get()
            == std::make_pair(
                std::numeric_limits<int>::min(),
                std::numeric_limits<int>::max()));
    }
}

TEST_CASE("[Interval] toString() method", "[utils][Interval]")
{
    constexpr Interval interval1{2, 7};
    CHECK(interval1.toString() == "[2,7]");
}

TEST_CASE("[Interval] Output stream operator", "[utils][Interval]")
{
    std::stringstream buffer;
    // Redirect std::cout to buffer
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    Interval const interval1{2, 7};
    std::cout << interval1.toString();

    // Use the string value of buffer to compare against expected output
    std::string text = buffer.str();

    // Restore original buffer before exiting
    std::cout.rdbuf(prevcoutbuf);

    CHECK(text == "[2,7]");
}
