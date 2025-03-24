#include "KeyValueStore.h"
#include <stx/btree_map>  // ✅ Include B+ Tree header

KeyValueStore::KeyValueStore(size_t memtable_size) : bloom(memtable_size,10) {}

KeyValueStore::~KeyValueStore() {}

void KeyValueStore::set(const std::string& key, const std::string& value) {
    store.insert(std::make_pair(key, value));  // ✅ B+ Tree insert
    bloom.insert(key);  // ✅ Add key to Bloom Filter
}

std::string KeyValueStore::get(const std::string& key) {
    if (!bloom.contains(key)) {
        return "";  // ✅ Skip unnecessary lookups
    }
    auto it = store.find(key);
    return (it != store.end()) ? it->second : "";
}

void KeyValueStore::del(const std::string& key) {
    store.erase(key);  // ✅ B+ Tree delete
}

// ✅ Implement getStore() to return a snapshot of the B+ Tree
std::vector<std::pair<std::string, std::string>> KeyValueStore::getStore() const {
    std::vector<std::pair<std::string, std::string>> snapshot;
    for (auto it = store.begin(); it != store.end(); ++it) {
        snapshot.emplace_back(*it);
    }
    return snapshot;
}
