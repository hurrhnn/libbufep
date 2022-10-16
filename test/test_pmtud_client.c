// A simple Path MTU Discovery implementation of UDP sockets.

#include <bufep.h>

int main(int argc, char **argv) {
    char *address;
    uint16_t port;

    if(argc < 3)
    {
        printf("Usage: %s [Address] [Port]\n", argv[0]);
        printf("Test suite arguments are missing! defaults to [127.0.0.1] [38450].\n");
        address = "127.0.0.1";
        port = 38450;
    } else {
        address = argv[1];
        if((port = strtol(argv[2], NULL, 10)) == EINVAL)
        {
            perror("Invalid Port number");
            return EXIT_FAILURE;
        }
    }

    bufep_socket_info_t server_info;
    struct sockaddr_in server_addr;
    server_info.sock_fd = bufep_socket_init_client(address, port, &server_addr);

    int server_socklen = sizeof(server_addr);
    server_info.socklen = &server_socklen;
    server_info.sockaddr_in = &server_addr;

    printf("%s connection's PMTU: %d\n", address, bufep_pmtud(&server_info));
}
