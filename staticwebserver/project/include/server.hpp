#pragma once

#include <vector>
#include <queue>
#include <mutex>
#include <netinet/in.h>
#include <iostream>
#include <thread>
#include <cstring>
#include <condition_variable>

#include "constants.hpp"


class Server {
public:
    Server() = delete;

    explicit Server(size_t poolSize = POOL_SIZE, int port = PORT, int countConn = CNT_CONN)
    : poolSize(poolSize), serverPort(port), queueConnections(CNT_CONN) {
        this->serverSocket = 0;
        this->clientSocket = 0;

        memset(&this->serverAddr, 0, sizeof(struct sockaddr_in));
        memset(&this->clientAddr, 0, sizeof(struct sockaddr_in));

        // Set the thread pool size
        this-> threadPool.resize(this->poolSize);

        for(size_t i = 0; i < this->poolSize; i++) {
            this->threadPool[i] = std::thread([this](){ this->handleRequest();});
        }
    };

    bool Init();
    void Run();
private:
    int serverSocket;
    int clientSocket;

    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;

    int serverPort;

    std::vector<std::thread> threadPool;
    size_t poolSize;

    std::queue<int> requestQueue;

    int queueConnections;

    std::mutex queueMutex;
    std::condition_variable cv;

    void handleRequest();

    bool loadConfig();
};

