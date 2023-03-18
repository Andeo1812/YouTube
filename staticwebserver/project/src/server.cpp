#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fstream>
#include <sstream>

#include <server.hpp>
#include <http_handler.hpp>

bool Server::Init() {
    this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Can not create socket" << std::endl;

        return {};
    }

    // Set server address
    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_port = htons(this->serverPort);
    this->serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Binding the socket to the address
    if (bind(this->serverSocket, (struct sockaddr *) &this->serverAddr, sizeof(this->serverAddr)) == -1) {
        std::cerr << "Failed to bind the socket to address " << errno << std::endl;
        return {};
    }

    // Setting the socket to passive
    listen(serverSocket, queueConnections);

    return true;
}

void Server::Run() {
    while (true) {
        //  Accept the connection
        socklen_t addr_size = sizeof(this->clientAddr);
        this->clientSocket = accept(serverSocket, (struct sockaddr *) &this->clientAddr, &addr_size);

        //  Displaying the IP of the peer app
        char peerIP[INET_ADDRSTRLEN] = {0};

        if (!inet_ntop(AF_INET, &this->clientAddr.sin_addr, peerIP, sizeof(peerIP))) {
            return;
        }

        this->queueMutex.lock();
        this->requestQueue.push(clientSocket);
        this->cv.notify_one();
        this->queueMutex.unlock();
    }
}

void Server::handleRequest() {
    std::unique_lock<std::mutex> lock(this->queueMutex, std::defer_lock);
    int client_socket = -1;

    HTTPHandler requestHandler;

    while (true) {
        // Pop the client socket from the queue
        lock.lock();
        this->cv.wait(lock, [this]() { return !this->requestQueue.empty(); });
        client_socket = this->requestQueue.front();
        this->requestQueue.pop();
        lock.unlock();

        char req[2 * REQ_SIZE];
        recv(client_socket, req, sizeof(req), 0);

        std::string reply = requestHandler.handle(req);

        send(client_socket, reply.c_str(), reply.size(), 0);

        // Closing connection
        close(client_socket);
    }
}

bool Server::loadConfig() {
    std::fstream configFile;
    configFile.open("../configs/config", std::ios::in);

    if (!configFile.is_open()) {
        return {};
    }

    int lineNum = 1;
    std::string line;
    std::string key;
    std::string value;

    while (getline(configFile, line)) {
        std::stringstream ssline(line);
        std::getline(ssline, key, '=');
        std::getline(ssline, value);

        if (key[0] == '#') {
            lineNum++;
            continue;
        } else if (key == "pool_size") {
            this->poolSize = std::stoi(value);
        } else if (key == "port_number") {
            this->serverPort = std::stoi(value);
        } else if (key == "backlog_size") {
            this->queueConnections = std::stoi(value);
        } else {
            std::cerr << "Warning : Invalid configuration key at line " << lineNum << std::endl;
        }

        lineNum++;
    }

    configFile.close();

    return true;
}
