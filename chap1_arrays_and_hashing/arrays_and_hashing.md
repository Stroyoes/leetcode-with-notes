# **Arrays and Hashing**

## **What is a Dynamic Array?**

A dynamic array is a resizable array structure that stores a sequence of elements in contiguous memory, like a normal array — but unlike static arrays, it can grow and shrink at runtime.

> 🧠 _**Analogy:**_
>
> Imagine you have a row of boxes.
> * **Static Array:** You decide beforehand you'll need 10 boxes, and you set them up. If you need 11, you're out of luck.
> * **Dynamic Array:** You start with a few boxes. When they're full, you get a bigger cart, move all your existing boxes to the new cart, and then add more boxes. You keep doing this as needed.

To understand dynamic array we have to first understand what a static array is. If you already know that you can jump to [here](#how-da-works). 

## **What is a static array?**

A static array has a fixed capacity that is determined at compile time and cannot be changed later. All elements in the array are always allocated in memory, whether used or not. 

### **Example: Static array (in C)**

```
#include <stdio.h>

int main() {
    int scores[6] = {87, 92, 76, 81, 95};  // static array with capacity 6

    // Length of array is fixed: 6
    // Only first 5 are used (others may be 0 or garbage if uninitialized)
    
    printf("All scores:\n");
    for (int i = 0; i < 6; i++) {
        printf("Index %d: %d\n", i, scores[i]);
    }

    return 0;
}
```

> 💡 _**Explanation:**_ 
> 
> This C program demonstrates a static array of fixed size `6`, where only the first 5 elements are initialized. The 6th element remains uninitialized (garbage values). The program prints all 6 elements using a for loop.

### **Time Complexity of Operations**

- **Accessing an element (random access):**

Takes O(1) constant time since elements can be accessed directly using their index numbers, regardless of the data set's size.

- **Searching for an element:**

Takes O(N) linear time. To find a value, you typically need to start at index zero and iterate through the array until the value is found or the end of the array is reached. The time taken increases linearly with the size of the data set. The best case scenario is when our target value is the first element in which case it has an O(1). 

- **Inserting or Deleting an element:**

Takes O(N) linear time. If you insert an element (e.g., at index zero), all subsequent elements must be shifted to the right to make room. Similarly, If you delete an element, all subsequent elements must be shifted to the left to close the gap. But, Inserting or deleting at the end requires no shifting of elements so that just takes O(1) time. 


One major limitation of static arrays is their fixed size: once they reach capacity, no additional elements can be inserted. Expanding them isn't straightforward either, as adjacent memory may already be occupied by other data, preventing a seamless resize.

To overcome this limitation, we turn to a more adaptable structure - dynamic arrays.

## **How dynamic arrays work?** <a name="how-da-works"></a>

A dynamic array inherently uses an inner static array with a fixed size.

When the inner static array of a dynamic array reaches its capacity (i.e., it's full), the dynamic array will "grow":

1. **Declare** and **instantiate** a new array with an increased capacity.
2. The capacity increase usually varies by programming language, typically between **1.5** and **2** times the original capacity (e.g., `capacity * 2`). 
3. Copy all existing elements from the old array to the newly created larger array. These new elements will have different memory addresses.

To avoid wasting space, we may shrink when the array is underused  (e.g., the size falls below a certain threshold like one-third of the capacity). This involves a similar process to growing: creating a new, smaller array (e.g., capacity / 2) and copying the elements over. **But beware** - frequent shrinking/growing can cause **thrashing** (a situation where a program or system spends more time managing memory or resources (like resizing arrays, paging, swapping) than doing useful work). 

### **Pseudocode: Dynamic Array Implementation**

The full code can be found at [`dynamic-array-pseudocode`](/src/dynamic_array.pseudo) .

For detailed explanation go to [`dynamic-array-pseudo-explained`](/src/dynamic_array_pseudo_explained.md) . 

### **Time Complexity of Operations**

- The time complexity for **accessing** and **searching** in a dynamic array is the same as in a static array — O(1) for direct access by index, and O(n) for linear search. 

- **Inserting or Deleting an element:**

In a dynamic array, these operations take O(N) time in the worst case when inserting or deleting at arbitrary positions, since elements may need to be shifted (e.g., inserting at the beginning or middle). However, inserting at the end is typically O(1) on average (amortized time), thanks to pre-allocated space. Similarly, removing the last element also takes O(1) time, as no shifting is required.

### **Advantages of Dynamic Arrays**

1. Fast Random Access - You can directly access any element using its index in O(1) constant time, just like with static arrays.
2. Contiguous Memory (Better Cache Performance) - Since elements are stored in consecutive memory locations, dynamic arrays offer better locality of reference, which helps CPUs cache and process data faster than structures like linked lists.
3. Efficient Insertions and Deletions at the End - Adding or removing elements at the end of the array is very fast - O(1) time in most cases - because no shifting of elements is needed.
4. Automatic Resizing - You don’t have to worry about running out of space. The dynamic array automatically grows when needed, allowing flexible usage without manual memory management.

### **Disadvantages of Dynamic Arrays**

1. Wasted Space (Over-allocation) - To support resizing efficiently, dynamic arrays often allocate more memory than needed. This leads to unused or "reserved" space, which can waste memory.
2. Slow Insertions/Deletions in the Middle - If you insert or delete elements anywhere other than the end, all elements after that position must be shifted, making these operations O(n) in the worst case.
3. Costly Resizing (Expansion/Shrinking) - When the array grows too full (or shrinks too much), a new array is created and all elements are copied over. This resizing process takes O(n) time and can be expensive if it happens frequently.

### **Implementations in _C_ and _python_**

- **Python Version with Error Handling**: [`dynamic-arr-in-py`](src/dynamic_arr.py)

- **C Version with Proper Memory Management**: [`dynamic-arr-in-C`](/src/dynamic_arr.c)
