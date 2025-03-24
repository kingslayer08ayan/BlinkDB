#include "PersistentKeyValueStore.h"
#include "REPL.h"

int main() {
    PersistentKeyValueStore store("database.json");  // ✅ Pass the filename
    REPL repl;
    repl.run(store);  // ✅ Now works because of correct inheritance
    return 0;
}
