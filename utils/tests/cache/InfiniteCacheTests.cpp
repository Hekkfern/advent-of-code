#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/cache/InfiniteCache.hpp>

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

TEST_CASE("[InfiniteCache] Constructor", "[utils][InfiniteCache]")
{
    SECTION("Numbers")
    {
        InfiniteCache<int, int> cache;
        CHECK(cache.size() == 0);
    }
    SECTION("Strings")
    {
        InfiniteCache<std::string, std::string> cache;
        CHECK(cache.size() == 0);
    }
    SECTION("Custom struct")
    {
        InfiniteCache<CustomStruct, CustomStruct2> cache;
        CHECK(cache.size() == 0);
    }
}

TEST_CASE("[InfiniteCache] get() / put() methods", "[utils][InfiniteCache]")
{
    SECTION("Numbers")
    {
        InfiniteCache<int, int> cache;
        CHECK(cache.size() == 0ULL);
        CHECK_FALSE(cache.get(6));
        cache.put(6, 1000);
        CHECK(cache.get(6) == 1000);
        CHECK(cache.size() == 1ULL);
    }
    SECTION("Strings")
    {
        InfiniteCache<std::string, std::string> cache;
        CHECK(cache.size() == 0ULL);
        CHECK_FALSE(cache.get("aa"));
        cache.put("aa", "bbb");
        CHECK(cache.get("aa") == "bbb");
        CHECK(cache.size() == 1ULL);
    }
    SECTION("Custom struct")
    {
        InfiniteCache<CustomStruct, CustomStruct2> cache;
        CustomStruct s1{2};
        CHECK(cache.size() == 0ULL);
        CHECK_FALSE(cache.get(s1));
        cache.put(s1, CustomStruct2{1000});
        CHECK(cache.get(s1) == CustomStruct2{1000});
        CHECK(cache.size() == 1ULL);
    }
}

TEST_CASE("[InfiniteCache] Overwrite item", "[utils][InfiniteCache]")
{
    InfiniteCache<int, int> cache;
    CHECK(cache.size() == 0ULL);
    // add new item
    cache.put(6, 1000);
    CHECK(cache.get(6) == 1000);
    CHECK(cache.size() == 1ULL);
    // overwrite
    cache.put(6, 2000);
    CHECK(cache.get(6) == 2000);
    CHECK(cache.size() == 1ULL);
}

TEST_CASE("[InfiniteCache] exists() methods", "[utils][InfiniteCache]")
{
    SECTION("Numbers")
    {
        InfiniteCache<int, int> cache;
        CHECK_FALSE(cache.exists(6));
        cache.put(6, 1000);
        CHECK(cache.exists(6));
    }
    SECTION("Strings")
    {
        InfiniteCache<std::string, std::string> cache;
        CHECK_FALSE(cache.exists("aa"));
        cache.put("aa", "bbb");
        CHECK(cache.exists("aa"));
    }
    SECTION("Custom struct")
    {
        InfiniteCache<CustomStruct, CustomStruct2> cache;
        CustomStruct s1{2};
        CHECK_FALSE(cache.exists(s1));
        cache.put(s1, CustomStruct2{1000});
        CHECK(cache.exists(s1));
    }
}

TEST_CASE("[InfiniteCache] erase() methods", "[utils][InfiniteCache]")
{
    SECTION("Numbers")
    {
        InfiniteCache<int, int> cache;
        CHECK(cache.size() == 0ULL);
        cache.put(6, 1000);
        CHECK(cache.size() == 1ULL);
        cache.erase(6);
        CHECK(cache.size() == 0ULL);
    }
    SECTION("Strings")
    {
        InfiniteCache<std::string, std::string> cache;
        CHECK(cache.size() == 0ULL);
        cache.put("aa", "bbb");
        CHECK(cache.size() == 1ULL);
        cache.erase("aa");
        CHECK(cache.size() == 0ULL);
    }
    SECTION("Custom struct")
    {
        InfiniteCache<CustomStruct, CustomStruct2> cache;
        CustomStruct s1{2};
        CHECK(cache.size() == 0ULL);
        cache.put(s1, CustomStruct2{1000});
        CHECK(cache.size() == 1ULL);
        cache.erase(s1);
        CHECK(cache.size() == 0ULL);
    }
}

TEST_CASE("[InfiniteCache] clear() methods", "[utils][InfiniteCache]")
{
    SECTION("Numbers")
    {
        InfiniteCache<int, int> cache;
        CHECK(cache.size() == 0ULL);
        cache.put(6, 1000);
        CHECK(cache.size() == 1ULL);
        cache.clear();
        CHECK(cache.size() == 0ULL);
    }
    SECTION("Strings")
    {
        InfiniteCache<std::string, std::string> cache;
        CHECK(cache.size() == 0ULL);
        cache.put("aa", "bbb");
        CHECK(cache.size() == 1ULL);
        cache.clear();
        CHECK(cache.size() == 0ULL);
    }
    SECTION("Custom struct")
    {
        InfiniteCache<CustomStruct, CustomStruct2> cache;
        CustomStruct s1{2};
        CHECK(cache.size() == 0ULL);
        cache.put(s1, CustomStruct2{1000});
        CHECK(cache.size() == 1ULL);
        cache.clear();
        CHECK(cache.size() == 0ULL);
    }
}
