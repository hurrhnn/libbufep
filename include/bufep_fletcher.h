#ifndef LIBBUFEP_BUFEP_FLETCHER_H
#define LIBBUFEP_BUFEP_FLETCHER_H

#include <stdint.h>
#include <stddef.h>

uint32_t bufep_fletcher32(const uint16_t *data, size_t len);

#endif //LIBBUFEP_BUFEP_FLETCHER_H
