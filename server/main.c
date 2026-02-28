#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "netlib.h"
int main() {
    int serverSocketFD = createTCPIPv4Socket();
    struct sockaddr_in serverAddress = createIPv4Address("", 2000);
}