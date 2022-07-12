#include <bufep.h>

int main() {
    const char *test_vectors[] = {"abcde", "abcdef", "abcdefgh", "Hello World...",
                                  "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus eros lectus, vulputate vel tellus quis, congue elementum eros. Nam ut bibendum urna, vel venenatis erat. Mauris lacus leo, convallis nec ornare non, congue vel est. Proin ultricies mi et leo lacinia vulputate. Nam quis consectetur orci. Integer ut nisi auctor, mollis turpis in, dapibus dui. Nullam lobortis lacinia tortor et ultrices."};
    const bufep_fletcher_checksum_t checksums[] = {0xF04FC729, 0x56502D2A, 0xEBE19591, 0x7F5C2A80, 0x524FB9A2};

    for (int i = 0; i < sizeof(test_vectors) / 8; i++) {
        bufep_fletcher_checksum_t checksum = bufep_fletcher((const bufep_fletcher_data_t *) test_vectors[i],
                                                            strlen(test_vectors[i]), BUFEP_FLETCHER_BIT);
        printf("\n[%d]: \"%s\"", i + 1, test_vectors[i]);
        if (checksum == checksums[i])
            printf("\n[%d]: calculated checksum = 0x%08X, checksum match.\n", i + 1, checksum);
        else
            printf("\n[%d]:  calculated checksum = 0x%08X, checksum mismatch!\n", i + 1, checksum);
    }
}
