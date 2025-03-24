#ifndef SERVER_H
#define SERVER_H

#include "KeyValueStore.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <arpa/inet.h>

class BlinkDBServer {
public:
    BlinkDBServer(int port);
    void run();

private:
    int server_fd;
    KeyValueStore store;
    void handleClient(int client_fd);
    std::vector<std::string> parseRESP2(const std::string& input);
    std::string processCommand(const std::vector<std::string>& command);
};

#endif // SERVER_H
