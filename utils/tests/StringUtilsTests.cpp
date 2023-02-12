#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/StringUtils.hpp>

TEST_CASE(
    "[StringUtils - toNumber] Works OK with all integer types",
    "[StringUtils, StringUtils_toNumber]")
{
    CHECK(utils::StringUtils::toNumber<uint8_t>("6") == 6U);
    CHECK(utils::StringUtils::toNumber<uint32_t>("6") == 6U);
    CHECK(utils::StringUtils::toNumber<uint64_t>("6") == 6ULL);
    CHECK(utils::StringUtils::toNumber<int8_t>("6") == 6);
    CHECK(utils::StringUtils::toNumber<int8_t>("-4") == -4);
    CHECK(utils::StringUtils::toNumber<int32_t>("6") == 6);
    CHECK(utils::StringUtils::toNumber<int32_t>("-4") == -4);
    CHECK(utils::StringUtils::toNumber<int64_t>("6") == 6LL);
    CHECK(utils::StringUtils::toNumber<int64_t>("-4") == -4LL);
}
