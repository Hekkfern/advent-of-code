#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/String.hpp>

TEST_CASE(
    "[StringUtils - toNumber] Works OK with all integer types",
    "[StringUtils, StringUtils_toNumber]")
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
