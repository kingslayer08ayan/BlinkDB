#include "REPL.h"
#include <iostream>

void REPL::run(KeyValueStore& store) {
    while (true) {
        std::cout << "Enter command (SET, GET, DEL, EXIT): ";
        std::string command, key, value;
        std::cin >> command;
        if (command == "EXIT") break;
        std::cin >> key;
        if (command == "SET") {
            std::cin >> value;
            store.set(key, value);
        } else if (command == "GET") {
            std::cout << store.get(key) << std::endl;
        } else if (command == "DEL") {
            store.del(key);
        }
    }
}
