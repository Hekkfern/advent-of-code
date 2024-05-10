#pragma once

#include <optional>
#include <unordered_map>
#include <utils/Concepts.hpp>

namespace utils::cache {

template <Hashable Key, typename Value>
class InfiniteCache {
public:
    InfiniteCache() noexcept = default;
    ~InfiniteCache() = default;
    InfiniteCache(InfiniteCache const&) noexcept = delete;
    InfiniteCache& operator=(InfiniteCache const&) noexcept = delete;
    InfiniteCache(InfiniteCache&& other) noexcept = default;
    InfiniteCache& operator=(InfiniteCache&& other) noexcept = default;

    /**
     * @brief      Gets the value cached for the specified key, if it exists.
     *
     * @param[in]  key   The key.
     *
     * @return     Cached value if exists. Otherwise, std::nullopt.
     */
    [[nodiscard]] std::optional<Value> get(Key const& key)
    {
        auto const it = mCacheItemsMap.find(key);
        if (it == mCacheItemsMap.cend()) {
            return {};
        }
        return it->second;
    }

    /**
     * @brief      Adds a new entry.
     *
     * @param[in]  key    The key.
     * @param[in]  value  The value of @p key.
     */
    void put(Key const& key, Value const& value)
    {
        mCacheItemsMap[key] = value;
    }

    /**
     * @brief      Checks if the selected key exists.
     *
     * @param[in]  key   The key
     *
     * @return     True if the key exists. False, otherwise.
     */
    bool exists(Key const& key) const { return mCacheItemsMap.contains(key); }

    /**
     * @brief      Deletes the entry (key and value) for the selected key, if it
     * exists.
     *
     * @param[in]  key   The key.
     */
    void erase(Key const& key) { mCacheItemsMap.erase(key); }

    /**
     * @brief      Clears all the cache.
     */
    void clear() { mCacheItemsMap.clear(); }

    /**
     * @brief      Get the current amount of entries stored in the cache.
     *
     * @return     Number of entries stored in.
     */
    [[nodiscard]] std::size_t size() const { return mCacheItemsMap.size(); }

private:
    std::unordered_map<Key, Value> mCacheItemsMap{};
};

} // namespace utils::cache
