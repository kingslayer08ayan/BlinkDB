#include "BloomFilter.h"
#include "Murmurhash.h"
#include <mutex>
#include <iostream>
BloomFilter::BloomFilter(size_t num_keys, size_t bits_per_key) {
    size = std::min(num_keys * bits_per_key, (size_t)1e8); // Reduce to 10M bits
    std::cout << "Allocating BloomFilter with size: " << size / 8 << " bytes\n";
    
    try {
        bitArray.resize(size, false);  // This may be the culprit
    } catch (const std::bad_alloc& e) {
        std::cerr << "BloomFilter allocation failed: " << e.what() << "\n";
        exit(1);
    }

    optimal_k = std::max(1, static_cast<int>(std::log(2) * bits_per_key));
}

void BloomFilter::insert(const std::string& key) {
    size_t hash1 = MurmurHash2(key.data(), key.size(), 0);
    size_t hash2 = MurmurHash2(key.data(), key.size(), hash1);

    for (size_t i = 0; i < optimal_k; ++i) {
        size_t hash = (hash1 + i * hash2) % size;
        size_t bucket = getBucketIndex(hash);
        while (locks[bucket].flag.test_and_set(std::memory_order_acquire));  // ✅ Spinlock
        bitArray[hash] = 1;
        locks[bucket].flag.clear(std::memory_order_release);
    }
}

bool BloomFilter::contains(const std::string& key) {
    size_t hash1 = MurmurHash2(key.data(), key.size(), 0);
    size_t hash2 = MurmurHash2(key.data(), key.size(), hash1);

    for (size_t i = 0; i < optimal_k; ++i) {
        size_t hash = (hash1 + i * hash2) % size;
        if (!bitArray[hash]) return false;
    }
    return true;
}
