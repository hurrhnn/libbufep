#include <bufep.h>

int main() {
    printf("Header struct size: %lu, %s\n", sizeof(bufep_header_t) - sizeof(unsigned char *),
           BUFEP_HEADER_LENGTH == sizeof(bufep_header_t) - sizeof(unsigned char *) ? "struct alignment applied."
                                                                                   : "struct alignment not applied.");
    return 0;
}
