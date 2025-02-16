#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "socket.h"

class ServerSocket : private Socket {
    public:
        ServerSocket(int port);
        ServerSocket(){};
        virtual ~ServerSocket();

        //overloading operators for sending/receiving data
        const ServerSocket& operator << (const std::string&) const;
        const ServerSocket& operator >> (const std::string&) const;

        void accept(ServerSocket&);
};

#endif