#ifndef LIBBUFEP_BUFEP_UUIDWRAPPER_H
#define LIBBUFEP_BUFEP_UUIDWRAPPER_H

#include "bufep_config.h"
#include <stdbool.h>

#ifdef BUFEP_MS_WINDOWS
#include <rpc.h>
#else
#include <uuid/uuid.h>
#endif

typedef unsigned char bufep_uuid_t[16];
typedef char   bufep_uuid_string_t[37];

#ifdef BUFEP_MS_WINDOWS
void bufep_uuid_convert(bool mode, UUID* native, bufep_uuid_t wrapped);
#endif

void bufep_uuid_generate(bufep_uuid_t uuid);

void bufep_uuid_clear(bufep_uuid_t uuid);

int bufep_uuid_compare(bufep_uuid_t u1, bufep_uuid_t u2);

void bufep_uuid_copy(bufep_uuid_t dst, bufep_uuid_t src);

int bufep_uuid_is_null(bufep_uuid_t uuid);

int bufep_uuid_parse(const bufep_uuid_string_t str_uuid, bufep_uuid_t uuid);

void bufep_uuid_unparse_lower(const bufep_uuid_t uuid, bufep_uuid_string_t str_uuid);

void bufep_uuid_unparse_upper(const bufep_uuid_t uuid, bufep_uuid_string_t str_uuid);

#endif //LIBBUFEP_BUFEP_UUIDWRAPPER_H
