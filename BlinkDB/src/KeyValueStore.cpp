#include "KeyValueStore.h"

KeyValueStore::KeyValueStore(size_t memtable_size) : bloom(memtable_size) {}

KeyValueStore::~KeyValueStore() {}

void KeyValueStore::set(const std::string& key, const std::string& value) {
    store[key] = value;
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
    store.erase(key);
}

// ✅ Implement getStore() to fix undefined reference
std::unordered_map<std::string, std::string> KeyValueStore::getStore() const {
    return store;
}
