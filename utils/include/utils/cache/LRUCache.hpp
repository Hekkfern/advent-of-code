#pragma once

#include <unordered_map>
#include <list>

namespace utils::cache {

class LRUCache {
public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end()) {
            return -1;
        }

        // Move the accessed element to the front of the list
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);

        return cacheMap[key]->second;
    }

    void put(int key, int value) {
        if (cacheMap.find(key) != cacheMap.end()) {
            // Update the value and move the element to the front
            cacheMap[key]->second = value;
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        } else {
            // Insert the new element
            if (cacheList.size() == capacity) {
                int lastKey = cacheList.back().first;
                cacheMap.erase(lastKey);
                cacheList.pop_back();
            }

            cacheList.emplace_front(key, value);
            cacheMap[key] = cacheList.begin();
        }
    }

    private:
    int capacity;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cacheMap;
    std::list<std::pair<int, int>> cacheList;
};

} // namespace utils::cache
