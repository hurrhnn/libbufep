// A simple UDP server-side implementation.

#include <bufep.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if(argc < 2)
    {
        printf("Usage: %s [Port]\n", argv[0]);
        return EXIT_SUCCESS;
    }

    if(strtol(argv[1], NULL, 10) == EINVAL)
    {
        perror("Invalid Port number");
        return EXIT_FAILURE;
    }

    int sock_fd;
    char buffer[65536];
    struct sockaddr_in server_addr, client_addr;

    if ( (sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        return EXIT_FAILURE;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(strtol(argv[1], NULL, 10));

    if (bind(sock_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("[*] Listening on 0.0.0.0:%ld...\n", strtol(argv[1], NULL, 10));
    while (1) {
        socklen_t socklen = sizeof(client_addr);
        ssize_t n;

        n = recvfrom(sock_fd, (char *)buffer, 65536, MSG_WAITALL, ( struct sockaddr *) &client_addr, &socklen);
        n += 0x1c;

        sprintf(buffer, "Received %zd bytes from %s:%d", n, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        printf("[*] %s\n", buffer);
        sendto(sock_fd, (const char *)buffer, strlen(buffer), 0, (const struct sockaddr *) &client_addr, socklen);
    }
}
