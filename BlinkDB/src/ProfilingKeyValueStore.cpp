#include "ProfilingKeyValueStore.h"
#include <gperftools/profiler.h>

void ProfilingKeyValueStore::profileOperations() {
    ProfilerStart("profile.txt");
    // Perform operations here
    ProfilerStop();
}
