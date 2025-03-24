#include "BenchmarkingKeyValueStore.h"
#include <chrono>
#include <iostream>
#include <thread>

void BenchmarkingKeyValueStore::benchmarkOperations(int numOperations) {
    // Persistence Test
    PersistentKeyValueStore persistentStore("benchmark_data.json");
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back([&persistentStore, numOperations, i]() {
            for (int j = i * numOperations / 4; j < (i + 1) * numOperations / 4; ++j) {
                persistentStore.set(std::to_string(j), "value");
            }
        });
    }
    for (auto& t : threads) {
        t.join();
    }
    persistentStore.flushToDisk(); // Flush to disk once after all operations
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Persistence Test Duration: " << duration << " ms" << std::endl;

    // LRU Cache Test
    LRUCache cache(1000);
    start = std::chrono::high_resolution_clock::now();
    threads.clear();
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back([&cache, numOperations, i]() {
            for (int j = i * numOperations / 4; j < (i + 1) * numOperations / 4; ++j) {
                cache.put(std::to_string(j), "value");
            }
        });
    }
    for (auto& t : threads) {
        t.join();
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "LRU Cache Test Duration: " << duration << " ms" << std::endl;

    // Multi-threading Test
    ThreadSafeKeyValueStore threadSafeStore;
    start = std::chrono::high_resolution_clock::now();
    threads.clear();
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back([&threadSafeStore, numOperations, i]() {
            for (int j = i * numOperations / 4; j < (i + 1) * numOperations / 4; ++j) {
                threadSafeStore.set(std::to_string(j), "value");
            }
        });
    }
    for (auto& t : threads) {
        t.join();
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Multi-threading Test Duration: " << duration << " ms" << std::endl;

    // AOF Test
    AppendOnlyLogKeyValueStore aofStore("aof_log.txt");
    start = std::chrono::high_resolution_clock::now();
    threads.clear();
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back([&aofStore, numOperations, i]() {
            for (int j = i * numOperations / 4; j < (i + 1) * numOperations / 4; ++j) {
                aofStore.set(std::to_string(j), "value");
            }
        });
    }
    for (auto& t : threads) {
        t.join();
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "AOF Test Duration: " << duration << " ms" << std::endl;
}
