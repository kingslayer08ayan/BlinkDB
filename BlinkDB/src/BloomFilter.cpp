#include "BloomFilter.h"
#include <shared_mutex>
#include <iostream>

BloomFilter::BloomFilter(size_t size) : size(size), bitArray(size, false) {}

void BloomFilter::insert(const std::string& key) {
    size_t hash = hashFunc(key) % size;
    size_t bucket = getBucketIndex(hash);  

    std::unique_lock<std::shared_mutex> lock(locks[bucket].mutex);  // ✅ Corrected locking
    bitArray[hash] = true;
}

bool BloomFilter::contains(const std::string& key) {
    size_t hash = hashFunc(key) % size;
    size_t bucket = getBucketIndex(hash);  

    std::shared_lock<std::shared_mutex> lock(locks[bucket].mutex);  // ✅ Corrected locking
    return bitArray[hash];
}
