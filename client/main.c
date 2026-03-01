#include "netlib.h"

int main() {
    
    int socketFD = createTCPIPv4Socket();
    struct sockaddr_in address = createIPv4Address("127.0.0.1", 2000);
    
    if (connect(socketFD, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("connect");
        close(socketFD);
        return 1;
    }

    printf("Connection was successful!\n");

    char* line = NULL;
    size_t lineSize = 0;
    printf("To stop input, type \"exit\" on a separate line\n");
    printf("---------------------------------------------\n");
    while(true) {
        ssize_t charCount = getline(&line, &lineSize, stdin);
        if (charCount == -1) {
            perror("getline");
            break;
        }

        if (strcmp(line, "exit\n") == 0) {
            break;
        }

        ssize_t sendResult = send(socketFD, line, charCount, 0);

        if (sendResult == -1) {
            perror("send");
            break;
        }
    }
    free(line);
    
    close(socketFD);
    printf("File closed\n");
    return 0;
}