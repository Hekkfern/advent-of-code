#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/CircularList.hpp>

using namespace utils::containers;

TEST_CASE("[CircularList] Constructors", "[utils][CircularList]")
{
    SECTION("Default constructor")
    {
        CircularList const circularList;
        REQUIRE(circularList.size() == 0U);
        REQUIRE(circularList.empty());
    }
    SECTION("Parametrized constructor")
    {
        SECTION("Copying a list")
        {
            std::list<int32_t> list{123};
            CircularList<int32_t> const circularList{list};
            REQUIRE(circularList.size() == 1U);
            REQUIRE_FALSE(circularList.empty());
        }
        SECTION("Moving a list")
        {
            CircularList<int32_t> const circularList{{123}};
            REQUIRE(circularList.size() == 1U);
            REQUIRE_FALSE(circularList.empty());
        }
    }
}

TEST_CASE("[CircularList] pushFront() method", "[utils][CircularList]")
{
    CircularList<int32_t> circularList{{123}};
    circularList.pushFront(234);
    REQUIRE(circularList.size() == 2U);
    REQUIRE(circularList.front() == 234);
    REQUIRE(circularList.back() == 123);
}

TEST_CASE("[CircularList] pushBack() method", "[utils][CircularList]")
{
    CircularList<int32_t> circularList{{123}};
    circularList.pushBack(234);
    REQUIRE(circularList.size() == 2U);
    REQUIRE(circularList.front() == 123);
    REQUIRE(circularList.back() == 234);
}

TEST_CASE("[CircularList] popFront() method", "[utils][CircularList]")
{
    CircularList<int32_t> circularList{{123, 234}};
    circularList.popFront();
    REQUIRE(circularList.size() == 1U);
    REQUIRE(circularList.front() == 234);
    REQUIRE(circularList.back() == 234);
}

TEST_CASE("[CircularList] popBack() method", "[utils][CircularList]")
{
    CircularList<int32_t> circularList{{123, 234}};
    circularList.popBack();
    REQUIRE(circularList.size() == 1U);
    REQUIRE(circularList.front() == 123);
    REQUIRE(circularList.back() == 123);
}

TEST_CASE("[CircularList] insert() method", "[utils][CircularList]")
{
    CircularList<int32_t> circularList{{123, 234}};
    constexpr int newValue{20};
    SECTION("At the beginning")
    {
        circularList.insert(circularList.begin(), newValue);
        REQUIRE(circularList.size() == 3U);
        REQUIRE(circularList.front() == newValue);
    }
    SECTION("At the end")
    {
        auto it{circularList.end()};
        circularList.insert(it, newValue);
        REQUIRE(circularList.size() == 3U);
        REQUIRE(circularList.back() == newValue);
    }
    SECTION("In the middle")
    {
        auto it{circularList.begin()};
        std::advance(it, 1);
        circularList.insert(it, newValue);
        REQUIRE(circularList.size() == 3U);
        REQUIRE(circularList.front() == 123);
        REQUIRE(circularList.back() == 234);
    }
}

TEST_CASE("[CircularList] erase() method", "[utils][CircularList]")
{
    CircularList<int32_t> circularList{{123, 234, 345}};
    SECTION("At the beginning")
    {
        circularList.erase(circularList.begin());
        REQUIRE(circularList.size() == 2U);
        REQUIRE(circularList.front() == 234);
    }
    SECTION("At the end")
    {
        auto it{circularList.end()};
        std::advance(it, -1);
        circularList.erase(it);
        REQUIRE(circularList.size() == 2U);
        REQUIRE(circularList.back() == 234);
    }
    SECTION("In the middle")
    {
        auto it{circularList.begin()};
        std::advance(it, 1);
        circularList.erase(it);
        REQUIRE(circularList.size() == 2U);
        REQUIRE(circularList.front() == 123);
        REQUIRE(circularList.back() == 345);
    }
}

TEST_CASE("[CircularList] swap() method", "[utils][CircularList]")
{
    CircularList<int32_t> circularList{{123, 234, 345}};
    bool result{circularList.swap(0U, 2U)};
    REQUIRE(result);
    REQUIRE(circularList.front() == 345);
    REQUIRE(circularList.back() == 123);
}

TEST_CASE("[CircularList] clear() method", "[utils][CircularList]")
{
    CircularList<int32_t> circularList{{123, 234, 345}};
    circularList.clear();
    REQUIRE(circularList.empty());
}

TEST_CASE("[CircularList] move() method", "[utils][CircularList]")
{
    CircularList<int32_t> circularList{{1, 2, 3, 4, 5, 6}};
    SECTION("In the middle")
    {
        circularList.move(1U, 3U);
        REQUIRE(circularList.size() == 6U);
        CircularList<int32_t> const expectedCircularList{{1, 3, 4, 2, 5, 6}};
        REQUIRE(circularList == expectedCircularList);
    }
    SECTION("Wrap-around")
    {
        circularList.move(4U, 1U);
        REQUIRE(circularList.size() == 6U);
        CircularList<int32_t> const expectedCircularList{{1, 5, 2, 3, 4, 6}};
        REQUIRE(circularList == expectedCircularList);
    }
    SECTION("Border positions (1/2)")
    {
        circularList.move(0U, circularList.size() - 1U);
        REQUIRE(circularList.size() == 6U);
        CircularList<int32_t> const expectedCircularList{{2, 3, 4, 5, 6, 1}};
        REQUIRE(circularList == expectedCircularList);
    }
    SECTION("Border positions (2/2)")
    {
        circularList.move(circularList.size() - 1U, 0U);
        REQUIRE(circularList.size() == 6U);
        CircularList<int32_t> const expectedCircularList{{6, 1, 2, 3, 4, 5}};
        REQUIRE(circularList == expectedCircularList);
    }
}

TEST_CASE("[CircularList] rotateLeft() method", "[utils][CircularList]")
{
    CircularList<int32_t> circularList{{1, 2, 3, 4, 5, 6}};
    SECTION("In the middle")
    {
        circularList.rotateLeft(2U);
        REQUIRE(circularList.size() == 6U);
        CircularList<int32_t> const expectedCircularList{{3, 4, 5, 6, 1, 2}};
        REQUIRE(circularList == expectedCircularList);
    }
}

TEST_CASE("[CircularList] rotateRight() method", "[utils][CircularList]")
{
    CircularList<int32_t> circularList{{1, 2, 3, 4, 5, 6}};
    SECTION("In the middle")
    {
        circularList.rotateRight(2U);
        REQUIRE(circularList.size() == 6U);
        CircularList<int32_t> const expectedCircularList{{5, 6, 1, 2, 3, 4}};
        REQUIRE(circularList == expectedCircularList);
    }
}
