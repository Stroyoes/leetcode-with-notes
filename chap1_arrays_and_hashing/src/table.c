// table.c

#include "table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Simple hash: sum of characters modulo capacity
static unsigned int hash(const char *key, int capacity) {
    unsigned long hash = 0;
    for (; *key; key++) hash = hash * 31 + (unsigned char)*key;
    return hash % capacity;
}

// One-line: allocate and initialize hash table with buckets
HashTable *ht_create(int capacity) {
    HashTable *ht = malloc(sizeof(HashTable));
    ht->capacity = capacity;
    ht->size = 0;
    ht->buckets = calloc(capacity, sizeof(Entry *));
    return ht;
}

// One-line: free all entries and hash table
void ht_free(HashTable *ht) {
    for (int i = 0; i < ht->capacity; i++) {
        Entry *e = ht->buckets[i];
        while (e) {
            Entry *next = e->next;
            free(e->key);
            free(e);
            e = next;
        }
    }
    free(ht->buckets);
    free(ht);
}

// One-line: insert or update key-value
void ht_set(HashTable *ht, const char *key, int value) {
    unsigned int idx = hash(key, ht->capacity);
    Entry *e = ht->buckets[idx];
    while (e) {
        if (strcmp(e->key, key) == 0) {
            e->value = value; // update existing
            return;
        }
        e = e->next;
    }
    // not found: create a new entry and prepend
    Entry *new = malloc(sizeof(Entry));
    new->key = strdup(key);
    new->value = value;
    new->next = ht->buckets[idx];
    ht->buckets[idx] = new;
    ht->size++;
}

// One-line: retrieve value, set found flag
int ht_get(HashTable *ht, const char *key, int *found) {
    unsigned int idx = hash(key, ht->capacity);
    for (Entry *e = ht->buckets[idx]; e; e = e->next) {
        if (strcmp(e->key, key) == 0) {
            *found = 1;
            return e->value;
        }
    }
    *found = 0;
    return 0;
}

// One-line: remove key-value, free its memory
void ht_remove(HashTable *ht, const char *key) {
    unsigned int idx = hash(key, ht->capacity);
    Entry **ptr = &ht->buckets[idx];
    while (*ptr) {
        if (strcmp((*ptr)->key, key) == 0) {
            Entry *del = *ptr;
            *ptr = del->next;
            free(del->key);
            free(del);
            ht->size--;
            return;
        }
        ptr = &(*ptr)->next;
    }
}
