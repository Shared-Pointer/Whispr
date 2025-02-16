#include "../include/server_socket.h"

#include <iostream>
ServerSocket::ServerSocket(int port) {
    if(!Socket::create()) {
        std::cout << "Server socket has failed to create \n";
    }

    if(!Socket::bind(port)) {
        std::cout << "Server socket has failed to bind \n";
    }

    if(!Socket::listen()) {
        std::cout << "Server socket has failed to listen \n";
    }
}

ServerSocket::~ServerSocket() {}

const ServerSocket& ServerSocket::operator<<(const std::string& s const) {
    if(!Socket::send(s)) {
        std::cout << "Failed to write to socket \n";
    }
    return *this;
}

const ServerSocket& ServerSocket::operator>>(const std::string& s const) {
    if(!Socket::recv(s)) {
        std::cout << "Failed to read from socket \n";
    }
    return *this;
}

void ServerSocket::accept(ServerSocket& sock) {
    if(!Socket::accept(sock)) {
        std::cout << "Failed to accept the socket \n";
    }
}