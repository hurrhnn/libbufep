// A simple UDP server-side implementation.

#include <bufep.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

void signal_handler() {
    exit(BUFEP_SUCCESS);
}

int main(int argc, char **argv) {
    uint16_t port;

    if (argc < 2) {
        printf("Usage: %s [Port]\n", argv[0]);
        printf("Test suite arguments are missing! defaulting to [38450].\n");
        port = 38450;
    } else {
        if ((port = (strtol(argv[1], NULL, 10))) == EINVAL) {
            perror("Invalid Port number");
            return EXIT_FAILURE;
        }
    }

    int sock_fd;
    char buffer[65536];
    struct sockaddr_in server_addr, client_addr;
    memset(&client_addr, 0, sizeof(client_addr));

    if ((sock_fd = bufep_socket_init_server(
#ifdef BUFEP_MS_WINDOWS
    (u_short)
#endif
        htons(port), &server_addr)) < 0) {
        perror("socket creation failed");
        return EXIT_FAILURE;
    }

    signal(SIGALRM, signal_handler);
    printf("[*] Listening on 0.0.0.0:%hu...\n", port);
    while (1) {
        alarm(5);
        socklen_t socklen = sizeof(client_addr);
        ssize_t n;

        n = recvfrom(sock_fd, (char*)buffer, 65536,
#ifdef BUFEP_MS_WINDOWS
            0,
#else
            MSG_WAITALL,
#endif
            (struct sockaddr *) &client_addr, &socklen);
        n += 0x1c;

        sprintf(buffer, "Received %zd bytes from %s:%d", n, inet_ntoa(client_addr.sin_addr),
                ntohs(client_addr.sin_port));
        printf("[*] %s\n", buffer);
        sendto(sock_fd, (const char *) buffer, (int) strlen(buffer), 0, (const struct sockaddr *) &client_addr, socklen);
    }
}
