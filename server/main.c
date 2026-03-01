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
    printf("socket was bound successfully\n");
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
    printf("Client connected\n");

    char buffer[1024];
    while (true) {
        ssize_t recvAmount = recv(clientSocketFD, buffer, sizeof(buffer), 0);
        if (recvAmount > 0) {
            buffer[recvAmount] = '\0';
            printf("%s", buffer);
        }
        else if (recvAmount == 0) {
            printf("Client disconnected\n");
            break;
        }
        else {
            perror("recv");
            break;
        }
    }
    printf("File closed\n");
    close(clientSocketFD);
    close(serverSocketFD);
    return 0;
}