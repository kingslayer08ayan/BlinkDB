#ifndef THREADSAFEKEYVALUESTORE_H
#define THREADSAFEKEYVALUESTORE_H

#include "KeyValueStore.h"
#include <mutex>

class ThreadSafeKeyValueStore : public KeyValueStore {  // ✅ Added inheritance
public:
    void set(const std::string& key, const std::string& value) override;

private:
    std::mutex mtx;
};

#endif  // THREADSAFEKEYVALUESTORE_H
