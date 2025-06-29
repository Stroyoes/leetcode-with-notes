# Rename to main.py

from table import HashTable

if __name__ == "__main__":
    ht = HashTable(8)
    ht.set("apple", 3)
    ht.set("banana", 7)
    ht.set("orange", 5)
    ht.set("banana", 10)  # update

    try:
        print("banana =>", ht.get("banana"))
    except KeyError:
        print("banana not found")

    ht.remove("apple")
    try:
        print("apple =>", ht.get("apple"))
    except KeyError:
        print("apple not found")
