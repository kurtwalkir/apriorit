#include "client.h"
using namespace client;

void TcpClient::connectToSrv(string ip, unsigned int port) {

    if (isConnDone) {
        return;
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        throw std::runtime_error("Cann't create socket!");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0) {
        close(sock);
        throw std::runtime_error("Cann't init server address class!");
    }

    auto *resa = reinterpret_cast<sockaddr*>(&serv_addr);
    if ((clientFd = connect(sock, resa, sizeof(serv_addr))) < 0) {
        close(sock);
        throw std::runtime_error("Cann't connect to the server!");
    }
    isConnDone = true;

    tRead=std::thread(&TcpClient::readThread, this);
    tWrite=std::thread(&TcpClient::writeThread, this);
    tWrite.join();
    tRead.join();
}

void TcpClient::disconnect() {
    if (isConnDone && sock > 0) {
         stopThreads = true;
         close(sock);
    }
}

void TcpClient::readThread() {

    while (!stopThreads.load()) {
        rMut.lock();
        char buffer[64] = { '\0' };
        const size_t len = read(sock, buffer, sizeof(buffer));
        if (len <= 0) {
            /* Disconnect case */
            disconnect();
            rMut.unlock();
            exit(EXIT_SUCCESS);
            break;
        }

        cout<<"Recived text:"<<buffer<<endl;
        rMut.unlock();
        this_thread::sleep_for(200ms);
    }
}

void TcpClient::writeThread() {

    while (!stopThreads.load()) {
        wMut.lock();
        string inputBuffer{};
        cout<<"Write text:";
        cin >> inputBuffer;
        send(sock, inputBuffer.c_str(), inputBuffer.length(), 0);
        wMut.unlock();
        this_thread::sleep_for(200ms);
    }
}
