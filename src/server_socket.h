#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

class Socket {
public:
  Socket();
  ~Socket();
};

#endif