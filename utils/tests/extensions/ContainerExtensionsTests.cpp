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
    static std::vector<int32_t> const Input{1, 2, 3, 4, 5, 6, 7};
    auto result{Input};

    SECTION("Initial position")
    {
        static constexpr std::size_t Position{0ULL};

        SECTION("Positive offset")
        {
            static std::vector<int32_t> const ExpectedResult{
                2, 3, 4, 1, 5, 6, 7};

            SECTION("Smaller than size")
            {
                utils::extensions::moveValueCircularly(result, Position, 3);
                CHECK(result == ExpectedResult);
            }
            SECTION("Greater than size")
            {
                utils::extensions::moveValueCircularly(result, Position, 10);
                CHECK(result == ExpectedResult);
            }
        }
        SECTION("Zero offset")
        {
            utils::extensions::moveValueCircularly(result, Position, 0);
            CHECK(result == Input);
        }
        SECTION("Negative offset")
        {
            static std::vector<int32_t> const ExpectedResult{
                2, 3, 4, 1, 5, 6, 7};

            SECTION("Smaller than size")
            {
                utils::extensions::moveValueCircularly(result, Position, -3);
                CHECK(result == ExpectedResult);
            }
            SECTION("Greater than size")
            {
                utils::extensions::moveValueCircularly(result, Position, -10);
                CHECK(result == ExpectedResult);
            }
        }
    }
    SECTION("Middle position")
    {
        static constexpr std::size_t Position{2ULL};

        SECTION("Positive offset")
        {
            static std::vector<int32_t> const ExpectedResult{
                1, 2, 4, 5, 6, 3, 7};

            SECTION("Smaller than size")
            {
                utils::extensions::moveValueCircularly(result, Position, 3);
                CHECK(result == ExpectedResult);
            }
            SECTION("Greater than size")
            {
                utils::extensions::moveValueCircularly(result, Position, 10);
                CHECK(result == ExpectedResult);
            }
        }
        SECTION("Zero offset")
        {
            utils::extensions::moveValueCircularly(result, Position, 0);
            CHECK(result == Input);
        }
        SECTION("Negative offset")
        {
            static std::vector<int32_t> const ExpectedResult{
                1, 2, 4, 5, 6, 3, 7};

            SECTION("Smaller than size")
            {
                utils::extensions::moveValueCircularly(result, Position, -3);
                CHECK(result == ExpectedResult);
            }
            SECTION("Greater than size")
            {
                utils::extensions::moveValueCircularly(result, Position, -10);
                CHECK(result == ExpectedResult);
            }
        }
    }
    SECTION("Final position")
    {
        static std::size_t const Position{Input.size() - 1ULL};

        SECTION("Positive offset")
        {
            static std::vector<int32_t> const ExpectedResult{
                1, 2, 3, 7, 4, 5, 6};

            SECTION("Smaller than size")
            {
                utils::extensions::moveValueCircularly(result, Position, 3);
                CHECK(result == ExpectedResult);
            }
            SECTION("Greater than size")
            {
                utils::extensions::moveValueCircularly(result, Position, 10);
                CHECK(result == ExpectedResult);
            }
        }
        SECTION("Zero offset")
        {
            utils::extensions::moveValueCircularly(result, Position, 0);
            CHECK(result == Input);
        }
        SECTION("Negative offset")
        {
            static std::vector<int32_t> const ExpectedResult{
                1, 2, 3, 7, 4, 5, 6};

            SECTION("Smaller than size")
            {
                utils::extensions::moveValueCircularly(result, Position, -3);
                CHECK(result == ExpectedResult);
            }
            SECTION("Greater than size")
            {
                utils::extensions::moveValueCircularly(result, Position, -10);
                CHECK(result == ExpectedResult);
            }
        }
    }

    CHECK(Input.size() == result.size());
}
