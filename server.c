#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT "3490"

int main() {
    socket(AF_INET, SOCK_STREAM, 0);
}