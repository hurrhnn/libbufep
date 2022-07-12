#ifndef LIBBUFEP_BUFEP_H
#define LIBBUFEP_BUFEP_H

#include "bufep_debug.h"
#include "bufep_fletcher.h"
#include "bufep_socket.h"
#include "bufep_pmtud.h"
#include "bufep_logger.h"
#include "bufep_uuidwrapper.h"

#include <stdio.h>

#define BUFEP_HEADER_LENGTH    0x1B
#define BUFEP_MAGIC_HEADER     0x700311
#define BUFEP_PROTOCOL_VERSION 0x0

#define BUFEP_HEADER_LENGTH_EXCLUDE_FLETCHER (0x1B - 0x04)

#ifdef BUFEP_MS_WINDOWS
#pragma pack(push, 1)
#endif
typedef struct {
    uint32_t magic_header: 24,
            protocol_version: 8;

    bufep_uuid_t client_identifier;

    uint8_t rr_type: 1,
            rr_error: 1,
            rr_code: 6;
    uint16_t data_size; /* NOTE: the size EXCLUDING header. */
    bufep_fletcher_checksum_t fletcher_32;

    unsigned char *payloads;
}
#ifndef BUFEP_MS_WINDOWS
__attribute__((aligned(1), packed))
#endif
bufep_header_t;
#ifdef BUFEP_MS_WINDOWS
#pragma pack(pop)
#endif

void bufep_hello();

int bufep_parse_header(unsigned char* raw, size_t raw_len, bufep_header_t *bufep_header);

#endif //LIBBUFEP_BUFEP_H
