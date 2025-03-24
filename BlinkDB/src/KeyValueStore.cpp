#include "KeyValueStore.h"

KeyValueStore::KeyValueStore(size_t memtable_size) {}

void KeyValueStore::set(const std::string& key, const std::string& value) {
    store[key] = value;
}

std::string KeyValueStore::get(const std::string& key) {
    auto it = store.find(key);
    return (it != store.end()) ? it->second : "";
}

void KeyValueStore::del(const std::string& key) {
    store.erase(key);
}

std::unordered_map<std::string, std::string> KeyValueStore::getStore() const {
    return store;
}
