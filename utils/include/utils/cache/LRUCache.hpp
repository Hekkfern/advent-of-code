#pragma once

#include <optional>
#include <unordered_map>

namespace utils::cache {

template <typename Key, typename Value, std::size_t N>
class LRUCache {
public:
    LRUCache() = default;

    [[nodiscard]] std::optional<Value> get(Key const& key) const
    {
        // TODO
    }

    void put(Key const&, Value const& value)
    {
        // TODO
    }

    void erase(Key const& key)
    {
        // TODO
    }

    [[nodiscard]] static std::size_t size() { return N; }

private:
    std::unordered_map<Key, Value> mNodes;
};

} // namespace utils::cache
