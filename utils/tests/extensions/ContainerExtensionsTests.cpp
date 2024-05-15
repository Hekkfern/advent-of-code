#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/extensions/ContainerExtensions.hpp>

TEST_CASE("[Extensions] rotate() function", "[utils][Extensions]")
{
    std::vector<int32_t> input{1, 2, 3, 4, 5, 6, 7};

    SECTION("Positive offset")
    {
        SECTION("Smaller than size")
        {
            utils::extensions::rotate(input, 3);
            CHECK(input == std::vector<int32_t>{5, 6, 7, 1, 2, 3, 4});
        }
        SECTION("Greater than size")
        {
            utils::extensions::rotate(input, 10);
            CHECK(input == std::vector<int32_t>{5, 6, 7, 1, 2, 3, 4});
        }
    }
    SECTION("Zero offset")
    {
        utils::extensions::rotate(input, 0);
        CHECK(input == std::vector<int32_t>{1, 2, 3, 4, 5, 6, 7});
    }
    SECTION("Negative offset")
    {
        SECTION("Smaller than size")
        {
            utils::extensions::rotate(input, -3);
            CHECK(input == std::vector<int32_t>{4, 5, 6, 7, 1, 2, 3});
        }
        SECTION("Greater than size")
        {
            utils::extensions::rotate(input, -10);
            CHECK(input == std::vector<int32_t>{4, 5, 6, 7, 1, 2, 3});
        }
    }
}

TEST_CASE("[Extensions] moveValueCircularly() function", "[utils][Extensions]")
{
    std::vector<int32_t> input{1, 2, 3, 4, 5, 6, 7};

    SECTION("Positive offset")
    {
        SECTION("Smaller than size")
        {
            utils::extensions::moveValueCircularly(input, 0ULL, 3);
            CHECK(input == std::vector<int32_t>{2, 3, 4, 1, 5, 6, 7});
        }
        SECTION("Greater than size")
        {
            utils::extensions::moveValueCircularly(input, 0ULL, 10);
            CHECK(input == std::vector<int32_t>{2, 3, 4, 1, 5, 6, 7});
        }
    }
    SECTION("Zero offset")
    {
        utils::extensions::moveValueCircularly(input, 0ULL, 0);
        CHECK(input == std::vector<int32_t>{1, 2, 3, 4, 5, 6, 7});
    }
    SECTION("Negative offset")
    {
        SECTION("Smaller than size")
        {
            utils::extensions::moveValueCircularly(input, 0ULL, -3);
            CHECK(input == std::vector<int32_t>{2, 3, 4, 1, 5, 6, 7});
        }
        SECTION("Greater than size")
        {
            utils::extensions::moveValueCircularly(input, 0ULL, -10);
            CHECK(input == std::vector<int32_t>{2, 3, 4, 1, 5, 6, 7});
        }
    }
}
