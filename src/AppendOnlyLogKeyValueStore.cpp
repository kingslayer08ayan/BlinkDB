#include "AppendOnlyLogKeyValueStore.h"
#include <fstream>

AppendOnlyLogKeyValueStore::AppendOnlyLogKeyValueStore(const std::string& filename) {
    this->filename = filename;
}

void AppendOnlyLogKeyValueStore::set(const std::string& key, const std::string& value) {
    KeyValueStore::set(key, value);
    appendToAOF("SET", key, value);
}

void AppendOnlyLogKeyValueStore::del(const std::string& key) {
    KeyValueStore::del(key);
    appendToAOF("DEL", key);
}

void AppendOnlyLogKeyValueStore::appendToAOF(const std::string& operation, const std::string& key, const std::string& value) {
    std::ofstream file(filename, std::ios_base::app);
    if (operation == "SET") {
        file << "SET " << key << " " << value << std::endl;
    } else if (operation == "DEL") {
        file << "DEL " << key << std::endl;
    }
}
