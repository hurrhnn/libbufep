#ifndef LIBBUFEP_BUFEP_PMTUD_H
#define LIBBUFEP_BUFEP_PMTUD_H

#include "bufep_socket.h"

#include <netinet/in.h>
#include <errno.h>

int bufep_pmtud(bufep_socket_info_t *server_info);

#endif //LIBBUFEP_BUFEP_PMTUD_H
