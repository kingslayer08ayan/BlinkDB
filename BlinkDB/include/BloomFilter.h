#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <vector>
#include <string>
#include <array>
#include <shared_mutex>  // ✅ Required for multi-threading
#include <functional>
#include <mutex>
class BloomFilter {
private:
    static constexpr size_t NUM_BUCKETS = 4;
    static constexpr size_t DEFAULT_SIZE = 1000000;

    struct alignas(64) PaddedMutex {  // ✅ Ensure cache-line alignment
        std::shared_mutex mutex;
    };

    std::vector<bool> bitArray;
    std::hash<std::string> hashFunc;
    std::array<PaddedMutex, NUM_BUCKETS> locks;  // ✅ Ensure correct mutex type
    size_t size;

    size_t getBucketIndex(size_t hash) const {
        return hash % NUM_BUCKETS;
    }

public:
    explicit BloomFilter(size_t size = DEFAULT_SIZE);

    void insert(const std::string& key);
    bool contains(const std::string& key);
};

#endif // BLOOMFILTER_H
