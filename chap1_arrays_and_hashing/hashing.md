# **Hashing, Hash Function and Hash Table**

 Hashing is a technique for mapping data of arbitrary size (keys) to fixed-size values called _hash
 codes_ or _hash values_. These hash values act as indices into a hash table, an array of _slots_ where the
 original data (or pointers to it) is stored. In an ideal hash table, computing the hash of a key and
 looking it up is **O(1)** time (constant time) because we compute an index and directly access that slot.  This avoids scanning the entire dataset. Mathematically, a hash function is a mapping.

$$
h : U \rightarrow \{0, 1, \dots, m - 1\}
$$

where $U$ is the universe of keys and $m$ is the table size. 

For example, inserting keys 54, 26, 93 into an 11-slot table using $h(k)=k \bmod 11$ yields slots 10, 4, 5 respectively, and we place each key into its computed slot. When collisions don't occur, looking up a value is as fast as accessing an element by its index in an array. 


