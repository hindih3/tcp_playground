#include "netlib.h"

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int createTCPIPv4Socket(void) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
        perror("socket");
    return fd;
}

struct sockaddr_in createIPv4Address(const char* ip, int port) {
    struct sockaddr_in address = {0};

    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if (ip == NULL || ip[0] == '\0')
        address.sin_addr.s_addr = INADDR_ANY;
    else
        inet_pton(AF_INET, ip, &address.sin_addr);

    return address;
}

struct acceptedSocket {
    int socketFD;
    struct sockaddr_in address;
    int error;
    bool success;
};

struct acceptedSocket* acceptConnection(int serverSocketFD) {

}
