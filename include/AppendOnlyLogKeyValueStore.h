#ifndef APPEND_ONLY_LOG_KEY_VALUE_STORE_H
#define APPEND_ONLY_LOG_KEY_VALUE_STORE_H

#include "KeyValueStore.h"

class AppendOnlyLogKeyValueStore : public KeyValueStore {
public:
    AppendOnlyLogKeyValueStore(const std::string& filename);
    void set(const std::string& key, const std::string& value);
    void del(const std::string& key);
    void appendToAOF(const std::string& operation, const std::string& key, const std::string& value = "");

private:
    std::string filename;
};

#endif // APPEND_ONLY_LOG_KEY_VALUE_STORE_H
