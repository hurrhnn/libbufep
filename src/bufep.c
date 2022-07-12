#include "bufep.h"

void bufep_hello() {
    printf("Hello, World!\n");
}

int bufep_parse_header(unsigned char *raw, size_t raw_len, bufep_header_t *bufep_header) {
    if (raw_len < BUFEP_HEADER_LENGTH) {
        BUFEP_DEBUG_MORE(RED, "Header length mismatch!\n");
        return BUFEP_FAILURE;
    }

    memcpy(bufep_header, raw, BUFEP_HEADER_LENGTH);
    if (bufep_header->magic_header != BUFEP_MAGIC_HEADER) {
        BUFEP_DEBUG_MORE(RED, "Magic header mismatch!\n");
        return BUFEP_FAILURE;
    }

    if (bufep_header->protocol_version != BUFEP_PROTOCOL_VERSION) {
        BUFEP_DEBUG_MORE(RED, "Protocol version mismatch!\n");
        return BUFEP_FAILURE;
    }

    if (bufep_uuid_is_null(bufep_header->client_identifier)) {
        BUFEP_DEBUG_MORE(RED, "Client Identifier is empty!\n");
        return BUFEP_FAILURE;
    }

    bufep_header->payloads = raw + BUFEP_HEADER_LENGTH;

    const size_t fletcher_data_length = ((BUFEP_FLETCHER_LENGTH(bufep_header->data_size) % 2) ?
                                         BUFEP_FLETCHER_LENGTH(bufep_header->data_size) + 0x1 :
                                         (BUFEP_FLETCHER_LENGTH(bufep_header->data_size)));
    const unsigned char
#ifdef BUFEP_MS_WINDOWS
    *fletcher_data = HeapAlloc(GetProcessHeap(), 0, fletcher_data_length);
if (fletcher_data == NULL)
    return BUFEP_FAILURE;
#else
            fletcher_data[fletcher_data_length];
#endif
    memset((unsigned char *) fletcher_data, 0x0, fletcher_data_length);
    memcpy((unsigned char *) fletcher_data, raw + 0x04, BUFEP_HEADER_LENGTH_EXCLUDE_FLETCHER - 0x04);
    memcpy((unsigned char *) (fletcher_data + BUFEP_HEADER_LENGTH_EXCLUDE_FLETCHER - 0x04), bufep_header->payloads,
           bufep_header->data_size);

    if (bufep_fletcher((bufep_fletcher_data_t *) fletcher_data, fletcher_data_length, BUFEP_FLETCHER_BIT) !=
        bufep_header->fletcher_32) {
        BUFEP_DEBUG_MORE(RED, "Fletcher checksum mismatch!\n");
        return BUFEP_FAILURE;
    }

#ifdef BUFEP_MS_WINDOWS
    HeapFree(GetProcessHeap(), 0, fletcher_data);
    HeapFree(GetProcessHeap(), 0, fletcher_block);
#endif
    return BUFEP_SUCCESS;
}
