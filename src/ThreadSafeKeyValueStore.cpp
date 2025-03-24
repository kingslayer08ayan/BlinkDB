#include "ThreadSafeKeyValueStore.h"

void ThreadSafeKeyValueStore::set(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(mtx);
    KeyValueStore::set(key, value);  // ✅ Correct way to call base class method
}
