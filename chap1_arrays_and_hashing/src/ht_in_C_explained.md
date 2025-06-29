# Explanation of Hash table implementation in C

---

```c
// table.h

#ifndef TABLE_H
#define TABLE_H
```

> 💡 **Explanation**
> These two lines are include‑guards. They prevent multiple inclusion of this header file during compilation. If `TABLE_H` is not defined, we define it and include everything up to the corresponding `#endif`. If it is already defined, the contents are skipped.

---

```c
typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;
} Entry;
```

> 💡 **Explanation**
> This defines a linked‑list node (`Entry`) used in each bucket to handle collisions (separate chaining).
>
> * `char *key;` points to a dynamically allocated string holding the key.
> * `int value;` stores the associated integer value.
> * `struct Entry *next;` points to the next node in the chain (or `NULL` if it’s the last).

---

```c
typedef struct {
    Entry **buckets;
    int capacity;
    int size;
} HashTable;
```

> 💡 **Explanation**
> This defines the main hash‑table structure.
>
> * `Entry **buckets;` is an array of pointers to `Entry` chains—one chain per bucket.
> * `int capacity;` is the total number of buckets.
> * `int size;` keeps track of how many key‑value pairs are currently stored.

---

```c
HashTable *ht_create(int capacity);
void ht_free(HashTable *ht);
void ht_set(HashTable *ht, const char *key, int value);
int ht_get(HashTable *ht, const char *key, int *found);
void ht_remove(HashTable *ht, const char *key);
#endif // TABLE_H
```

> 💡 **Explanation**
> These are the function prototypes for our API:
>
> * `ht_create` allocates and initializes a new table.
> * `ht_free` deallocates everything.
> * `ht_set` inserts or updates a key/value.
> * `ht_get` looks up a value by key; sets `*found` to 1 if present, 0 otherwise.
> * `ht_remove` deletes a key/value pair.

---

```c
// table.c
#include "table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
```

> 💡 **Explanation**
>
> * `#include "table.h"` brings in our declarations.
> * `<stdlib.h>` provides `malloc`, `calloc`, `free`.
> * `<string.h>` provides `strdup`, `strcmp`.
> * `<stdio.h>` is only used here if you add debugging `printf`s (not strictly required for functionality).

---

```c
static unsigned int hash(const char *key, int capacity) {
    unsigned long hash = 0;
    for (; *key; key++) 
        hash = hash * 31 + (unsigned char)*key;
    return hash % capacity;
}
```

> 💡 **Explanation**
> This is our hash‐function:
>
> 1. Initialize `hash = 0`.
> 2. For each character in the null‑terminated `key` string, multiply the running `hash` by 31 (a small prime) and add the character’s unsigned value.
> 3. Finally, take the modulo by `capacity` to map into a bucket index in `[0…capacity-1]`.
> 4. Marked `static` so it’s private to this file.

---

```c
HashTable *ht_create(int capacity) {
    HashTable *ht = malloc(sizeof(HashTable));
    ht->capacity = capacity;
    ht->size = 0;
    ht->buckets = calloc(capacity, sizeof(Entry *));
    return ht;
}
```

> 💡 **Explanation**
>
> 1. `malloc` a `HashTable` struct.
> 2. Store `capacity` and initialize `size` to 0.
> 3. `calloc` an array of `capacity` pointers, all initially `NULL`—one slot per bucket.
> 4. Return the pointer to the newly created table.

---

```c
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
```

> 💡 **Explanation**
>
> 1. Loop over each bucket index `i`.
> 2. Traverse its linked list (`Entry *e`).
> 3. For each node, save `e->next` in `next`, `free(e->key)` (since we `strdup`’d it), then `free(e)` itself, and move to the next node.
> 4. After clearing all chains, `free(ht->buckets)` (the bucket array) and finally `free(ht)`.

---

```c
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
    Entry *new = malloc(sizeof(Entry));
    new->key = strdup(key);
    new->value = value;
    new->next = ht->buckets[idx];
    ht->buckets[idx] = new;
    ht->size++;
}
```

> 💡 **Explanation**
>
> 1. Compute the bucket index `idx`.
> 2. Walk the chain at `buckets[idx]` to see if `key` already exists (`strcmp`).
>
>    * If found, overwrite `value` and return.
> 3. If not found, allocate a new `Entry`.
> 4. `strdup` the `key` so we own our own copy.
> 5. Set its `value`, make it point to the former head (`new->next = …`), and then set `buckets[idx] = new` to insert at head.
> 6. Increment the overall `size`.

---

```c
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
```

> 💡 **Explanation**
>
> 1. Compute the bucket index.
> 2. Traverse its linked list; if `strcmp` matches, set `*found = 1` and return the stored `value`.
> 3. If the key is not in the chain, set `*found = 0` and return 0 (caller must check `found`).

---

```c
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
```

> 💡 **Explanation**
>
> 1. Compute the bucket index.
> 2. Use a double‐pointer `Entry **ptr` so we can easily relink the previous node’s `next` (or the bucket head) when deleting.
> 3. If `(*ptr)->key` matches, save the node to `del`, set `*ptr = del->next` (skipping over it), then `free` the key and node, decrement `size`, and return.
> 4. Otherwise, advance `ptr` to the address of the next‐pointer.

---

```c
// main.c

#include "table.h"
#include <stdio.h>

int main(void) {
    HashTable *ht = ht_create(10);

    ht_set(ht, "apple", 3);
    ht_set(ht, "banana", 7);
    ht_set(ht, "orange", 5);
    ht_set(ht, "banana", 10); // update existing entry

    int found;
    int val = ht_get(ht, "banana", &found);
    printf("banana => %d (found? %d)\n", val, found);

    ht_remove(ht, "apple");
    val = ht_get(ht, "apple", &found);
    printf("apple => %d (found? %d)\n", val, found);

    ht_free(ht);
    return 0;
}
```

> 💡 **Explanation**
>
> 1. Include our API and `<stdio.h>` for printing.
> 2. `ht_create(10)` makes a 10‑bucket table.
> 3. We `ht_set` three fruits, then overwrite `"banana"`.
> 4. `ht_get` retrieves `"banana"`, printing its value and whether it was found.
> 5. We `ht_remove("apple")`, then attempt to `ht_get` it again (should show `found? 0`).
> 6. Finally, clean up with `ht_free` and exit.
