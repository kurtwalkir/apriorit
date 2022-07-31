#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <mutex>
#include <atomic>

using namespace std;

/**
* @brief Implementation of simple tcp server.
* */

namespace server {
    class TcpServer {
    private:
        const unsigned char INPUT_BUFFER = 64;
        unsigned int PORT = 1234;
        string serverIp{"127.0.0.1"};
        const unsigned char MAX_CLIENTS = 5;
        vector<int> clients;
        int opt;
        mutex mut;
        atomic<bool> stopThreads {false};

        std::thread t;
        std::thread clientsThreads[5];
        size_t indx = 0;
        sockaddr_in address;
        int serverFd;
        void serverThread(int fd);
        void acceptThread();
        void initServer();
        void shutdownSrv();

    public:
        TcpServer() = default;
        ~TcpServer() = default;
        TcpServer(string ip, unsigned int port);
        TcpServer(const TcpServer &) = delete;
        TcpServer& operator = (const TcpServer &) = delete;
        TcpServer(const TcpServer &&) = delete;

        /**
        * @brief Creates a server thread.
        */
        void run();
    };
};