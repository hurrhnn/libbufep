#ifndef LIBBUFEP_BUFEP_FLETCHER_H
#define LIBBUFEP_BUFEP_FLETCHER_H

#include <stdint.h>
#include <stddef.h>

#define BUFEP_FLETCHER_BIT 32

typedef uint16_t bufep_fletcher_data_t;
typedef uint32_t bufep_fletcher_checksum_t;

bufep_fletcher_checksum_t bufep_fletcher(const bufep_fletcher_data_t *data, size_t len, unsigned short bit);

#endif //LIBBUFEP_BUFEP_FLETCHER_H
