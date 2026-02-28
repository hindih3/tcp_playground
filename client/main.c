#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "netlib.h"

int main() {
    
    int fd = createTCPIPv4Socket();
    struct sockaddr_in address = createIPv4Address("127.0.0.1", 2000);
    
    int result = connect(fd, (struct sockaddr*)&address, sizeof(address));

    if(result == 0) {
        printf("Connection was successful!\n");
    } else {
        perror("connect");
        return 1;
    }

    char* message;
    message = "GET / HTTP/1.1\r\nHost: google.com\r\nConnection: close\r\n\r\n";
    send(fd, message, strlen(message), 0);

    char buffer[1024];
    recv(fd, buffer, sizeof(buffer), 0);
    printf("Response was %s\n", buffer);
    
    close(fd);
    printf("File closed\n");
    return 0;
}