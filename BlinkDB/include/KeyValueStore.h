#ifndef KEYVALUESTORE_H
#define KEYVALUESTORE_H

#include <unordered_map>
#include <string>

class KeyValueStore {
public:
    KeyValueStore(size_t memtable_size = 1000);  // ✅ Constructor added
    virtual void set(const std::string& key, const std::string& value);
    virtual std::string get(const std::string& key);
    virtual void del(const std::string& key);
    std::unordered_map<std::string, std::string> getStore() const;

    virtual ~KeyValueStore() {}  // ✅ Virtual destructor to fix vtable issue

protected:
    std::unordered_map<std::string, std::string> store;
};

#endif  // KEYVALUESTORE_H
