#ifndef SERVER_H
#define SERVER_H

#include "KeyValueStore.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_EVENTS 1024  // Maximum concurrent clients

class BlinkDBServer {
public:
    BlinkDBServer(int port);
    void run();

private:
    int server_fd;
    int epoll_fd;
    KeyValueStore store;

    void handleClient(int client_fd);
    std::vector<std::string> parseRESP2(const std::string& input);
    std::string processCommand(const std::vector<std::string>& command);
    void setNonBlocking(int fd);
};

#endif // SERVER_H
