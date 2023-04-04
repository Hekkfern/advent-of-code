#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/String.hpp>

TEST_CASE("[String] toNumber method", "[utils][String]")
{
    CHECK(utils::string::toNumber<uint8_t>("6") == 6U);
    CHECK(utils::string::toNumber<uint32_t>("6") == 6U);
    CHECK(utils::string::toNumber<uint64_t>("6") == 6ULL);
    CHECK(utils::string::toNumber<int8_t>("6") == 6);
    CHECK(utils::string::toNumber<int8_t>("-4") == -4);
    CHECK(utils::string::toNumber<int32_t>("6") == 6);
    CHECK(utils::string::toNumber<int32_t>("-4") == -4);
    CHECK(utils::string::toNumber<int64_t>("6") == 6LL);
    CHECK(utils::string::toNumber<int64_t>("-4") == -4LL);
}

TEST_CASE("[String] split method", "[utils][String]")
{
    SECTION("Comma-separated number")
    {
        const auto result1{utils::string::split("12,3", ",")};
        CHECK(result1[0] == "12");
        CHECK(result1[1] == "3");
    }
    SECTION("Numbers and text")
    {
        const auto result2{utils::string::split("-12..aa", "..")};
        CHECK(result2[0] == "-12");
        CHECK(result2[1] == "aa");
    }
}
