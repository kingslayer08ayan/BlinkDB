#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <list>
#include <unordered_map>
#include <string>

class LRUCache {
public:
    LRUCache(int capacity);
    void put(const std::string& key, const std::string& value);

private:
    int capacity;
    std::list<std::pair<std::string, std::string>> cache;
    std::unordered_map<std::string, std::list<std::pair<std::string, std::string>>::iterator> map;
};

#endif  // LRUCACHE_H
