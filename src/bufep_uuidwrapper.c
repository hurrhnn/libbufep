#include "bufep_uuidwrapper.h"

#ifdef _UUID_H
#elif defined(_UUID_UUID_H)
void bufep_uuid_generate(bufep_uuid_t uuid) {
    uuid_generate_time(uuid);
}
void bufep_uuid_clear(bufep_uuid_t uuid) {
    uuid_clear(uuid);
}
int bufep_uuid_compare(bufep_uuid_t u1, bufep_uuid_t u2) {
    return uuid_compare(u1, u2);
}
void bufep_uuid_copy(bufep_uuid_t dst, bufep_uuid_t src) {
    uuid_copy(dst, src);

}
bool bufep_uuid_is_null(bufep_uuid_t uuid) {
    return uuid_is_null(uuid);
}

int bufep_uuid_parse(const bufep_uuid_string_t str_uuid, bufep_uuid_t uuid) {

    return uuid_parse(str_uuid, uuid);
}

void bufep_uuid_unparse_lower(const bufep_uuid_t uuid, bufep_uuid_string_t str_uuid) {
    uuid_unparse_lower(uuid, str_uuid);
}

void bufep_uuid_unparse_upper(const bufep_uuid_t uuid, bufep_uuid_string_t str_uuid) {
    uuid_unparse_upper(uuid, str_uuid);
}
#else
#endif
