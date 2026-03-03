#include "netlib.h"

int main() {
    int serverSocketFD = createTCPIPv4Socket();
    struct sockaddr_in serverAddress = createIPv4Address("", 2000);
    int opt = 1;
    if (setsockopt(serverSocketFD, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        close(serverSocketFD);
        return 1;
    }
    
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
    
    fd_set masterSet;
    fd_set readSet;

    FD_ZERO(&masterSet);
    FD_SET(serverSocketFD, &masterSet);

    int maxFD = serverSocketFD;

    while(true) {
        readSet = masterSet;
        int activity = select(maxFD + 1, &readSet, NULL, NULL, NULL);

        if (activity < 0) {
            perror("select");
            break;
        }

        if (FD_ISSET(serverSocketFD, &readSet)) {

            struct sockaddr_in clientAddress;
            socklen_t clientLen = sizeof(clientAddress);

            int clientFD = accept(serverSocketFD, (struct sockaddr*)&clientAddress, &clientLen);

            if (clientFD >= 0) {
                FD_SET(clientFD, &masterSet);

                if (clientFD > maxFD)
                    maxFD = clientFD;

                printf("New client connected: %d\n", clientFD);
            }
        }

        for (int i = 0; i <= maxFD; i++) {
            if (i != serverSocketFD && FD_ISSET(i, &readSet)) {

                char buffer[1024];
                ssize_t recvAmount = recv(i, buffer, sizeof(buffer) - 1, 0);

                if (recvAmount > 0) {
                    buffer[recvAmount] = '\0';
                    printf("Client %d: %s", i, buffer);
                }
                else if (recvAmount == 0) {
                    printf("Client %d disconnected\n", i);
                    close(i);
                    FD_CLR(i, &masterSet);
                }
                else {
                    perror("recv");
                    close(i);
                    FD_CLR(i, &masterSet);
                }
            }
        }
    }

    for (int i = 0; i <= maxFD; i++) {
        close(i);
    }
    printf("File closed\n");
    return 0;
}