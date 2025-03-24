#include "BloomFilter.h"
#include <functional>

BloomFilter::BloomFilter(size_t size) : bit_array(size, false) {}

void BloomFilter::insert(const std::string& key) {
    bit_array[hash(key, 1) % bit_array.size()] = true;
    bit_array[hash(key, 2) % bit_array.size()] = true;
}

bool BloomFilter::probablyContains(const std::string& key) const {
    return bit_array[hash(key, 1) % bit_array.size()] &&
           bit_array[hash(key, 2) % bit_array.size()];
}

size_t BloomFilter::hash(const std::string& key, int seed) const {
    std::hash<std::string> hasher;
    return hasher(key) ^ (seed * 0x9e3779b9);
}
