#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <vector>
#include <string>

class BloomFilter {
public:
    BloomFilter(size_t size);
    void insert(const std::string& key);
    bool probablyContains(const std::string& key) const;
    void remove(const std::string& key); // Optional

private:
    size_t hash(const std::string& key, int seed) const;
    std::vector<bool> bit_array;
};

#endif // BLOOMFILTER_H
