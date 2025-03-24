#ifndef PERSISTENTKEYVALUESTORE_H
#define PERSISTENTKEYVALUESTORE_H

#include "KeyValueStore.h"
#include <fstream>

class PersistentKeyValueStore : public KeyValueStore {
public:
    PersistentKeyValueStore(const std::string& filename);
    virtual ~PersistentKeyValueStore();  // ✅ Declare virtual destructor

    void set(const std::string& key, const std::string& value) override;
    void flushToDisk();
    void loadFromDisk();

private:
    std::string filename;
};

#endif  // PERSISTENTKEYVALUESTORE_H
