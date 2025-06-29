// table.h

#ifndef TABLE_H
#define TABLE_H

// Node in the linked list for chaining
typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;
} Entry;

// Hash table struct
typedef struct {
    Entry **buckets;
    int capacity;
    int size;
} HashTable;

// One-line explanation: Create a new hash table with given capacity
HashTable *ht_create(int capacity);

// One-line explanation: Free all memory used by the hash table
void ht_free(HashTable *ht);

// One-line explanation: Insert or update key-value pair into the table
void ht_set(HashTable *ht, const char *key, int value);

// One-line explanation: Retrieve value for key; returns 0 if not found
int ht_get(HashTable *ht, const char *key, int *found);

// One-line explanation: Remove a key-value pair from the table
void ht_remove(HashTable *ht, const char *key);

#endif // TABLE_H
