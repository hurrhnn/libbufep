#include "bufep_socket.h"

#ifdef BUFEP_MS_WINDOWS
static bool bufep_is_winsock_initiated = false;

int bufep_socket_init_winsock() {
    if (!bufep_is_winsock_initiated) {
        bufep_is_winsock_initiated = true;

        int iResult;
        WSADATA wsaData;

        // Initialize Winsock
        if ((iResult = WSAStartup(MAKEWORD(2,2), &wsaData)) != 0) {
            printf("WSAStartup failed: %d\n", iResult);
            return BUFEP_FAILURE;
        }
    }
    return BUFEP_SUCCESS;
}
#endif

int bufep_socket_init_client(char *address, int port, struct sockaddr_in *p_server_addr) {
#ifdef BUFEP_MS_WINDOWS
    if(bufep_socket_init_winsock() == BUFEP_FAILURE)
        return BUFEP_FAILURE;
#endif
    char resolved_address[0xF];

    int sock_fd, val, timeout_limit = 1000;
#ifdef BUFEP_MS_WINDOWS
    int timeout = 1000;
#else
    struct timeval timeout = { timeout_limit / 1000, (timeout_limit % 1000) * 1000 };
#endif

    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("Error in socket creation");
        return BUFEP_FAILURE;
    }

    if (setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) != 0) // set timeout
    {
        perror("Error in setsockopt(recv_timeout/udp)");
        return BUFEP_FAILURE;
    }

#ifdef BUFEP_MS_WINDOWS
    if (setsockopt(sock_fd, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout)) != 0) // set timeout
    {
        perror("Error in setsockopt(send_timeout/udp)");
        return BUFEP_FAILURE;
    }
#endif

#ifdef IP_MTU_DISCOVER
    val = IP_PMTUDISC_DO;
    if (setsockopt(sock_fd, IPPROTO_IP, IP_MTU_DISCOVER, &val, sizeof(val)) != 0)
    {
        perror("Error in setsockopt(IP_MTU_DISCOVER)");
        return BUFEP_FAILURE;
    }
#else
    val = 0x1;
    if (setsockopt(sock_fd, IPPROTO_IP, IP_DONTFRAG, &val, sizeof(val)) != 0)
    {
        perror("Error in setsockopt(IP_DONTFRAG)");
        return BUFEP_FAILURE;
    }
#endif

    memset(p_server_addr, 0, sizeof(*p_server_addr));
    p_server_addr->sin_family = AF_INET; // IPv4
    p_server_addr->sin_port = htons((uint16_t) port);

    struct hostent *hostent;
    struct in_addr **addr_list;

    if ((hostent = gethostbyname(address)) == NULL) {
        fprintf(stderr, "The connection could not be resolved to %s.\n", address);
        return BUFEP_FAILURE;
    } else {
        addr_list = (struct in_addr **) hostent->h_addr_list;
        strcpy(resolved_address, inet_ntoa(*addr_list[0]));
    }

    if (!inet_pton(AF_INET, resolved_address, &p_server_addr->sin_addr)) {
        perror("Could not convert the internet host address");
        return BUFEP_FAILURE;
    }

    return sock_fd;
}

int bufep_socket_init_server(int port, struct sockaddr_in *p_server_addr) {
#ifdef BUFEP_MS_WINDOWS
    if (bufep_socket_init_winsock() == BUFEP_FAILURE)
        return BUFEP_FAILURE;
#endif
    int sock_fd;

    if ( (sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        return EXIT_FAILURE;
    }

    memset(p_server_addr, 0, sizeof(*p_server_addr));

    p_server_addr->sin_family = AF_INET; // IPv4
    p_server_addr->sin_addr.s_addr = INADDR_ANY;
    p_server_addr->sin_port = port;

    if (bind(sock_fd, (const struct sockaddr *)p_server_addr, sizeof(*p_server_addr)) < 0 )
    {
        perror("bind failed");
        return BUFEP_FAILURE;
    }
    return sock_fd;
}
