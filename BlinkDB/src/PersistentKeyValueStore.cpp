#include "PersistentKeyValueStore.h"
#include <iostream>

PersistentKeyValueStore::PersistentKeyValueStore(const std::string& filename) : filename(filename), wal("wal.log", std::ios::app) {
    loadFromDisk();
}

PersistentKeyValueStore::~PersistentKeyValueStore() {
    flushToDisk();  // Ensure data is written on shutdown
    wal.close();
}

void PersistentKeyValueStore::set(const std::string& key, const std::string& value) {
    writeToWAL("SET", key, value);
    KeyValueStore::set(key, value);
}

void PersistentKeyValueStore::del(const std::string& key) {
    writeToWAL("DEL", key);
    KeyValueStore::del(key);
}

void PersistentKeyValueStore::writeToWAL(const std::string& operation, const std::string& key, const std::string& value) {
    wal << operation << " " << key;
    if (!value.empty()) wal << " " << value;
    wal << "\n";
    wal.flush();  // ✅ Ensure write is immediately recorded
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
        KeyValueStore::set(key, value);
    }
    file.close();
}
