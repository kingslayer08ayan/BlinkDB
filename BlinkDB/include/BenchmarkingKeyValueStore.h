#ifndef BENCHMARKINGKEYVALUESTORE_H
#define BENCHMARKINGKEYVALUESTORE_H

#include "PersistentKeyValueStore.h"
#include "LRUCache.h"
#include "ThreadSafeKeyValueStore.h"
#include "AppendOnlyLogKeyValueStore.h"

class BenchmarkingKeyValueStore {
public:
    void benchmarkOperations(int numOperations);
};

#endif  // BENCHMARKINGKEYVALUESTORE_H
