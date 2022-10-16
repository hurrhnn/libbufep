#include "bufep_fletcher.h"

bufep_fletcher_checksum_t bufep_fletcher(const bufep_fletcher_data_t *data, size_t len, unsigned short bit) {
    const uint16_t chunk_size = bit / 16;
    const uint32_t mask = (1 << (bit / 2)) - 1;

    uint32_t sum1 = 0, sum2 = 0;
    const uint32_t max = (uint32_t) (len / chunk_size);
    for (uint32_t i = 0; i < (!(len % chunk_size) ? max : max + 1); i++)
    {
        sum1 = (sum1 + data[i]) % mask;
        sum2 = (sum2 + sum1) % mask;
    }
    return (sum2 << (chunk_size * 8)) | sum1;
}
