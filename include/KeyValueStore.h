#ifndef KEYVALUESTORE_H
#define KEYVALUESTORE_H

#include <string>
#include <vector>
#include "stx/btree_map.h"  // ✅ Include B+ Tree header
#include "BloomFilter.h"

class KeyValueStore {
public:
    KeyValueStore(size_t memtable_size = 10000);
    virtual ~KeyValueStore();

    virtual void set(const std::string& key, const std::string& value);
    virtual std::string get(const std::string& key);
    virtual void del(const std::string& key);

    // ✅ Return a vector instead of unordered_map for B+ Tree compatibility
    virtual std::vector<std::pair<std::string, std::string>> getStore() const;

protected:
    stx::btree_map<std::string, std::string> store;  // ✅ Use B+ Tree instead of unordered_map
    BloomFilter bloom;  // ✅ Bloom filter for fast lookups
};

#endif  // KEYVALUESTORE_H
