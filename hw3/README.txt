This project is a C++ home wrok 2 (Tcp/ip client-server) project with cmake.

Task description:
Implement a program for Linux using "socket.h" functionality that allows several clients to connect to it over TCP and send messages. If the client sends 'hello' message, the server should respond 'world'. If any other message is sent, the server should send it back to the client without changing it. Implement a client that can connect to the server described earlier and send messages to it.

The client and server should be able to maintain a TCP connection and exchange messages until an explicit 'disconnect' command is received from the user.


Author: Oleksandr Mordyk
Build dependencies:
> C++ compiler (g++ 9.4.0+)
> cmake

Run-time dependencies:
OS: Linux
Library: pthread.


Structure:
.
├── CMakeLists.txt
├── inc
│   ├── client.h
│   └── server.h
├── README.txt
└── src
    ├── client.cpp
    ├── main.cpp
    └── server.cpp



Building and usage:
Build by making a build directory (i.e. build/), run cmake in that folder, and then use make.

Example:
> mkdir build && cd build
> cmake ..
> make
> ./hw_3 <server/client>