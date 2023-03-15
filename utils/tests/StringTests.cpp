#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/String.hpp>

TEST_CASE(
    "[String - toNumber] Works OK with all integer types",
    "[String, String_toNumber]")
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

TEST_CASE("[String - split] Works OK", "[String, String_split]")
{
    const auto result1{ utils::string::split("12,3", ",") };
    CHECK(result1[0] == "12");
    CHECK(result1[1] == "3");
    const auto result2{ utils::string::split("-12..aa", "..") };
    CHECK(result2[0] == "-12");
    CHECK(result2[1] == "aa");
}
