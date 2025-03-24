#include "PersistentKeyValueStore.h"
#include <iostream>

PersistentKeyValueStore::PersistentKeyValueStore(const std::string& filename) : filename(filename) {
    loadFromDisk();  // ✅ Load previous data from file at startup
}

PersistentKeyValueStore::~PersistentKeyValueStore() {  // ✅ Now correctly defined
    flushToDisk();  // ✅ Ensure data is saved when the object is destroyed
}

void PersistentKeyValueStore::set(const std::string& key, const std::string& value) {
    KeyValueStore::set(key, value);
    flushToDisk();  // ✅ Immediately save changes
}

void PersistentKeyValueStore::flushToDisk() {
    std::ofstream file(filename, std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (const auto& pair : getStore()) {
        file << pair.first << " " << pair.second << "\n";
    }

    file.close();
}

void PersistentKeyValueStore::loadFromDisk() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open file " << filename << " (starting fresh)." << std::endl;
        return;
    }

    std::string key, value;
    while (file >> key >> value) {
        KeyValueStore::set(key, value);  // ✅ Load each key-value pair into memory
    }

    file.close();
}
