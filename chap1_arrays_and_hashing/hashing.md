# **Hashing, Hash Function and Hash Table**

## **Hashing**

Hashing is a technique for mapping data of arbitrary size (keys) to fixed-size values called _hash codes_ or _hash values_. These hash values act as indices into a hash table, an array of _slots_ where the original data (or pointers to it) is stored. In an ideal hash table, computing the hash of a key and looking it up is **O(1)** time (constant time) because we compute an index and directly access that slot.  This avoids scanning the entire dataset. Mathematically, a hash function is a mapping.

![hash function](https://latex.codecogs.com/png.image?\dpi{150}\color{white}h:U\rightarrow\{0,1,\dots,m-1\})

where $U$ is the universe of keys and $m$ is the table size. 

For example, inserting keys 54, 26, 93 into an 11-slot table using $$h(k) = k \bmod 11$$ yields slots 10, 4, 5 respectively, and we place each key into its computed slot. When collisions don't occur, looking up a value is as fast as accessing an element by its index in an array.

## **Hash Functions**

A hash function computes an integer index for each key. A good hash function should be: 
deterministic (same key always same output), uniform (evenly distribute keys), fast to compute, and minimize collisions (different keys mapping to the same index). An example of a C function that hashes a string by its first letter:

```c 
 unsigned int hash(const char *word) {
     return (toupper(word[0]) - 'A');  // Only uses first character
 }

```

This trivial hash maps "apple" and "ant" both to 0, showing poor distribution. A better approach is the division method:
![hash function](https://latex.codecogs.com/png.image?\dpi{150}\color{white}h(k)=k\bmod{m})

where $m$ (often prime) is the table size. For strings, one can use polynomial hashing: convert characters to integer values $s_i$ and compute

![hash function](https://latex.codecogs.com/png.image?\dpi{150}&space;\color{white}h(s)=(s_0\cdot&space;a^{n-1}+s_1\cdot&space;a^{n-2}+\cdots+s_{n-1})\bmod{m})

where $a$ is a constant base (like 31). For example, the word "cat" can be hashed by summing its ASCII values (99+97+116) and taking the remainder: if $m=10$, $(99+97+116)\bmod 10 = 2$. Adding positional weights (e.g., multiply by powers of $a$) spreads anagrams into different hashes.

There are more practical methods like: 

- The **folding** method splits a numeric key into chunks, sums them, and mods by $m$ (e.g., phone number 436-555-4601 split into 43,65,55,46,01 gives sum 210, hash $210\bmod11=1$).

- The **mid-square** method squares the key and takes middle digits (e.g., 44²=1936, middle “93”, then $93\bmod11=5$).

In all cases, a final modulo ensures the index is in range. 

> Keep hash functions simple: an overly complex hash may cost more time than it saves in search (slowing down the overall process).

## **Collisions and the Pigeonhole Principle**

A collision occurs when two distinct keys hash to the same slot. Collisions are **inevitable**: with only $m$ slots and potentially many keys, the Pigeonhole Principle guarantees at least two keys share an
index. 

For example, hashing 44 into an 11-slot table using $h(k)=k\bmod11$ yields index 0, but if 77 is already at 0, both collide. 

Thus, even a perfect hash function (one-to-one mapping) isn’t usually possible for large or dynamic key sets. 

A good hash
function aims to minimize collisions via uniform distribution, but it cannot eliminate them. 

When a collision happens, the hash table must resolve it, either by storing multiple items in a single
slot or by probing for another empty slot. These strategies are crucial for maintaining performance.

## **Collision Resolution Strategies**

### **Separate Chaining**

In **separate chaining**, each table slot holds a pointer to a linked list (or another collection) of all keys hashing there. To insert, you add the key to the list at its index; to search, you traverse that list.

Example in C:

```c
typedef struct node {
    char word[LENGTH+1];
    struct node *next;
 } node;

 #define N 10007  // number of buckets
 node *table[N];  // hash table: array of list heads
 // ... initialize table[i]=NULL for all i
```

Each `table[i]` is the head of a linked list. Insertion (at head) in C:

```c
unsigned int index = hash(word) % N;
node *new = malloc(sizeof(node));
strcpy(new->word, word);
new->next = table[index];
table[index] = new;
```

Searching involves scanning the list at `table[index]`. Chaining is simple and handles deletions easily:
just remove a node from a list. Its average search time is $O(1 + \alpha)$, where $\alpha=n/m$ is the
load factor (average list length). However, in the worst case (all keys hash same slot), search
degrades to $O(n)$.

An ASCII illustration of separate chaining:

```
Index 0: -> [Cat] -> [Cow] -> [Car] -> NULL
Index 1: -> NULL
Index 2: -> [Dog] -> NULL
Index 3: -> [Fish] -> [Fox] -> NULL
...
```

### **Open Addressing**

In **open addressing**, all keys reside in the table array itself; on collision, the algorithm probes the table for another empty slot. 

We compute a sequence of candidate indices until an empty one is found. Common probing methods include:

- **Linear Probing**: Try $h(k), h(k)+1, h(k)+2, ... (mod\:m)$. For example, inserting keys 77 and 44 into an 11-slot table with $h(k)=k\bmod11$: 77→0 goes to slot 0, 44→0 collides, so we try slot 1
and insert it there. 

    The sequence of slots can be visualized as:
    ```
    Index:  0   1   2   3   4   5  ... 10
    Table: [77][44] ... (others)
    ```

    Searching under linear probing follows the same sequence: if searching for 44, compute 0, see 77 (not match), then check index 1 and find 44. 

    A drawback is _primary clustering_: long runs of occupied slots forms, causing many probes. For instance, with keys 18,25,32,39 filling slots 1–4, inserting 45 (which hashes to 3) has to skip to 5, extending the cluster.

- **Quadratic Probing**: Jump by increasing squares: try $h(k), h(k)+1^2, h(k)+2^2, h(k)+3^2, ... 
(mod\:m)$. E.g., if $h(k)=5$, we try 5,6,9, etc. 

    Quadratic probing avoids primary clustering
    (different keys “spread out” more), but can still create secondary clustering (keys with same
    original hash follow the same probe pattern). 
    
    Example: for 44 hashing to 0,
    probes go to 1, 4, 9, etc.

- **Double Hashing**: Use a second hash function $h_2(k)$ to compute skip sizes. After the first
 hash $h_1(k)$, subsequent probes are

    ![hash function](https://latex.codecogs.com/png.image?\dpi{150}&space;\color{white}\text{index}_i=(h_1(k)+i\cdot&space;h_2(k))\bmod{m})

    For instance, with $h_1(k)=k \bmod m$ and $h_2(k)=1+(k \bmod(m-1))$, the sequence jumps by
    $h_2(k)$ each time. 
    
    Double hashing greatly reduces clustering, because different keys have
    different probe sequences.

**Searching with open addressing**: To search a key, compute its hash and probe in the same
sequence until you find the key (success) or hit an empty slot (failure). Unlike chaining, even if a slot
is empty during insertion, you may have to continue probing because earlier occupied slots might
have “skipped” this spot.

**Open addressing example (C)** – for simplicity, use -1 to indicate empty:

```c
#define EMPTY -1
#define DELETED -2
int table[SIZE];  // initialize all to EMPTY

void insert(int key) {
    int i = 0;
    int h = hash(key) % SIZE;
    while (i < SIZE) {
        int idx = (h + i) % SIZE;  // linear probing
        if (table[idx] == EMPTY || table[idx] == DELETED) {
            table[idx] = key;
            return;
        }
        i++;
    }
    // table full or rehash needed
}
```

This uses linear probing; quadratic or double hashing just change the computation of `idx`.

Deletion
in open addressing can be tricky (often mark slots as DELETED to not break probe chains).

**Comparison: Chaining vs Open Addressing**

-  **Chaining** is robust under high load and simplifies deletions, but requires extra memory for
pointers. If $n$ keys fill $m$ buckets, the average list length is $\alpha=n/m$ and search time
is $O(1+\alpha)$ . 

- **Open addressing** saves space (just the table array) but performance deteriorates quickly as
 the load factor $\alpha$ approaches 1. 
    
    **Knuth’s analysis** shows that with linear probing,
    successful searches cost about $(1 + 1/(1-\alpha))/2$ probes on average, while unsuccessful
    searches cost about $(1 + 1/(1-\alpha)^2)/2$. In practice, we keep $\alpha<1$ (often
    $\alpha<0.75$) by resizing the table when it gets too full.

## **Clustering**

Clustering is the tendency for keys to form contiguous groups (clusters) in a hash table, common with open addressing. In _primary clustering_ (linear probing), a filled slot can cause a “run” of occupied cells (e.g., indices 1–5 filled as in [2]), making subsequent probes long.

Secondary clustering occurs with quadratic probing: keys hashing to the same index follow identical
probe sequences, clustering around that region. Double hashing largely avoids clustering since its
probe sequence depends on the key

Clustering hurts performance: many empty slots may exist but are “shielded” behind clusters, so
new keys must skip long runs. ASCII example of primary clustering (linear probing):

```
Index: 0  1  2  3  4  5  6  7  8  9
Table: -- 18 25 32 39 -- -- -- -- --
```

(“--” denotes empty). Inserting key 45 (hashes to 3) must skip 3 and 4, landing in 5, thus extending
the block:

```
Index: 0  1  2  3  4  5  6  7  8  9
Table: -- 18 25 32 39 45 -- -- -- --
```

Now a dense cluster spans 1–5, slowing future operations. In summary, clustering leads to longer
probe sequences (slower insert/search) even when many slots remain free.

## **Load Factor and Performance**

The **load factor** $\alpha = n/m$ measures table fullness (with $n$ keys, $m$ slots). It critically
affects performance. In chaining, $\alpha$ is the average bucket size: expected search time is
$O(1+\alpha)$ (since one hash lookup plus scanning that bucket). In open addressing, as $\alpha$
grows, probe lengths increase nonlinearly. Typically, implementations resize (expand) the table once
$\alpha$ crosses a threshold (e.g. 0.7–0.8) to keep operations fast.
For example, Knuth’s formulas for linear probing show dramatic slowdown when $\alpha$ nears 1.
If $\alpha=0.9$, an unsuccessful search in linear probing would take on average $(1 + 1/(0.1)^2)/2 ≈
50$ probes. Thus, a small load factor is crucial. Most libraries (e.g. Java’s HashMap, C++’s
unordered_map) do automatic rehashing: they allocate a larger array and reinsert keys when load
gets high.

## Real-World Implementations and Applications

Hash tables underpin many data structures and systems. Common examples:

* **Dictionaries/Maps**:
  Python’s `dict` and `set` use open addressing with probing.
  C++’s `std::unordered_map` uses chaining.
  Java’s `HashMap` and `Hashtable` use chaining with dynamic resizing.

* **Caching and Databases**:
  In-memory caches (e.g., `memcached`) and database indexes often use hashing for fast key lookups.

* **Symbol Tables**:
  Compilers use hash tables to map variable names to information.

* **Cryptographic Uses**:
  Cryptographic hash functions (e.g., MD5, SHA-\*) are related but serve different needs.
  They produce irreversible digests for security and are **not** optimized for hash tables.
  Regular hash tables use fast, non-cryptographic hashes since collision resistance is not required.

> 💡 _**Real-world hash functions add features**_:
>
> Python’s `hash()` combines a polynomial hash with random seeds to thwart collision-based attacks.
> Many systems also preselect table sizes to be **prime numbers** to distribute keys better and avoid stuck probe cycles.

## Limitations and Security

Hash tables have pitfalls:

* **Worst-case performance**:
  If many keys collide (due to a poor hash function or malicious input), operations degrade to **O(n)**.
  Attackers can exploit this (e.g., by sending many colliding keys) to cause denial-of-service **(DoS)**. 
  
  Mitigation: Modern languages like Python randomize hash seeds.

* **Memory overhead**:

  * Chaining requires **pointers** for each element.
  * Open addressing may waste slots or require special flags (like `DELETED`).

* **No order**:
  Hash tables do **not preserve key order**.
  Iterating in sorted order requires additional steps.

* **Sensitivity to table size**:
  Using a bad table size (like a power of 2 with a bad hash) or not resizing can lead to **heavy clustering** or frequent collisions.

## Summary

> In summary, **hashing offers average-case efficiency** but must be used carefully.
> A well-chosen hash function and resizing policy yield **lightning-fast lookups**.
> Otherwise, performance can collapse under collisions or high load.

## **Implementations in _C_ and _Python_**

- **Python Version with Separate Chaining**: [`table.py`](src/table.py)  
  > 🚀 Run it using:  
  > ```bash
  > python3 main.py
  > ```  
  > 📁 *Make sure `main.py` and `table.py` are in the same folder.*

- **C Version with Separate Chaining**: [`table.h`, `table.c`, and `main.c`](src/)  
  > 🚀 Compile and run using:  
  > ```bash
  > gcc -o main main.c table.c
  > ./main
  > ```  
  > 📁 *Make sure `table.h`, `table.c`, and `main.c` are in the same folder.*

---

### <ins>**Quick Recap**</ins>

---


<table align="center">
  <tr>
    <td align="center">
      <a href="../README.md">
        <img src="https://img.shields.io/badge/-📚%20Jump%20to%20Prev%20Chapter-blueviolet?style=for-the-badge" alt="Jump to Prev Chapter">
      </a>
    </td>
    <td align="center">
      <a href="./hashing.md">
        <img src="https://img.shields.io/badge/-📚%20Jump%20to%20Next%20Section-blueviolet?style=for-the-badge" alt="Jump to Next Section">
      </a>
    </td>
  </tr>
</table>

