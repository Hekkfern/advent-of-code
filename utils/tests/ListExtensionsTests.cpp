#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/ListExtensions.hpp>

using namespace utils::containers;

TEST_CASE("[ListExtensions] moveFromXToY() method", "[utils][ListExtensions]")
{
    std::list<int32_t> list{1, 2, 3, 4, 5, 6};
    SECTION("In the middle")
    {
        bool result{moveFromXToY(list, 1U, 3U)};
        REQUIRE(result);
        REQUIRE(list.size() == 6U);
        std::list<int32_t> const expectedCircularList{1, 3, 4, 2, 5, 6};
        REQUIRE(list == expectedCircularList);
    }
    SECTION("In the middle (reverse)")
    {
        bool result{moveFromXToY(list, 4U, 1U)};
        REQUIRE(result);
        REQUIRE(list.size() == 6U);
        std::list<int32_t> const expectedCircularList{1, 5, 2, 3, 4, 6};
        REQUIRE(list == expectedCircularList);
    }
    SECTION("Border positions")
    {
        bool result{moveFromXToY(list, 0U, list.size() - 1U)};
        REQUIRE(result);
        REQUIRE(list.size() == 6U);
        std::list<int32_t> const expectedCircularList{2, 3, 4, 5, 6, 1};
        REQUIRE(list == expectedCircularList);
    }
    SECTION("Border positions (reverse)")
    {
        bool result{moveFromXToY(list, list.size() - 1U, 0U)};
        REQUIRE(result);
        REQUIRE(list.size() == 6U);
        std::list<int32_t> const expectedCircularList{6, 1, 2, 3, 4, 5};
        REQUIRE(list == expectedCircularList);
    }
}

TEST_CASE(
    "[ListExtensions] circularMoveXPositions() method",
    "[utils][ListExtensions]")
{
    std::list<int32_t> list{1, 2, 3, 4, 5, 6};
    SECTION("In the middle")
    {
        bool result{circularMoveXPositions(list, 1U, 2)};
        REQUIRE(result);
        REQUIRE(list.size() == 6U);
        std::list<int32_t> const expectedCircularList{1, 3, 4, 2, 5, 6};
        REQUIRE(list == expectedCircularList);
    }
    SECTION("In the middle (reverse)")
    {
        bool result{false};
        SECTION("Negative number of positions")
        {
            result = circularMoveXPositions(list, 4U, -3);
        }
        SECTION("Positive number of positions")
        {
            result = circularMoveXPositions(list, 4U, 3U);
        }
        REQUIRE(result);
        REQUIRE(list.size() == 6U);
        std::list<int32_t> const expectedCircularList{1, 5, 2, 3, 4, 6};
        REQUIRE(list == expectedCircularList);
    }
    SECTION("Wrap-around in the left side")
    {
        bool result{circularMoveXPositions(list, 1U, -3)};
        REQUIRE(result);
        REQUIRE(list.size() == 6U);
        std::list<int32_t> const expectedCircularList{3, 4, 2, 5, 6, 1};
        REQUIRE(list == expectedCircularList);
    }
    SECTION("Wrap-around in the right side")
    {
        bool result{circularMoveXPositions(list, 1U, 7)};
        REQUIRE(result);
        REQUIRE(list.size() == 6U);
        std::list<int32_t> const expectedCircularList{1, 3, 2, 4, 5, 6};
        REQUIRE(list == expectedCircularList);
    }
}

TEST_CASE("[ListExtensions] rotateLeft() method", "[utils][ListExtensions]")
{
    SECTION("Success")
    {
        std::list<int32_t> list{1, 2, 3, 4, 5, 6};
        bool result{false};
        SECTION("Small amount") { result = circularRotateLeft(list, 2U); }
        SECTION("High amount") { result = circularRotateLeft(list, 8U); }
        REQUIRE(result);
        REQUIRE(list.size() == 6U);
        std::list<int32_t> const expectedCircularList{3, 4, 5, 6, 1, 2};
        REQUIRE(list == expectedCircularList);
    }
    SECTION("Error")
    {
        SECTION("Small list")
        {
            std::list<int32_t> list{1};
            bool result{circularRotateLeft(list, 2U)};
            REQUIRE_FALSE(result);
        }
        SECTION("Wrong amount")
        {
            std::list<int32_t> list{1, 2, 3, 4, 5, 6};
            bool result{false};
            SECTION("Zero positions") { result = circularRotateLeft(list, 0U); }
            SECTION("Wrap-around to zero")
            {
                result = circularRotateLeft(list, 6U);
            }
            REQUIRE_FALSE(result);
        }
    }
}

TEST_CASE("[ListExtensions] rotateRight() method", "[utils][ListExtensions]")
{
    SECTION("Success")
    {
        std::list<int32_t> list{1, 2, 3, 4, 5, 6};
        bool result{false};
        SECTION("Small amount") { result = circularRotateRight(list, 2U); }
        SECTION("High amount") { result = circularRotateRight(list, 8U); }
        REQUIRE(result);
        REQUIRE(list.size() == 6U);
        std::list<int32_t> const expectedCircularList{5, 6, 1, 2, 3, 4};
        REQUIRE(list == expectedCircularList);
    }
    SECTION("Error")
    {
        SECTION("Small list")
        {
            std::list<int32_t> list{1};
            bool result{circularRotateRight(list, 2U)};
            REQUIRE_FALSE(result);
        }
        SECTION("Wrong amount")
        {
            std::list<int32_t> list{1, 2, 3, 4, 5, 6};
            bool result{false};
            SECTION("Zero positions")
            {
                result = circularRotateRight(list, 0U);
            }
            SECTION("Wrap-around to zero")
            {
                result = circularRotateRight(list, 6U);
            }
            REQUIRE_FALSE(result);
        }
    }
}
