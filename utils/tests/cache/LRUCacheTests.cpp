#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/cache/LRUCache.hpp>

using namespace utils::cache;

struct CustomStruct {
    int a;
    bool operator==(CustomStruct const& other) const noexcept
    {
        return a == other.a;
    }
};
template <>
struct std::hash<CustomStruct> {
    inline std::size_t operator()(CustomStruct const& x) const
    {
        return std::hash<int>()(x.a);
    }
};

struct CustomStruct2 {
    int b;
    bool operator==(CustomStruct2 const& other) const noexcept
    {
        return b == other.b;
    }
};

TEST_CASE("[LRUCache] Constructor", "[utils][LRUCache]")
{
    SECTION("Numbers")
    {
        LRUCache<int, int> cache{10};
        CHECK(cache.maxSize() == 10);
    }
    SECTION("Strings")
    {
        LRUCache<std::string, std::string> cache{10};
        CHECK(cache.maxSize() == 10);
    }
    SECTION("Custom struct")
    {
        LRUCache<CustomStruct, CustomStruct2> cache{10};
        CHECK(cache.maxSize() == 10);
    }
}

TEST_CASE("[LRUCache] get() / put() methods", "[utils][LRUCache]")
{
    SECTION("Numbers")
    {
        LRUCache<int, int> cache{10};
        CHECK_FALSE(cache.get(6));
        cache.put(6, 1000);
        CHECK(cache.get(6) == 1000);
    }
    SECTION("Strings")
    {
        LRUCache<std::string, std::string> cache{10};
        CHECK_FALSE(cache.get("aa"));
        cache.put("aa", "bbb");
        CHECK(cache.get("aa") == "bbb");
    }
    SECTION("Custom struct")
    {
        LRUCache<CustomStruct, CustomStruct2> cache{10};
        CustomStruct s1{2};
        CHECK_FALSE(cache.get(s1));
        cache.put(s1, CustomStruct2{1000});
        CHECK(cache.get(s1) == CustomStruct2{1000});
    }
}
