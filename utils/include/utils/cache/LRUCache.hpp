#pragma once

#include <list>
#include <optional>
#include <unordered_map>
#include <utils/Concepts.hpp>

namespace utils::cache {

template <typename Key, typename Value>
    requires std::equality_comparable<Key> && Hashable<Key>
class LRUCache {
public:
    /**
     * @brief      Constructor
     *
     * @param[in]  maxSize  The maximum capacity of the cache. Once this
     *                      capacity is surpassed, the oldest entries are
     *                      started being evicted.
     */
    explicit LRUCache(std::size_t const maxSize) noexcept
        : mMaxSize{maxSize}
    {
    }

    LRUCache(LRUCache const&) noexcept = delete;
    LRUCache& operator=(LRUCache const&) noexcept = delete;
    LRUCache(LRUCache&& other) noexcept = default;
    LRUCache& operator=(LRUCache&& other) noexcept = default;

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
        mCacheItemsList.splice(
            mCacheItemsList.begin(), mCacheItemsList, it->second);
        return it->second->second;
    }

    /**
     * @brief      Adds a new entry.
     *
     * @details    When inserting a new key and the cache is at capacity, the
     *             least recently used key is evicted.
     *
     * @param[in]  key    The key.
     * @param[in]  value  The value of @p key.
     */
    void put(Key const& key, Value const& value)
    {
        auto it = mCacheItemsMap.find(key);
        mCacheItemsList.emplace_front(key, value);
        if (it != mCacheItemsMap.end()) {
            mCacheItemsList.erase(it->second);
            mCacheItemsMap.erase(it);
        }
        mCacheItemsMap[key] = mCacheItemsList.begin();

        if (mCacheItemsMap.size() > mMaxSize) {
            auto last = mCacheItemsList.end();
            --last;
            mCacheItemsMap.erase(last->first);
            mCacheItemsList.pop_back();
        }
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
     * @brief      Deletes the entry (key and value) for the selected key.
     *
     * @param[in]  key   The key.
     */
    void erase(Key const& key)
    {
        auto it = mCacheItemsMap.find(key);
        if (it != mCacheItemsMap.end()) {
            mCacheItemsList.erase(it->second);
            mCacheItemsMap.erase(it);
        }
    }

    /**
     * @brief      Clears all the cache.
     */
    void clear()
    {
        mCacheItemsList.clear();
        mCacheItemsMap.clear();
    }

    /**
     * @brief      Get the current amount of entries storedin the cache.
     *
     * @return     Number of entries stored in.
     */
    [[nodiscard]] std::size_t size() const { return mCacheItemsMap.size(); }

    /**
     * @brief      Gets the maximum capacity of the cache.
     *
     * @return     Maximum number of entries capable to contain.
     */
    [[nodiscard]] std::size_t maxSize() const { return mMaxSize; }

private:
    using KeyValuePair = std::pair<Key, Value>;
    using ListIterator = std::list<KeyValuePair>::iterator;

    std::list<KeyValuePair> mCacheItemsList{};
    std::unordered_map<Key, ListIterator> mCacheItemsMap{};
    std::size_t mMaxSize;
};

} // namespace utils::cache
