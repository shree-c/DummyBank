#include "/usr/include/libbson-1.0/bson.h"
#include "/usr/include/libmongoc-1.0/mongoc/mongoc.h"

int db_create(char *json_string) {
    const char *uri_string = "mongodb://localhost:27017";
    mongoc_uri_t *uri;
    mongoc_client_t *client;
    mongoc_database_t *database;
    mongoc_collection_t *collection;
    bson_t *command, reply, *insert;
    bson_error_t error;
    char *str;
    bool retval;
    bson_t *bson;
    // initialising mongoc internals
    mongoc_init();
    // creating mongodb uri object from uri string
    uri = mongoc_uri_new_with_error(uri_string, &error);
    // giving out error message is couldn't create uri
    if (!uri) {
        fprintf(stderr, "failed to parse URI :%s\n"
        "error message: %s\n", uri_string, error.message);
        return EXIT_FAILURE;
    }
    // creating new client instance client = mongoc_client_new_from_uri(uri); // exiting if failed to create client
   
    client = mongoc_client_new_from_uri (uri);
    if (!client) {
        return EXIT_FAILURE;
    }
    // registering application name for traking purposes

    mongoc_client_set_appname(client, "testingmor"); // get a handle on database to work with by giving dbname and collection name
    database = mongoc_client_get_database (client, "tesname");
    collection = mongoc_client_get_collection (client, "tesname", "tescoll_name");
    // pinging the database (checking whether the database is working or not)
    //creating the command in BSON format
    bson = bson_new_from_json ((const uint8_t *)json_string, -1, &error);
    if (!bson) {
      fprintf (stderr, "%s\n", error.message);
      return EXIT_FAILURE;
    }
    if (!mongoc_collection_insert_one(collection, bson, NULL, NULL, &error)) {
        fprintf(stderr, "error: %s", error.message);
    }

    mongoc_collection_destroy (collection);
    mongoc_database_destroy (database);
    mongoc_uri_destroy (uri);
    mongoc_client_destroy (client);
    mongoc_cleanup ();

   return EXIT_SUCCESS;
}
int db_find_name(char *name) {
    mongoc_client_t *client;
    mongoc_collection_t *collection;
    mongoc_cursor_t *cursor;
    const bson_t *doc;
    bson_t *query;
    char *str;
    mongoc_init();
    client = mongoc_client_new("mongodb://localhost:27017/?appname=testingmor");
    collection = mongoc_client_get_collection(client, "tesname", "tescoll_name");
    query = bson_new();
    BSON_APPEND_UTF8(query, "first name", name);
    //taking cursor to that position
    cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);
    if (!mongoc_cursor_next(cursor, &doc)) {
        printf("not found\n");
        return EXIT_FAILURE;
    }

    bson_destroy(query);
    mongoc_cursor_destroy(cursor);
    mongoc_collection_destroy(collection);
    mongoc_client_destroy(client);
    mongoc_cleanup();
    return 0;
}

int db_remove(char *name) {

    mongoc_client_t *client;
    mongoc_collection_t *collection;
    bson_t *doc;
    bson_error_t error;
    mongoc_init();
    client = mongoc_client_new("mongodb://localhost:27017/?appname=testingmor");
    collection = mongoc_client_get_collection(client, "tesname", "tescoll_name");
    if (db_find_name(name)) { 
        printf("not found...\n");
        return EXIT_FAILURE;
    }
    doc = bson_new();

    BSON_APPEND_UTF8(doc, "first name", name);
    if(!mongoc_collection_delete_one(collection, doc, NULL, NULL, &error)) {
        fprintf(stderr, "error deleting: %s\n", error.message);
    } else
        printf("successfully deleted...\n");
    bson_destroy(doc);
    mongoc_collection_destroy(collection);
    mongoc_client_destroy(client);
    mongoc_cleanup();
    return 0;
}
int db_transact(char *name, int amount, char tra_type) {
    mongoc_client_t *client;
    mongoc_collection_t *collection;
    mongoc_cursor_t *cursor;
    const bson_t *doc;
    bson_t *query = NULL;
    bson_t *update = NULL;
    bson_error_t error;
    mongoc_init();
    int balance_before;
    client = mongoc_client_new("mongodb://localhost:27017/?appname=testingmor");
    collection = mongoc_client_get_collection(client, "tesname", "tescoll_name");
    query = bson_new();
    BSON_APPEND_UTF8(query, "first name", name);
    cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);
    if (cursor == NULL) {
        printf("couldn't find\n");
        return EXIT_FAILURE;
    }
    while(mongoc_cursor_next(cursor, &doc)) {
        char *str = bson_as_canonical_extended_json (doc, NULL);
        printf ("%s\n", str);
        printf("came here\n");
        bson_iter_t iter;
        if (bson_iter_init(&iter, doc)) {
            while (bson_iter_next(&iter)) {
                if (strcmp(bson_iter_key(&iter), "balance") == 0) {
                    balance_before = bson_iter_int32(&iter);
                }
            }
        }
    }
    printf("balance_before: %d, amount transacted: %d\n", balance_before, amount);
    int final_balance;
    if (tra_type == 'd') {
        if ((balance_before - amount) <= 500) {
            printf("Not possible minimum balance should be 500.\n");
            return EXIT_FAILURE;
        }
        final_balance = balance_before - amount;
    } else if (tra_type == 'c') {
        if (amount <= 0) {
            printf("Invalid amount.\n");
            return EXIT_FAILURE;
        }
        final_balance = balance_before + amount;
    } 
    printf("final balance :%d\n", final_balance);
    update = BCON_NEW ("$set", "{", "balance", BCON_INT32 (final_balance), "}");
    if (!mongoc_collection_update_one (
              collection, query, update, NULL, NULL, &error)) {
          fprintf (stderr, "%s\n", error.message);
          goto fail;
       }
    printf("updated\n");
    fail:
       //if (doc)
        //  bson_destroy (doc);
       if (query)
          bson_destroy (query);
       if (update)
          bson_destroy (update);

       mongoc_collection_destroy (collection);
       mongoc_client_destroy (client);
       mongoc_cleanup ();

       return 0;

}


 

int db_display(char *name) {
    mongoc_client_t *client;
    mongoc_collection_t *collection;
    mongoc_cursor_t *cursor;
    const bson_t *doc;
    bson_t *query;
    char *str;
    mongoc_init();
    client = mongoc_client_new("mongodb://localhost:27017/?appname=testingmor");
    collection = mongoc_client_get_collection(client, "tesname", "tescoll_name");
    query = bson_new();
    BSON_APPEND_UTF8 (query, "first name", name);
    //taking cursor to that position
    cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);
    int exists = 0;
    while(mongoc_cursor_next(cursor, &doc)) {
        // we are iterating over the document
        exists = 1;
        bson_iter_t iter;
        if (bson_iter_init(&iter, doc)) {
            // here we make decision to print different data formats
            while (bson_iter_next(&iter)) {
                if (strcmp(bson_iter_key(&iter), "_id") == 0) {
                    char oidhold[25];
                    bson_oid_to_string(bson_iter_oid(&iter), oidhold);
                    printf (" acc_id : %s\n", oidhold);
                }
                else if (strcmp(bson_iter_key(&iter), "balance") == 0)
                    printf (" %s : %d\n", bson_iter_key(&iter), bson_iter_int32(&iter));
                else
                    printf (" %s : %s\n", bson_iter_key(&iter), bson_iter_utf8(&iter, NULL));
            }
        }
    }
    if (!exists) {
            printf("not found\n");
            return EXIT_FAILURE;
    }
    bson_destroy(query);
    mongoc_cursor_destroy(cursor);
    mongoc_collection_destroy(collection);
    mongoc_client_destroy(client);
    mongoc_cleanup();
    return 0;
}
