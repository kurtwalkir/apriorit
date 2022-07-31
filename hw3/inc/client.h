#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <mutex>
#include <atomic>

using namespace std;

/**
* @brief Implementation of simple tcp client.
* */

namespace client {


    /**
    * @brief A simple class that provides API for creation a tcp client.
    */
    class TcpClient {
    private:
        thread tRead, tWrite;
        mutex rMut, wMut;
        int sock;
        int clientFd;
        sockaddr_in serv_addr;
        bool isConnDone = false;
        atomic<bool> stopThreads {false};


        /**
        * @brief Thread for reading user input.
        */
        void readThread();

        /**
        * @brief Thread for printing input data.
        */
        void writeThread();
    public:
        TcpClient() = default;
        TcpClient(const TcpClient &) = delete;
        TcpClient& operator = (const TcpClient &) = delete;
        TcpClient(const TcpClient &&) = delete;
        ~TcpClient() = default;

        /**
        * @brief Connects to the server by given ip and port.
        * @param ip - ip addr.
        * @param port - tcp port.
        */
        void connectToSrv(string ip, unsigned int port);

        /**
        * @brief Disconnects from the server.
        */
        void disconnect();
    };
};
