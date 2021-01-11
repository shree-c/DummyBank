#include <libbson-1.0/bson/bson.h>
#include <stdio.h>
#include "/usr/include/libbson-1.0/bson.h"
#include "/usr/include/libmongoc-1.0/mongoc/mongoc.h"

int seed_retriver() {
    mongoc_client_t *client;
    mongoc_collection_t *collection;
    mongoc_cursor_t *cursor;
    const bson_t *doc;
    bson_t *query;
    char *str;
    mongoc_init();
    client = mongoc_client_new("mongodb://localhost:27017/?appname=testingmor");
    collection = mongoc_client_get_collection(client, "tesname", "seed_store");
    //taking cursor to that position
    query = bson_new();
    cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);
    int valstored;
    if (mongoc_cursor_next(cursor, &doc)) {
        char *str = bson_as_canonical_extended_json (doc, NULL);
        bson_iter_t iter;
        if (bson_iter_init(&iter, doc)) {
            while (bson_iter_next(&iter)) {
                    valstored = bson_iter_int32(&iter);
                }
            }
     }

    bson_destroy(query);
    mongoc_cursor_destroy(cursor);
    mongoc_collection_destroy(collection);
    mongoc_client_destroy(client);
    mongoc_cleanup();
    return valstored;
}

char *acc_no_gen() {
    char *acc_no = (char *) malloc(11 * sizeof(char));
    int seed = seed_retriver();
    sprintf(acc_no, "198571%04d", seed);
    return acc_no;
}

void update_seed() {
	mongoc_collection_t *collection;
	mongoc_client_t *client;
	bson_error_t error;
	bson_t *update = NULL;
    bson_t *query = NULL;
	mongoc_init();
	client = mongoc_client_new("mongodb://localhost:27017/?appname=testingmor");
    collection = mongoc_client_get_collection(client, "tesname", "seed_store");
    int seed = seed_retriver();
    query = bson_new();
    BSON_APPEND_INT32(query, "seed", seed);
    seed++;
    printf("%d\n", seed);
    update = BCON_NEW("$set", "{", "seed", BCON_INT32(seed), "}");
    if (!mongoc_collection_update_one (
          collection, query, update, NULL, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
    }
    if (query)
      bson_destroy (query);
    if (update)
      bson_destroy (update);

    mongoc_collection_destroy (collection);
    mongoc_client_destroy (client);
    mongoc_cleanup ();

}

int main() {
    printf("before_seed:%d\n", seed_retriver());
    printf("account no:%s\n", acc_no_gen());
    update_seed();
    printf("updated_seed:%d\n", seed_retriver());
    return 0;
}
