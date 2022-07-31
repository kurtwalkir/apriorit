
#include "server.h"
using namespace server;

TcpServer::TcpServer(string ip, unsigned int port) {
    serverIp = ip;
    PORT = port;
}

void TcpServer::acceptThread() {

    initServer();
    while(!stopThreads.load()) {
        auto *resa = reinterpret_cast<sockaddr*>(&address);
        auto addrlen = sizeof(address);
        int newSocket;
        if ((newSocket = accept(serverFd, resa, (socklen_t*)&addrlen)) < 0) {
            close(serverFd);
            throw std::runtime_error("Cann't accept client!");
        }

        if (indx < MAX_CLIENTS) {
            clients.push_back(newSocket);
            clientsThreads[indx++] = thread(&TcpServer::serverThread, this, newSocket);
        }
        this_thread::sleep_for(100ms);
    }
}

void TcpServer::serverThread(int fd) {

    while(true) {
        char buffer[INPUT_BUFFER] = { '\0' };
        read(fd, buffer, INPUT_BUFFER);
        mut.lock();
            if (!strncmp(buffer, "hello", strlen("hello"))) {
                send(fd, "world", strlen("world"), 0);
            } else if (!strncmp(buffer, "disconnect", strlen("disconnect"))) {
                shutdownSrv();
            } else {
                send(fd, buffer, strlen(buffer), 0);
            }
        mut.unlock();
        this_thread::sleep_for(200ms);
    }
}

void TcpServer::initServer() {

    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        throw std::runtime_error("Cann't create socket!");
    }

        if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                sizeof(opt))) {
        close(serverFd);
        throw std::runtime_error("Cann't setsockopt!");
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    auto *resa = reinterpret_cast<sockaddr*>(&address);
    if (bind(serverFd, resa, sizeof(address)) < 0) {
        close(serverFd);
        throw std::runtime_error("Cann't bind socket!");
    }
    if (listen(serverFd, MAX_CLIENTS) < 0) {
        close(serverFd);
        throw std::runtime_error("Cann't listen socket!");
    }
}

void TcpServer::run() {
    t = thread(&TcpServer::acceptThread, this);
    t.join();
}

void TcpServer::shutdownSrv() {
    stopThreads = true;
    for (const auto &it: clients) {
        close(it);
    }
    shutdown(serverFd, SHUT_RDWR);
}
