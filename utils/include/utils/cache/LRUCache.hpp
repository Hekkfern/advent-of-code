#pragma once

#include <optional>
#include <unordered_map>
#include <list>

namespace utils::cache {

// https://github.com/lamerman/cpp-lru-cache/blob/master/include/lrucache.hpp

template <typename Key, typename Value>
class LRUCache {
public:
    typedef typename std::pair<Key, Value> KeyValuePair;
	typedef typename std::list<KeyValuePair>::iterator ListIterator;


    LRUCache(std::size_t const maxSize) : mMaxSize{maxSize};

    LRUCache(const LRUCache&)=delete;
    LRUCache & 	operator= (const LRUCache &)=delete;
    LRUCache (LRUCache &&other) noexcept=default;
    LRUCache & 	operator= (LRUCache &&other) noexcept=default;

    [[nodiscard]] std::optional<Value> get(Key const& key) const
    {
        auto it = _cache_items_map.find(key);
		if (it == _cache_items_map.end()) {
			return {};
		}
			_cache_items_list.splice(_cache_items_list.begin(), _cache_items_list, it->second);
			return it->second->second;
    }

    /**
     * @brief
     *
     * @details when inserting a new key and the cache is at capacity, the least recently used key should be evicted.
     *
     * @param[in] key
     * @param[in] value
     */
    void put(Key const& key, Value const& value)
    {
        auto it = _cache_items_map.find(key);
		_cache_items_list.push_front(key_value_pair_t(key, value));
		if (it != _cache_items_map.end()) {
			_cache_items_list.erase(it->second);
			_cache_items_map.erase(it);
		}
		_cache_items_map[key] = _cache_items_list.begin();

		if (_cache_items_map.size() > _max_size) {
			auto last = _cache_items_list.end();
			last--;
			_cache_items_map.erase(last->first);
			_cache_items_list.pop_back();
		}
    }

    bool exists(Key const& key) const{
        return _cache_items_map.find(key) != _cache_items_map.end();
    }

    void erase(Key const& key)
    {
        // TODO
    }

    void clear(){
        _cache_items_list.clear();
        _cache_items_map.clear();
    }

    [[nodiscard]] std::size_t size()const {
         return _cache_items_map.size();
    }

      [[nodiscard]] std::size_t maxSize()const {
        return mMaxSize;
    }


private:
    std::list<key_value_pair_t> _cache_items_list;
	std::unordered_map<key_t, list_iterator_t> _cache_items_map;
    std::size mMaxSize;
};

} // namespace utils::cache
