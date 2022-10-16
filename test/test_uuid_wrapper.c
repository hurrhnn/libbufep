#include <bufep.h>

int main() {
    bufep_uuid_t test_uuid, copied_test_uuid;
    bufep_uuid_string_t test_uuid_str;
    bool is_uuid_null;

    bufep_uuid_generate(test_uuid);
    is_uuid_null = bufep_uuid_is_null(test_uuid);
    printf("UUID Created: %s", is_uuid_null ? "False - FAIL\n" : "True - PASS\n");
    if(is_uuid_null)
        return -BUFEP_FAILURE;

    bufep_uuid_unparse_lower(test_uuid, test_uuid_str);
    printf("\nUUID: %s\n", test_uuid_str);

    bufep_uuid_unparse_upper(test_uuid, test_uuid_str);
    printf("Capitalized-UUID: %s\n", test_uuid_str);

    bufep_uuid_copy(copied_test_uuid, test_uuid);
    if(bufep_uuid_compare(test_uuid, copied_test_uuid) == 0)
        printf("\nUUID Copy & Compare: PASS\n");
    else {
        printf("\nUUID Copy & Compare: FAIL\n");
        return -BUFEP_FAILURE;
    }

    bufep_uuid_parse(test_uuid_str, copied_test_uuid);
    if(bufep_uuid_compare(test_uuid, copied_test_uuid) == 0)
        printf("UUID Parse: PASS\n");
    else {
        printf("UUID Parse: FAIL\n");
        return -BUFEP_FAILURE;
    }

    bufep_uuid_clear(test_uuid);
    if(bufep_uuid_is_null(test_uuid))
        printf("UUID Clear: PASS\n");
    else {
        printf("UUID Clear: FAIL\n");
        return -BUFEP_FAILURE;
    }
}
