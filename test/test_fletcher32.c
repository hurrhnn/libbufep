#include <bufep.h>

int main() {
    const char *test_vectors[] = {"abcde", "abcdef", "abcdefgh"};
    const bufep_fletcher_checksum_t checksums[] = {0xF04FC729, 0x56502D2A, 0xEBE19591};

    for (int i = 0; i < sizeof(test_vectors) / 8; i++) {
        bufep_fletcher_checksum_t checksum = bufep_fletcher32((const bufep_fletcher_data_t *) test_vectors[i],
                                                              strlen(test_vectors[i]));
        printf("[%d]: \"%s\", calculated checksum = 0x%08X, ", i + 1, test_vectors[i], checksum);
        if (checksum == checksums[i])
            printf("checksum match.\n");
        else
            printf("checksum mismatch!!!\n");
    }
}
