#ifndef SOCKET_H
#define SOCKET_H

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <string>

const int MAX_HOSTNAME = 200;
const int MAX_CONNECTIONS = 2;
// In bytes, how much data can we recieve in a single operation
const int MAX_DATA_RECIEVED = 500;

class Socket {
   public:
    Socket();
    virtual ~Socket();

    bool create();                // create socket
    bool bind(const int port);    // bind socket to particular port
    bool listen() const;          // set socket to listen to conn
    bool accept(Socket &) const;  // accept connection from cli

    bool connect(
        const std::string host,
        const int port);  // connect (why we have this in server socket?,
                          // we don't need to connect to anything)
    bool send(const std::string) const;  // send data through socket

    int recv(std::string &) const;  // recieve data
    void set_non_blocking(
        const bool);  // set socket to non-blocking connections
    bool is_valid() const { return m_sock != -1; }  // checks if socket is valid

   private:
    int m_sock;
    sockaddr_in m_addr;
};

#endif