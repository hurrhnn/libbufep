#include <bufep.h>

int main() {
    if (BUFEP_HEADER_LENGTH != sizeof(bufep_header_t) - sizeof(unsigned char *)) {
        printf("Header struct size: "
#ifdef BUFEP_MS_WINDOWS
               "%llu"
#else
               "%lu"
#endif
               ", struct alignment not applied.\n", sizeof(bufep_header_t) - sizeof(unsigned char *));
        return EXIT_FAILURE;
    }

    int status;
    unsigned char example_packet[] = "\x11\x03\x70\x00\x56\x9b\x5e\x65\xd2\x01\xed\x11\x89\x67\x00\xe0\x4c\x68\x07\x0e\x45\x06\x00\xe7\x28\x29\x65\x7a\x6f\x74\x67\x61\x79";
    bufep_header_t header;

    status = bufep_parse_header((unsigned char *) example_packet, 33, &header);
    if (status == BUFEP_FAILURE)
        return EXIT_FAILURE;

    BUFEP_DEBUG_MORE(GRN, "BUFEP Protocol version: 0x%x\n", header.protocol_version);

    bufep_uuid_string_t uuid;
    bufep_uuid_unparse_upper(header.client_identifier, uuid);
    BUFEP_DEBUG_MORE(GRN, "Client UUID: %s\n", uuid);

    BUFEP_DEBUG_MORE(GRN, "[%s] [Type]: %s - (%s)\n", uuid, (!header.rr_type ? "Request" : "Response"),
                     (!header.rr_error ? "NORMAL" : "ERROR"));
    BUFEP_DEBUG_MORE(GRN, "[%s] [Code]: %02d\n", uuid, header.rr_code);
    BUFEP_DEBUG_MORE(GRN, "[%s] [Data]: %s\n", uuid, header.payloads);
    return 0;
}
