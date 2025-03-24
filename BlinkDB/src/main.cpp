#include "PersistentKeyValueStore.h"
#include "REPL.h"

int main() {
    PersistentKeyValueStore store("database.json");
    REPL repl;
    repl.run(store);
    return 0;
}
