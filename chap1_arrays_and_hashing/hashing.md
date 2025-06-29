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
