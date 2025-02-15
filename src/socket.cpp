#include "../include/socket.h"

#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include <iostream>

Socket::Socket()
    : m_sock(-1)  // -1 means INVALID SOCKET
{
    memset(&m_addr, 0, sizeof(m_addr));  // zeroing m_sock
}

Socket::~Socket() {
    if (is_valid())       // checks if m_sock != -1
        ::close(m_sock);  // if it exists we close this
}

bool Socket::create() {
    // AF_NET means ipv4
    // SOCK_STREAM means TCP
    // 0 is a default protocol for TCP
    m_sock = socket(AF_INET, SOCK_STREAM, 0);

    if (!is_valid()) return false;  // check if this socket is a nice one

    int on = 1;
    // seting options for socket in order to reuse socket
    if (setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&on,
                   sizeof(on)) == -1)
        return false;

    return true;
}

bool Socket::bind(const int port) {
    if (!is_valid()) {
        return false;
    }

    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = INADDR_ANY;  // any IP address
    m_addr.sin_port = htons(port);        // convert port to network standard

    // real binding here
    int bind_return =
        ::bind(m_sock, (struct sockaddr *)&m_addr, sizeof(m_addr));

    if (bind_return == -1) {
        return false;
    }

    return true;
}

bool Socket::listen() const {
    if (!is_valid()) return false;

    int listen_return = ::listen(m_sock, MAX_CONNECTIONS);

    if (listen_return == -1) return false;

    return true;
}

bool Socket::accept(Socket &new_socket) const {
    int addr_length = sizeof(m_addr);
    new_socket.m_sock =
        ::accept(m_sock, (sockaddr *)&m_addr, (socklen_t *)&addr_length);

    if (new_socket.m_sock <= 0) return false;

    return true;
}

bool Socket::send(const std::string s) const {
    int status = ::send(m_sock, s.c_str(), s.size(), MSG_NOSIGNAL);

    if (status == -1) return false;

    return true;
}

int Socket::recv(std::string &s) const {
    char buf[MAX_DATA_RECIEVED + 1];

    s = "";

    memset(buf, 0, MAX_DATA_RECIEVED + 1);

    int status = ::recv(m_sock, buf, MAX_DATA_RECIEVED, 0);

    if (status == -1) {
        std::cout << "status == -1   errno == " << errno
                  << "  in Socket::recv\n";
        return 0;
    } else if (status == 0)
        return 0;
    else {
        s = buf;
        return status;
    }
}

bool Socket::connect(const std::string host, const int port) {
    if (!is_valid()) return false;

    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(port);

    int status = inet_pton(AF_INET, host.c_str(), &m_addr.sin_addr);

    if (errno == EAFNOSUPPORT) return false;

    status = ::connect(m_sock, (sockaddr *)&m_addr, sizeof(m_addr));

    if (status == 0)
        return true;
    else
        return false;
}

void Socket::set_non_blocking(const bool b) {
    int opts;

    opts = fcntl(m_sock, F_GETFL);  // get descriptor flags

    if (opts < 0) return;

    if (b)
        opts = (opts | O_NONBLOCK);
    else
        opts = (opts & ~O_NONBLOCK);

    fcntl(m_sock, F_SETFL, opts);
}
