#include "bufep.h"

void bufep_hello() {
    printf("Hello, World!\n");
}

int bufep_parse_header(unsigned char *raw, size_t raw_len, bufep_header_t *bufep_header) {
    if (raw_len < BUFEP_HEADER_LENGTH) {
        BUFEP_DEBUG_MORE(RED, "Header length mismatch!");
        return BUFEP_FAILURE;
    }

    memcpy(bufep_header, raw, BUFEP_HEADER_LENGTH);
    if (bufep_header->magic_header != BUFEP_MAGIC_HEADER) {
        BUFEP_DEBUG_MORE(RED, "Magic haeader mismatch!");
        return BUFEP_FAILURE;
    }

    if (bufep_header->protocol_version != BUFEP_PROTOCOL_VERSION) {
        BUFEP_DEBUG_MORE(RED, "Protocol version mismatch!");
        return BUFEP_FAILURE;
    }

    if (bufep_uuid_is_null(bufep_header->client_identifier)) {
        BUFEP_DEBUG_MORE(RED, "Client Identifier is empty!");
        return BUFEP_FAILURE;
    }

    const size_t fletcher_data_length = (BUFEP_HEADER_LENGTH_EXCLUDE_FLETCHER +
                                         bufep_header->data_size);
    const size_t fletcher_block_length = (fletcher_data_length % sizeof(uint16_t) == 0 ? fletcher_data_length /
                                                                                         sizeof(uint16_t) :
                                          (fletcher_data_length / sizeof(uint16_t)) + 1);
    const unsigned char fletcher_data[fletcher_block_length];
    memcpy((unsigned char *)fletcher_data, bufep_header, BUFEP_HEADER_LENGTH_EXCLUDE_FLETCHER);
    memcpy((unsigned char *)(fletcher_data + BUFEP_HEADER_LENGTH_EXCLUDE_FLETCHER), bufep_header->payloads, bufep_header->data_size);

    bufep_fletcher_data_t fletcher_block[fletcher_block_length];

    memset(&fletcher_block[fletcher_block_length - 1], 0x0, sizeof(uint16_t));
    for (int i = 0; i < fletcher_block_length; i++)
        memcpy(&fletcher_block[i], bufep_header->payloads + (i * sizeof(uint16_t)), sizeof(uint16_t));

    if(bufep_fletcher((bufep_fletcher_data_t *) fletcher_data, fletcher_data_length, BUFEP_FLETCHER_BIT) != bufep_header->fletcher_32) {
        BUFEP_DEBUG_MORE(RED, "Fletcher checksum mismatch!");
        return BUFEP_FAILURE;
    }

    return BUFEP_SUCCESS;
}
