#ifndef PROFILING_KEY_VALUE_STORE_H
#define PROFILING_KEY_VALUE_STORE_H

#include "KeyValueStore.h"

class ProfilingKeyValueStore : public KeyValueStore {
public:
    void profileOperations();
};

#endif // PROFILING_KEY_VALUE_STORE_H
