#include "bufep_uuidwrapper.h"

#if defined(BUFEP_MS_WINDOWS)
void bufep_uuid_convert(bool mode, UUID* native, bufep_uuid_t wrapped) {
    int offset = 0;
    if (!mode)
    {
        memcpy(wrapped, &(native->Data1), sizeof(native->Data1));
        memcpy(wrapped + (offset += sizeof(native->Data1)), &(native->Data2), sizeof(native->Data2));
        memcpy(wrapped + (offset += sizeof(native->Data2)), &(native->Data3), sizeof(native->Data3));
        memcpy(wrapped + (offset += sizeof(native->Data3)), &(native->Data4), sizeof(native->Data4));
    }
    else {
        memcpy(&(native->Data1), wrapped, sizeof(native->Data1));
        memcpy(&(native->Data2), wrapped + (offset += sizeof(native->Data1)), sizeof(native->Data2));
        memcpy(&(native->Data3), wrapped + (offset += sizeof(native->Data2)), sizeof(native->Data3));
        memcpy(&(native->Data4), wrapped + (offset += sizeof(native->Data3)), sizeof(native->Data4));
    }
}

void bufep_uuid_generate(bufep_uuid_t uuid) {
    UUID uuid_t;
    UuidCreateSequential(&uuid_t);
    bufep_uuid_convert(0, &uuid_t, uuid);
}
void bufep_uuid_clear(bufep_uuid_t uuid) {
    int code;
    UUID uuid_t;
    code = UuidCreateNil(&uuid_t);

    if(code == RPC_S_OK)
        bufep_uuid_convert(0, &uuid_t, uuid);
}

int bufep_uuid_compare(bufep_uuid_t u1, bufep_uuid_t u2) {
    int code, result;
    UUID u1_t, u2_t;
    bufep_uuid_convert(1, &u1_t, u1);
    bufep_uuid_convert(1, &u2_t, u2);
    result = UuidCompare(&u1_t, &u2_t, &code);

    if (code != RPC_S_OK)
        return BUFEP_FAILURE;
    else
        return result;
}
void bufep_uuid_copy(bufep_uuid_t dst, bufep_uuid_t src) {
    memcpy(dst, src, sizeof(bufep_uuid_t));
}

int bufep_uuid_is_null(bufep_uuid_t uuid) {
    int code, result;
    UUID uuid_t;
    bufep_uuid_convert(1, &uuid_t, uuid);
    result = UuidIsNil(&uuid_t, &code);

    if (code != RPC_S_OK)
        return BUFEP_FAILURE;
    else
        return result;
}

int bufep_uuid_parse(const bufep_uuid_string_t str_uuid, bufep_uuid_t uuid) {
    UUID uuid_t;
    bufep_uuid_convert(1, &uuid_t, uuid);
    return UuidFromStringA((char *) str_uuid, &uuid_t);
}

void bufep_uuid_unparse_lower(const bufep_uuid_t uuid, bufep_uuid_string_t str_uuid) {
    int code;
    UUID uuid_t;
    RPC_CSTR uuid_string_t;
    bufep_uuid_convert(1, &uuid_t, (unsigned char *) uuid);
    code = UuidToStringA(&uuid_t, &uuid_string_t);

    if(code == RPC_S_OK)
        strcpy(str_uuid, uuid_string_t);

    RpcStringFreeA(&uuid_string_t);
}

void bufep_uuid_unparse_upper(const bufep_uuid_t uuid, bufep_uuid_string_t str_uuid) {
    int code;
    UUID uuid_t;
    RPC_CSTR uuid_string_t;
    bufep_uuid_convert(1, &uuid_t, (unsigned char *) uuid);
    code = UuidToStringA(&uuid_t, &uuid_string_t);

    if (code == RPC_S_OK) {
        strcpy(str_uuid, uuid_string_t);
        CharUpperA(str_uuid);
    }

    RpcStringFreeA(&uuid_string_t);
}

#elif defined(_UUID_H) || defined(_UUID_UUID_H) || defined(_UL_LIBUUID_UUID_H)
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

int bufep_uuid_is_null(bufep_uuid_t uuid) {
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
#endif
