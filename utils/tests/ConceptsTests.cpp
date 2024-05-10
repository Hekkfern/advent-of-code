#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/Concepts.hpp>

TEST_CASE("[Concepts] NumericType", "[utils][Concepts]")
{
    STATIC_CHECK(not NumericType<std::string>);
    STATIC_CHECK(not NumericType<bool>);
    STATIC_CHECK(not NumericType<std::vector<int>>);
    STATIC_CHECK(not NumericType<int8_t*>);
    STATIC_CHECK(not NumericType<char*>);
    STATIC_CHECK(not NumericType<std::byte>);
    STATIC_CHECK(not NumericType<std::unique_ptr<int32_t>>);
    STATIC_CHECK(NumericType<char>);
    STATIC_CHECK(NumericType<int8_t>);
    STATIC_CHECK(NumericType<int32_t>);
    STATIC_CHECK(NumericType<int64_t>);
    STATIC_CHECK(NumericType<uint8_t>);
    STATIC_CHECK(NumericType<uint32_t>);
    STATIC_CHECK(NumericType<uint64_t>);
    STATIC_CHECK(NumericType<std::size_t>);
    STATIC_CHECK(NumericType<float_t>);
    STATIC_CHECK(NumericType<double_t>);
}

TEST_CASE("[Concepts] IntegerType", "[utils][Concepts]")
{
    STATIC_CHECK(not IntegerType<std::string>);
    STATIC_CHECK(not IntegerType<bool>);
    STATIC_CHECK(not IntegerType<std::vector<int>>);
    STATIC_CHECK(not IntegerType<int8_t*>);
    STATIC_CHECK(not IntegerType<char*>);
    STATIC_CHECK(not IntegerType<std::byte>);
    STATIC_CHECK(not IntegerType<std::unique_ptr<int32_t>>);
    STATIC_CHECK(IntegerType<char>);
    STATIC_CHECK(IntegerType<int8_t>);
    STATIC_CHECK(IntegerType<int32_t>);
    STATIC_CHECK(IntegerType<int64_t>);
    STATIC_CHECK(IntegerType<uint8_t>);
    STATIC_CHECK(IntegerType<uint32_t>);
    STATIC_CHECK(IntegerType<uint64_t>);
    STATIC_CHECK(IntegerType<std::size_t>);
    STATIC_CHECK(not IntegerType<float_t>);
    STATIC_CHECK(not IntegerType<double_t>);
}

TEST_CASE("[Concepts] UnsignedIntegerType", "[utils][Concepts]")
{
    STATIC_CHECK(not UnsignedIntegerType<std::string>);
    STATIC_CHECK(not UnsignedIntegerType<bool>);
    STATIC_CHECK(not UnsignedIntegerType<std::vector<int>>);
    STATIC_CHECK(not UnsignedIntegerType<int8_t*>);
    STATIC_CHECK(not UnsignedIntegerType<char*>);
    STATIC_CHECK(not UnsignedIntegerType<std::byte>);
    STATIC_CHECK(not UnsignedIntegerType<std::unique_ptr<int32_t>>);
    STATIC_CHECK(not UnsignedIntegerType<char>);
    STATIC_CHECK(not UnsignedIntegerType<int8_t>);
    STATIC_CHECK(not UnsignedIntegerType<int32_t>);
    STATIC_CHECK(not UnsignedIntegerType<int64_t>);
    STATIC_CHECK(UnsignedIntegerType<uint8_t>);
    STATIC_CHECK(UnsignedIntegerType<uint32_t>);
    STATIC_CHECK(UnsignedIntegerType<uint64_t>);
    STATIC_CHECK(UnsignedIntegerType<std::size_t>);
    STATIC_CHECK(not UnsignedIntegerType<float_t>);
    STATIC_CHECK(not UnsignedIntegerType<double_t>);
}

TEST_CASE("[Concepts] SignedIntegerType", "[utils][Concepts]")
{
    STATIC_CHECK(not SignedIntegerType<std::string>);
    STATIC_CHECK(not SignedIntegerType<bool>);
    STATIC_CHECK(not SignedIntegerType<std::vector<int>>);
    STATIC_CHECK(not SignedIntegerType<int8_t*>);
    STATIC_CHECK(not SignedIntegerType<char*>);
    STATIC_CHECK(not SignedIntegerType<std::byte>);
    STATIC_CHECK(not SignedIntegerType<std::unique_ptr<int32_t>>);
    STATIC_CHECK(SignedIntegerType<char>);
    STATIC_CHECK(SignedIntegerType<int8_t>);
    STATIC_CHECK(SignedIntegerType<int32_t>);
    STATIC_CHECK(SignedIntegerType<int64_t>);
    STATIC_CHECK(not SignedIntegerType<uint8_t>);
    STATIC_CHECK(not SignedIntegerType<uint32_t>);
    STATIC_CHECK(not SignedIntegerType<uint64_t>);
    STATIC_CHECK(not SignedIntegerType<std::size_t>);
    STATIC_CHECK(not SignedIntegerType<float_t>);
    STATIC_CHECK(not SignedIntegerType<double_t>);
}
