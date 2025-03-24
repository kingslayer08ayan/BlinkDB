#include "BloomFilter.h"

BloomFilter::BloomFilter(size_t size) : size(size), bitArray(size, false) {}

void BloomFilter::insert(const std::string& key) {
    size_t index = hashFn(key) % size;
    bitArray[index] = true;
}

bool BloomFilter::contains(const std::string& key) const {
    size_t index = hashFn(key) % size;
    return bitArray[index];
}
