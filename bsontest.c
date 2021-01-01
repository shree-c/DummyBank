#include "/usr/include/libbson-1.0/bson/bson.h"
#include <stdlib.h>
int main() {
    bson_error_t error;
    bson_t *bson;
    char *string;
    const char *json = "{\"name\": \"shridhar\"}";
    bson = bson_new_from_json((const uint8_t *)json, -1, &error);
    if (!bson) {
        fprintf(stderr, "%s\n", error.message);
        return EXIT_FAILURE;
    }
    string = bson_as_canonical_extended_json(bson, NULL);
    printf("%s\n",string);
    bson_free(string);

    return 0;
}




