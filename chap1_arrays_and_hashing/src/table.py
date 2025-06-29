# table.py

"""HashTable with separate chaining for collision resolution."""

class Node:
    """One-line: Node storing a key-value pair in a linked list."""
    __slots__ = ('key', 'value', 'next')
    def __init__(self, key, value, nxt=None):
        self.key = key
        self.value = value
        self.next = nxt

class HashTable:
    """One-line: A simple hash table with chaining."""

    def __init__(self, capacity=16):
        """One-line: Initialize table with given capacity."""
        self.capacity = capacity
        self.size = 0
        self.buckets = [None] * capacity

    def _hash(self, key):
        """One-line: Compute bucket index for a key."""
        return hash(key) % self.capacity

    def set(self, key, value):
        """One-line: Insert or update key-value."""
        idx = self._hash(key)
        node = self.buckets[idx]
        while node:
            if node.key == key:
                node.value = value
                return
            node = node.next
        # insert new node at head
        self.buckets[idx] = Node(key, value, self.buckets[idx])
        self.size += 1

    def get(self, key):
        """One-line: Retrieve value for key or raise KeyError."""
        idx = self._hash(key)
        node = self.buckets[idx]
        while node:
            if node.key == key:
                return node.value
            node = node.next
        raise KeyError(key)

    def remove(self, key):
        """One-line: Remove key-value or raise KeyError."""
        idx = self._hash(key)
        prev = None
        node = self.buckets[idx]
        while node:
            if node.key == key:
                if prev:
                    prev.next = node.next
                else:
                    self.buckets[idx] = node.next
                self.size -= 1
                return
            prev, node = node, node.next
        raise KeyError(key)
