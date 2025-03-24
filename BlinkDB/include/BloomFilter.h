#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <vector>
#include <string>
#include <functional>

class BloomFilter {
public:
    BloomFilter(size_t size);
    void insert(const std::string& key);
    bool contains(const std::string& key) const;

private:
    size_t size;
    std::vector<bool> bitArray;
    std::hash<std::string> hashFn; // Simple hash function
};

#endif  // BLOOMFILTER_H
