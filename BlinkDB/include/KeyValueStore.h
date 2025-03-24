#ifndef KEYVALUESTORE_H
#define KEYVALUESTORE_H

#include <unordered_map>
#include <string>
#include "BloomFilter.h"

class KeyValueStore {
public:
    KeyValueStore(size_t memtable_size = 10000);
    virtual ~KeyValueStore();

    virtual void set(const std::string& key, const std::string& value);
    virtual std::string get(const std::string& key);
    virtual void del(const std::string& key);
    
    // ✅ Ensure correct declaration (const added)
    virtual std::unordered_map<std::string, std::string> getStore() const;

protected:
    std::unordered_map<std::string, std::string> store;
    BloomFilter bloom;  // ✅ Bloom filter for fast lookups
};

#endif  // KEYVALUESTORE_H
