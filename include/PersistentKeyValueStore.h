#ifndef PERSISTENTKEYVALUESTORE_H
#define PERSISTENTKEYVALUESTORE_H

#include "KeyValueStore.h"
#include <fstream>
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>
#include <condition_variable>

class PersistentKeyValueStore : public KeyValueStore {
public:
    PersistentKeyValueStore(const std::string& filename);
    virtual ~PersistentKeyValueStore();  // ✅ Ensure virtual destructor is declared

    void set(const std::string& key, const std::string& value) override;
    void del(const std::string& key) override;
    void flushToDisk();
    void loadFromDisk();
    void flushWAL();

private:
    std::string filename;
    std::ofstream wal;
    std::vector<std::string> walBuffer;
    size_t walThreshold = 1000;

    std::thread walThread;
    std::mutex walMutex;
    std::condition_variable walCondVar;
    std::atomic<bool> stopWalThread{false};

    void walWorker();  // ✅ Background WAL thread
};

#endif  // PERSISTENTKEYVALUESTORE_H
