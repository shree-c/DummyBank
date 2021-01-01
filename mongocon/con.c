#include "/usr/include/libbson-1.0/bson.h"
#include "/usr/include/libmongoc-1.0/mongoc/mongoc.h"

int db(char *strrr) {
    printf("came here");
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

    mongoc_client_set_appname(client, "testingmor");
    // get a handle on database to work with by giving dbname and collection name
    database = mongoc_client_get_database (client, "tesname");
    collection = mongoc_client_get_collection (client, "tesname", "tescoll_name");
    // pinging the database (checking whether the database is working or not)
    //creating the command in BSON format
    bson = bson_new_from_json ((const uint8_t *)strrr, -1, &error);
    if (!bson) {
      fprintf (stderr, "%s\n", error.message);
      return EXIT_FAILURE;
    }
    if (!mongoc_collection_insert_one(collection, bson, NULL, NULL, &error)) {
        fprintf(stderr, "error: %s", error.message);
    }
    

      // bson_destroy (insert);
    //bson_destroy (&reply);
    //bson_destroy (command);
   // bson_free (str);

    /*
        * Release our handles and clean up libmongoc
        */
    mongoc_collection_destroy (collection);
    mongoc_database_destroy (database);
    mongoc_uri_destroy (uri);
    mongoc_client_destroy (client);
    mongoc_cleanup ();

       return EXIT_SUCCESS;
}
