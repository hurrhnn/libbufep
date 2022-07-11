#ifndef LIBBUFEP_BUFEP_FLETCHER32_H
#define LIBBUFEP_BUFEP_FLETCHER32_H

#include <stdint.h>
#include <stddef.h>

typedef uint16_t bufep_fletcher_data_t;
typedef uint32_t bufep_fletcher_checksum_t;

bufep_fletcher_checksum_t bufep_fletcher32(const bufep_fletcher_data_t *data, size_t len);

#endif //LIBBUFEP_BUFEP_FLETCHER32_H
