#include "netlib.h"

int main() {
    
    int socketFD = createTCPIPv4Socket();
    struct sockaddr_in address = createIPv4Address("127.0.0.1", 2000);
    
    if (connect(socketFD, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("connect");
        close(socketFD);
        return 1;
    }

    printf("Connection was successful. Type \"exit\" on a separate line to terminate\n");

    char* line = NULL;
    size_t lineSize = 0;

    while(true) {
        int maxFD = socketFD > STDIN_FILENO ? socketFD : STDIN_FILENO;
        fd_set readSet; //initialize set of file descriptors
        FD_ZERO(&readSet); //zero-assign set to avoid garbage values

        FD_SET(STDIN_FILENO, &readSet); //add keyboard input to set (STDIN_FILENO stands for 0 - keyboard input)
        FD_SET(socketFD, &readSet); //add socket to set

        int activity = select(maxFD + 1, &readSet, NULL, NULL, NULL); //put program to sleep until kernel detects activity in readSet

        if (activity < 0) {
            perror("select");
            break;
        }

        if (FD_ISSET(STDIN_FILENO, &readSet)) { //check if keyboard input is ready
            ssize_t charCount = getline(&line, &lineSize, stdin);

            if (charCount <= 0) {
                break;
            }

            if (strcmp(line, "exit\n") == 0) {
                break;
            }

            ssize_t sent = send(socketFD, line, charCount, 0);
            if (sent < 0) {
                perror("send");
                break;
            }
        }

        if (FD_ISSET(socketFD, &readSet)) { //check if server input is ready
            char buffer[1024];

            ssize_t recvAmount = recv(socketFD, buffer, sizeof(buffer) - 1, 0);

            if (recvAmount > 0) {
                buffer[recvAmount] = '\0';
                printf("%s", buffer);
            }
            else if (recvAmount == 0) {
                printf("Server disconnected\n");
                break;
            }
            else {
                perror("recv");
                break;
            }
        }
    }
    close(socketFD);
    printf("File closed\n");
    return 0;
}