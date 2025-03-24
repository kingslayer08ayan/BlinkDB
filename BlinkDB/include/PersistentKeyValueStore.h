#ifndef PERSISTENTKEYVALUESTORE_H
#define PERSISTENTKEYVALUESTORE_H

#include "KeyValueStore.h"
#include <fstream>
#include <string>

class PersistentKeyValueStore : public KeyValueStore {
public:
    PersistentKeyValueStore(const std::string& filename);
    ~PersistentKeyValueStore();

    void set(const std::string& key, const std::string& value) override;
    void del(const std::string& key) override;
    void flushToDisk();
    void loadFromDisk();

private:
    std::string filename;
    std::ofstream wal;  // ✅ Write-Ahead Log file

    void writeToWAL(const std::string& operation, const std::string& key, const std::string& value = "");
};

#endif  // PERSISTENTKEYVALUESTORE_H
