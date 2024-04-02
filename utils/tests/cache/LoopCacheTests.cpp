#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/cache/LoopCache.hpp>

using namespace utils::cache;

struct Item {
    int32_t value;

    bool operator==(Item const& other) const noexcept
    {
        return value == other.value;
    }
};

template <>
struct std::hash<Item> {
    std::size_t operator()(Item const& k) const noexcept
    {
        return std::hash<int32_t>()(k.value);
    }
};

TEST_CASE("[LoopCache] run() method", "[utils][LoopCache]")
{
    Item item{0};
    LoopCache::run<Item>(item, 1000ULL, [](Item& item) -> void {
        ++item.value;
        if (item.value > 7) {
            item.value = 0;
        }
    });
    CHECK(item.value == 0);
}
