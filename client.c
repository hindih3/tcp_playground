#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT "3490"

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        return 1;
    }

    char* ip = "142.250.9.139"; // google
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_port = htons(80);
    address.sin_family = AF_INET;

    if (inet_pton(AF_INET, ip, &address.sin_addr) <= 0) {
        perror("inet_pton");
        return 1;
    }
    
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