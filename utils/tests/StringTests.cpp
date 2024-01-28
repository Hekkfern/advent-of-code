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
        auto const result{utils::string::split("12,3", ",")};
        CHECK(result[0] == "12");
        CHECK(result[1] == "3");
    }
    SECTION("Numbers and text")
    {
        auto const result{utils::string::split("-12..aa", "..")};
        CHECK(result[0] == "-12");
        CHECK(result[1] == "aa");
    }
}

TEST_CASE("[String] join method", "[utils][String]")
{
    SECTION("Comma-separated number")
    {
        auto const result{utils::string::join({"12", "3"}, ",")};
        CHECK(result == "12,3");
    }
    SECTION("Numbers and text")
    {
        auto const result{utils::string::join({"-12", "aa"}, "..")};
        CHECK(result == "-12..aa");
    }
}

TEST_CASE("[String] contains method", "[utils][String]")
{
    CHECK(utils::string::contains("helloworld13518", "world"));
    CHECK(utils::string::contains("helloworldworld13518", "world"));
    CHECK(utils::string::contains("helloworldworl13518", "1"));
    CHECK_FALSE(utils::string::contains("helloworld13518", "."));
}

TEST_CASE("[String] ltrim method", "[utils][String]")
{
    CHECK(utils::string::ltrim("helloworld13518") == "helloworld13518");
    CHECK(utils::string::ltrim("  helloworld13518") == "helloworld13518");
    CHECK(utils::string::ltrim("  helloworld13518  ") == "helloworld13518  ");
    CHECK(utils::string::ltrim("helloworl d13518") == "helloworl d13518");
    CHECK(utils::string::ltrim("    ") == "");
}

TEST_CASE("[String] rtrim method", "[utils][String]")
{
    CHECK(utils::string::rtrim("helloworld13518") == "helloworld13518");
    CHECK(utils::string::rtrim("helloworld13518  ") == "helloworld13518");
    CHECK(utils::string::rtrim("  helloworld13518  ") == "  helloworld13518");
    CHECK(utils::string::rtrim("helloworl d13518") == "helloworl d13518");
    CHECK(utils::string::ltrim("    ") == "");
}

TEST_CASE("[String] trim method", "[utils][String]")
{
    CHECK(utils::string::trim("helloworld13518") == "helloworld13518");
    CHECK(utils::string::trim("  helloworld13518") == "helloworld13518");
    CHECK(utils::string::trim("helloworld13518  ") == "helloworld13518");
    CHECK(utils::string::trim("  helloworld13518  ") == "helloworld13518");
    CHECK(utils::string::trim("helloworl d13518") == "helloworl d13518");
    CHECK(utils::string::ltrim("    ") == "");
}

TEST_CASE("[String] remove_excess_whitespace method", "[utils][String]")
{
    std::string const text{
        "   Hello Geeks . Welcome   to  GeeksforGeeks   .    "};
    CHECK(
        utils::string::remove_excess_whitespace(text)
        == " Hello Geeks . Welcome to GeeksforGeeks .");
}
