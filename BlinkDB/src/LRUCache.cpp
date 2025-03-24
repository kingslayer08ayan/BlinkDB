#include "LRUCache.h"

LRUCache::LRUCache(int capacity) : capacity(capacity) {}

void LRUCache::put(const std::string& key, const std::string& value) {
    auto it = map.find(key);
    if (it != map.end()) {
        cache.erase(it->second);
    } else if (cache.size() >= capacity) {
        map.erase(cache.front().first);
        cache.pop_front();
    }

    cache.push_back({key, value});
    map[key] = --cache.end();
}
