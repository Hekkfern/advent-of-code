#pragma once

#include <list>
#include <optional>
#include <unordered_map>

namespace utils::cache {

// https://github.com/lamerman/cpp-lru-cache/blob/master/include/lrucache.hpp

template <typename Key, typename Value>
class LRUCache {
public:
    explicit LRUCache(std::size_t const maxSize) noexcept
        : mMaxSize{maxSize}
    {
    }

    LRUCache(LRUCache const&) noexcept = delete;
    LRUCache& operator=(LRUCache const&) noexcept = delete;
    LRUCache(LRUCache&& other) noexcept = default;
    LRUCache& operator=(LRUCache&& other) noexcept = default;

    /**
     * @brief
     *
     * @param key
     *
     * @return
     */
    [[nodiscard]] std::optional<Value> get(Key const& key) const
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
     * @brief
     *
     * @details when inserting a new key and the cache is at capacity, the least
     * recently used key should be evicted.
     *
     * @param[in] key
     * @param[in] value
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
            mCacheItemsMap.erase(mCacheItemsList.back()->first);
            mCacheItemsList.pop_back();
        }
    }

    bool exists(Key const& key) const { return mCacheItemsMap.contains(key); }

    void erase(Key const& key)
    {
        auto it = mCacheItemsMap.find(key);
        if (it != mCacheItemsMap.end()) {
            mCacheItemsList.erase(*it);
            mCacheItemsMap.erase(it);
        }
    }

    void clear()
    {
        mCacheItemsList.clear();
        mCacheItemsMap.clear();
    }

    [[nodiscard]] std::size_t size() const { return mCacheItemsMap.size(); }

    [[nodiscard]] std::size_t maxSize() const { return mMaxSize; }

private:
    using KeyValuePair = std::pair<Key, Value>;
    using ListIterator = std::list<KeyValuePair>::iterator;

    std::list<KeyValuePair> mCacheItemsList{};
    std::unordered_map<Key, ListIterator, std::hash<Key>> mCacheItemsMap{};
    std::size_t mMaxSize;
};

} // namespace utils::cache
