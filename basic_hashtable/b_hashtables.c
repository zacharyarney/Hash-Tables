#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/****
  Basic hash table key/value pair
 ****/
typedef struct Pair {
    char *key;
    char *value;
} Pair;

/****
  Basic hash table
 ****/
typedef struct BasicHashTable {
    int capacity;
    Pair **storage;
} BasicHashTable;

/****
  Create a key/value pair to be stored in the hash table.
 ****/
Pair *create_pair(char *key, char *value)
{
    Pair *pair = malloc(sizeof(Pair));
    pair->key = strdup(key);
    pair->value = strdup(value);

    return pair;
}

/****
  Use this function to safely destroy a hashtable pair.
 ****/
void destroy_pair(Pair *pair)
{
    if (pair != NULL) {
        free(pair->key);
        free(pair->value);
        free(pair);
    }
}

/****
  djb2 hash function

  Do not modify this!
 ****/
unsigned int hash(char *str, int max)
{
    unsigned long hash = 5381;
    int c;
    unsigned char * u_str = (unsigned char *)str;

    while ((c = *u_str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % max;
}


/****
  Fill this in.

  All values in storage should be initialized to NULL
  (hint: look up `calloc`)
 ****/
BasicHashTable *create_hash_table(int capacity)
{
    // Allocates space for the struct
    BasicHashTable *ht = malloc(sizeof(BasicHashTable));
    // allocates space for the actual storage
    // use calloc() to initialize everything to NULL
    ht->storage = calloc(capacity, sizeof(Pair *));
    //initialises capacity
    ht->capacity = capacity;

    return ht;
}

/****
  Fill this in.

  If you are overwriting a value with a different key, print a warning.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_insert(BasicHashTable *ht, char *key, char *value)
{
    // hashes an index for the item
    unsigned int i = hash(key, ht->capacity);
    // creates new Pair struct using function params
    Pair *pair = create_pair(key, value);
    // check if index is already occupied
    if (ht->storage[i] != NULL) {
        // prints warning when overwriting with different value
        if (strcmp(key, ht->storage[i]->key) != 0) {
            printf("Overwriting this value");
        }
        // delete current value
        destroy_pair(ht->storage[i]);
    }
    // insert new value
    ht->storage[i] = pair;
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(BasicHashTable *ht, char *key)
{
    // hashes an index from the key
    unsigned int i = hash(key, ht->capacity);
    // checks to see if there's anything at that index
    if (ht->storage[i] == NULL || strcmp(ht->storage[i]->key, key) != 0) {
        printf("Nothing to remove");
    } else {
        // remove item
        destroy_pair(ht->storage[i]);
        ht->storage[i] = NULL;
    }

}

/****
  Fill this in.

  Should return NULL if the key is not found.
 ****/
char *hash_table_retrieve(BasicHashTable *ht, char *key)
{
    // hash index from key
    unsigned int i = hash(key, ht->capacity);
    // checks to see if there's anything at that index
    if (ht->storage[i] == NULL || strcmp(ht->storage[i]->key, key) != 0) {
        printf("Nothing to retrieve");
        return NULL;
    } else {
        // return item at hashed index
        return ht->storage[i]->value;
    }
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(BasicHashTable *ht)
{
    // free individual elements first
    for (int i = 0; i < ht->capacity; i++) {
        if (ht->storage[i] != NULL) {
            destroy_pair(ht->storage[i]);
        }
    }
    // free storage array
    free(ht->storage);
    // free the hash table struct
    free(ht);
}


#ifndef TESTING
int main(void)
{
    struct BasicHashTable *ht = create_hash_table(16);

    hash_table_insert(ht, "line", "Here today...\n");

    printf("%s", hash_table_retrieve(ht, "line"));

    hash_table_remove(ht, "line");

    if (hash_table_retrieve(ht, "line") == NULL) {
        printf("...gone tomorrow. (success)\n");
    } else {
        fprintf(stderr, "ERROR: STILL HERE\n");
    }

    destroy_hash_table(ht);

    return 0;
}
#endif
