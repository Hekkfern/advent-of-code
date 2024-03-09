#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/cache/LRUCache.hpp>

using namespace utils::cache;

struct CustomStruct {
    int a;
};
template <>
struct std::hash<CustomStruct> {
    inline std::size_t operator()(CustomStruct const& x) const
    {
        return std::hash<int>()(x.a);
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
        struct CustomStruct2 {
            int b;
        };
        LRUCache<CustomStruct, CustomStruct2> cache{10};
        CHECK(cache.maxSize() == 10);
    }
}
