#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/cache/LRUCache.hpp>

using namespace utils::cache;

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
        struct CustomStruct1 {
            int a;
        };
        struct CustomStruct2 {
            int b;
        };
        LRUCache<CustomStruct1, CustomStruct2> cache{10};
        CHECK(cache.maxSize() == 10);
    }
}
