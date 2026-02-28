#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "netlib.h"

int main() {
    int serverSocketFD = createTCPIPv4Socket();
    struct sockaddr_in serverAddress = createIPv4Address("", 2000);
    int opt = 1;
    setsockopt(serverSocketFD, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    if (bind(serverSocketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("bind");
        close(serverSocketFD);
        return 1;
    }
    printf("socket was bound successfully!\n");
    if (listen(serverSocketFD, 10) < 0) {
        perror("listen");
        close(serverSocketFD);
        return 1;
    }
    
    struct sockaddr_in clientAddress;
    socklen_t clientLen = sizeof(clientAddress);

    int clientSocketFD = accept(serverSocketFD, (struct sockaddr*)&clientAddress, &clientLen);
    if (clientSocketFD < 0) {
        perror("socket");
        close(serverSocketFD);
        return 1;
    }
    printf("Client connected!\n");
    char buffer[1024];
    recv(clientSocketFD, buffer, sizeof(buffer), 0);
    printf("Response was %s\n", buffer);
    
    close(clientSocketFD);
    close(serverSocketFD);
    return 0;
}