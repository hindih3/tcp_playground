#ifndef NETLIB_H
#define NETLIB_H

#include <netinet/in.h>

int createTCPIPv4Socket(void);
struct sockaddr_in createIPv4Address(const char* ip, int port);

#endif