#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/String.hpp>

TEST_CASE("[String] toNumber method", "[utils][String]")
{
    auto value1{utils::string::toNumber<uint8_t>("6")};
    CHECK(value1);
    CHECK(*value1 == 6U);
    auto value2{utils::string::toNumber<uint32_t>("6")};
    CHECK(value2);
    CHECK(*value2 == 6U);
    auto value3{utils::string::toNumber<uint64_t>("6")};
    CHECK(value3);
    CHECK(*value3 == 6ULL);
    auto value4{utils::string::toNumber<int8_t>("6")};
    CHECK(value4);
    CHECK(*value4 == 6);
    auto value5{utils::string::toNumber<int8_t>("-4")};
    CHECK(value5);
    CHECK(*value5 == -4);
    auto value6{utils::string::toNumber<int32_t>("6")};
    CHECK(value6);
    CHECK(*value6 == 6);
    auto value7{utils::string::toNumber<int32_t>("-4")};
    CHECK(value7);
    CHECK(*value7 == -4);
    auto value8{utils::string::toNumber<int64_t>("6")};
    CHECK(value8);
    CHECK(*value8 == 6LL);
    auto value9{utils::string::toNumber<int64_t>("-4")};
    CHECK(value9);
    CHECK(*value9 == -4LL);
}

TEST_CASE("[String] split method", "[utils][String]")
{
    SECTION("Comma-separated number")
    {
        auto const result1{utils::string::split("12,3", ",")};
        CHECK(result1[0] == "12");
        CHECK(result1[1] == "3");
    }
    SECTION("Numbers and text")
    {
        auto const result2{utils::string::split("-12..aa", "..")};
        CHECK(result2[0] == "-12");
        CHECK(result2[1] == "aa");
    }
}
