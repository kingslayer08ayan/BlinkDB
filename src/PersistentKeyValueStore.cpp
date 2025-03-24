#include "PersistentKeyValueStore.h"
#include <iostream>

PersistentKeyValueStore::PersistentKeyValueStore(const std::string& filename)
    : filename(filename), wal("wal.log", std::ios::app) {
    loadFromDisk();

    // ✅ Start background WAL flush thread
    walThread = std::thread(&PersistentKeyValueStore::walWorker, this);
}

PersistentKeyValueStore::~PersistentKeyValueStore() {
    stopWalThread = true;
    walCondVar.notify_one();  // ✅ Wake up the WAL thread to exit
    if (walThread.joinable()) walThread.join();

    flushWAL();  // ✅ Ensure remaining WAL entries are flushed before exit
    flushToDisk();
    wal.close();
}

void PersistentKeyValueStore::set(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(walMutex);
    walBuffer.push_back("SET " + key + " " + value + "\n");
    if (walBuffer.size() >= walThreshold) {
        walCondVar.notify_one();  // ✅ Wake up WAL thread
    }
    KeyValueStore::set(key, value);
}

void PersistentKeyValueStore::del(const std::string& key) {
    std::lock_guard<std::mutex> lock(walMutex);
    walBuffer.push_back("DEL " + key + "\n");
    if (walBuffer.size() >= walThreshold) {
        walCondVar.notify_one();  // ✅ Wake up WAL thread
    }
    KeyValueStore::del(key);
}

void PersistentKeyValueStore::flushWAL() {
    std::lock_guard<std::mutex> lock(walMutex);
    for (const std::string& entry : walBuffer) {
        wal << entry;
    }
    wal.flush();
    walBuffer.clear();
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

void PersistentKeyValueStore::walWorker() {
    while (!stopWalThread) {
        std::unique_lock<std::mutex> lock(walMutex);
        walCondVar.wait_for(lock, std::chrono::seconds(2), [&] { return !walBuffer.empty(); });
        if (!walBuffer.empty()) {
            flushWAL();
        }
    }
}
void PersistentKeyValueStore::flushToDisk() {
    std::lock_guard<std::mutex> lock(walMutex);

    std::ofstream file(filename, std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open " << filename << " for writing." << std::endl;
        return;
    }

    auto storeMap = getStore();
    for (const auto& pair : storeMap) {
        file << pair.first << " " << pair.second << "\n";
    }

    file.close();
}