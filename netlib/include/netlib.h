#ifndef NETLIB_H
#define NETLIB_H

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>

struct acceptedSocket;
int createTCPIPv4Socket(void);
struct sockaddr_in createIPv4Address(const char* ip, int port);

#endif