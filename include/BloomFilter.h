#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <vector>
#include <string>
#include <atomic>
#include <cmath>

class BloomFilter {
private:
    static constexpr size_t NUM_BUCKETS = 16;
    static constexpr size_t MAX_BLOOM_SIZE = 10'000'000;  // ✅ Prevent excessive allocation

    struct alignas(64) PaddedLock {  // ✅ Avoid false sharing
        std::atomic_flag flag = ATOMIC_FLAG_INIT;
    };

    std::vector<bool> bitArray;
    size_t size;
    int optimal_k;  // ✅ Fixed hash count to avoid excess hashing
    PaddedLock locks[NUM_BUCKETS];

    size_t getBucketIndex(size_t hash) const {
        return hash % NUM_BUCKETS;
    }

public:
    explicit BloomFilter(size_t num_keys, size_t bits_per_key);

    void insert(const std::string& key);
    bool contains(const std::string& key);
};

#endif  // BLOOMFILTER_H
