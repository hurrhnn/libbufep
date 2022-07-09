#ifndef LIBBUFEP_BUFEP_SOCKET_H
#define LIBBUFEP_BUFEP_SOCKET_H

#include "bufep_config.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef BUFEP_MS_WINDOWS
#include <stdbool.h>
#include <Ws2tcpip.h>
#else
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#endif

typedef struct bufep_socket_info {
    int sock_fd;
    struct sockaddr_in *sockaddr_in;
    int *socklen;
} bufep_socket_info_t;

#ifdef BUFEP_MS_WINDOWS
int bufep_socket_init_winsock();
#endif

int bufep_init_socket(char *address, int port, struct sockaddr_in *p_server_addr);

#endif //LIBBUFEP_BUFEP_SOCKET_H
