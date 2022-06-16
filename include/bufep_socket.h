#ifndef LIBBUFEP_BUFEP_SOCKET_H
#define LIBBUFEP_BUFEP_SOCKET_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

typedef struct bufep_socket_info {
    int sock_fd;
    struct sockaddr_in *sockaddr_in;
    int *socklen;
} bufep_socket_info_t;

int bufep_init_socket(char *address, int port, struct sockaddr_in *p_server_addr);

#endif //LIBBUFEP_BUFEP_SOCKET_H
