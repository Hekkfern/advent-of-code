#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/Concepts.hpp>

TEST_CASE("[Concepts] NumericType", "[utils][Concepts]")
{
    STATIC_CHECK(not NumericType<std::string>);
    STATIC_CHECK(not NumericType<bool>);
    STATIC_CHECK(not NumericType<std::vector<int>>);
    STATIC_CHECK(NumericType<int8_t>);
    STATIC_CHECK(NumericType<int32_t>);
    STATIC_CHECK(NumericType<int64_t>);
    STATIC_CHECK(NumericType<uint8_t>);
    STATIC_CHECK(NumericType<uint32_t>);
    STATIC_CHECK(NumericType<uint64_t>);
    STATIC_CHECK(NumericType<float_t>);
    STATIC_CHECK(NumericType<double_t>);
}
