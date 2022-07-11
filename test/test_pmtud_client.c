// A simple Path MTU Discovery implementation of UDP sockets.

#include <bufep.h>

int main(int argc, char **argv) {
    if(argc < 3)
    {
        printf("Usage: %s [Address] [Port]\n", argv[0]);
        return EXIT_SUCCESS;
    }

    if(strtol(argv[2], NULL, 10) == EINVAL)
    {
        perror("Invalid Port number");
        return EXIT_FAILURE;
    }

    bufep_hello();
    char *address = argv[1];
    uint16_t port = (uint16_t) strtol(argv[2], NULL, 10);

    bufep_socket_info_t server_info;
    struct sockaddr_in server_addr;
    server_info.sock_fd = bufep_socket_init_client(address, port, &server_addr);

    int server_socklen = sizeof(server_addr);
    server_info.socklen = &server_socklen;
    server_info.sockaddr_in = &server_addr;

    printf("%s connection's PMTU: %d\n", address, bufep_pmtud(&server_info));
}
