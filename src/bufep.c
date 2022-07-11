#include "bufep.h"

void bufep_hello() {
    printf("Hello, World!\n");
}

int bufep_parse_header(unsigned char* raw, size_t raw_len, bufep_header_t *bufep_header) {
    if(raw_len < BUFEP_HEADER_LENGTH)
    {
        BUFEP_DEBUG_MORE(RED, "Header length mismatch!");
        return BUFEP_FAILURE;
    }

    memcpy(bufep_header, raw, BUFEP_HEADER_LENGTH);
    if(bufep_header->magic_header != BUFEP_MAGIC_HEADER)
    {
        BUFEP_DEBUG_MORE(RED, "Magic haeader mismatch!");
        return BUFEP_FAILURE;
    }

    if(bufep_header->protocol_version != BUFEP_PROTOCOL_VERSION)
    {
        BUFEP_DEBUG_MORE(RED, "Protocol version mismatch!");
        return BUFEP_FAILURE;
    }

    if(bufep_uuid_is_null(bufep_header->client_identifier))
    {
        BUFEP_DEBUG_MORE(RED, "Client Identifier is empty!");
        return BUFEP_FAILURE;
    }

    if(bufep_fletcher32((bufep_fletcher_data_t *) bufep_header->client_identifier, sizeof(bufep_uuid_t)) != bufep_header->fletcher_32) {
        BUFEP_DEBUG_MORE(RED, "Fletcher checksum mismatch!");
        return BUFEP_FAILURE;
    }

    return BUFEP_SUCCESS;
}
