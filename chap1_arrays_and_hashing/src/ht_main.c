// Rename this file to main.c

#include "table.h"
#include <stdio.h>

int main(void) {
    HashTable *ht = ht_create(10);
    ht_set(ht, "apple", 3);
    ht_set(ht, "banana", 7);
    ht_set(ht, "orange", 5);
    ht_set(ht, "banana", 10); // update

    int found;
    int val = ht_get(ht, "banana", &found);
    printf("banana => %d (found? %d)\n", val, found);

    ht_remove(ht, "apple");
    val = ht_get(ht, "apple", &found);
    printf("apple => %d (found? %d)\n", val, found);

    ht_free(ht);
    return 0;
}
