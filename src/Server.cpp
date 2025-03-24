#include "Server.h"
#include <iostream>
#include <istream>
BlinkDBServer::BlinkDBServer(int port) : store(10000) {  
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, SOMAXCONN) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    // ✅ Create epoll instance
    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("Epoll creation failed");
        exit(EXIT_FAILURE);
    }

    setNonBlocking(server_fd);

    epoll_event event{};
    event.events = EPOLLIN;
    event.data.fd = server_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event);

    std::cout << "BlinkDB RESP2 server listening on port " << port << std::endl;
}

void BlinkDBServer::setNonBlocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void BlinkDBServer::run() {
    epoll_event events[MAX_EVENTS];

    while (true) {
        int num_fds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        for (int i = 0; i < num_fds; i++) {
            if (events[i].data.fd == server_fd) {
                sockaddr_in client_addr;
                socklen_t addr_len = sizeof(client_addr);
                int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
                if (client_fd < 0) continue;

                setNonBlocking(client_fd);

                epoll_event client_event{};
                client_event.events = EPOLLIN | EPOLLET; // Edge-triggered mode
                client_event.data.fd = client_fd;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &client_event);
            } else {
                handleClient(events[i].data.fd);
            }
        }
    }
}

void BlinkDBServer::handleClient(int client_fd) {
    char buffer[1024] = {0};
    int bytes_read = read(client_fd, buffer, 1024);
    
    if (bytes_read <= 0) {
        close(client_fd);
        epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, nullptr);
        return;
    }

    std::vector<std::string> command = parseRESP2(std::string(buffer));
    std::string response = processCommand(command);

    send(client_fd, response.c_str(), response.length(), 0);
}

std::vector<std::string> BlinkDBServer::parseRESP2(const std::string& input) {
    std::vector<std::string> result;
    size_t pos = 0;
    
    while (pos < input.size()) {
        if (input[pos] == '*' || input[pos] == '$') {
            pos = input.find("\n", pos);
            if (pos == std::string::npos) break;
            pos++;
        } else {
            size_t end = input.find("\r\n", pos);
            if (end == std::string::npos) break;
            result.push_back(input.substr(pos, end - pos));
            pos = end + 2;
        }
    }

    return result;
}


std::string BlinkDBServer::processCommand(const std::vector<std::string>& command) {
    if (command.empty()) return "-ERR unknown command\r\n";

    std::string cmd = command[0];

    if (cmd == "PING") {
        return "+PONG\r\n";
    } else if (cmd == "SET" && command.size() == 3) {
        store.set(command[1], command[2]);
        return "+OK\r\n";
    } else if (cmd == "GET" && command.size() == 2) {
        std::string value = store.get(command[1]);
        return value.empty() ? "$-1\r\n" : "$" + std::to_string(value.length()) + "\r\n" + value + "\r\n";
    } else if (cmd == "DEL" && command.size() == 2) {
        store.del(command[1]);
        return ":1\r\n";
    } else {
        return "-ERR unknown command\r\n";
    }
}
