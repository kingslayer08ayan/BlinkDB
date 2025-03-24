#ifndef REPL_H
#define REPL_H

#include "KeyValueStore.h"

class REPL {
public:
    void run(KeyValueStore& store);
};

#endif // REPL_H
