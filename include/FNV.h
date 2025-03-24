#ifndef FNVHASH_H
#define FNVHASH_H

#include <cstdint>
#include <string>

inline uint32_t fnv1aHash(const std::string& key) {
    uint32_t hash = 2166136261u;  // FNV offset basis
    for (char c : key) {
        hash ^= static_cast<uint8_t>(c);
        hash *= 16777619u;  // FNV prime
    }
    return hash;
}

#endif // FNVHASH_H
