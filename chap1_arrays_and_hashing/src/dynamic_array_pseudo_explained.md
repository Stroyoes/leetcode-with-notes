# Explanation of the dynamic array pseudocode 

---

```
Class Dynamic_Array
```

> 💡 _**Explanation:**_
>
> * `Class` defines a blueprint or structure for an object—in this case, a dynamic array.
> * The class encapsulates both **data (attributes)** and **operations (methods)**.
> * This structure helps bundle related operations and data, mimicking real-world objects in code.

---

```

  Attributes
    array <- new array of ints of size 1 
    size <- 0 // Number of elements currently stored
    capacity <- 1 // Current capacity of the array 

```

> 💡 _**Explanation:**_
> 
> * `Attributes` lists the internal data (state) maintained by the object.
> * `array` is the internal storage — starts with size 1.
> * `size` tracks how many valid elements are currently stored.
> * `capacity` is the maximum number of elements that can be held before resizing is needed.
> * These should ideally be **private**, meaning they are internal to the class and not directly accessible outside. Why? To enforce **encapsulation** and prevent accidental or invalid modifications.

---

```
  Method add(element)
    If size = capacity Then
      Call resize_array()
    array[size] <- element 
    size <- size + 1
```

> 💡 _**Explanation:**_
> 
> * `Method` defines a reusable function within the class.
> * This method adds a new `element` at the end of the array.
> * If the array is full (`size == capacity`), it calls `resize_array` to expand.
> * The new element is placed at the next available index, and `size` is incremented.
> * This operation maintains **amortized constant time** efficiency.

---

```
  Method resize_array()
    new_capacity <- capacity * 2
    new_array <- new array of ints of size new_capacity
    For i <- 0 To size - 1 Do 
      new_array[i] <- array[i]
    End For 

    array <- new_array
    capacity <- new_capacity

```

> 💡 _**Explanation:**_
> 
> * This method **doubles the current capacity** to allow more insertions.
> * A new array is created with `new_capacity`.
> * Elements from the old array are copied into the new one using a loop.
> * Finally, the internal pointer `array` is updated to the new array, and `capacity` is adjusted.
> * Doubling strategy helps maintain **efficient resizing** with fewer operations overall.

---

```
  Method shrink_array()
    If size > 0 Then 
      new_capacity <- Max(1, size) 
      new_array <- new array of ints of size new_capacity
      For i <- 0 To size - 1 Do 
        new_array[i] <- array[i]
      End For 

      array <- new_array 
      capacity <- new_capacity 
    End If 
```

> 💡 _**Explanation:**_
> 
> * This method reduces memory usage by **shrinking the array** to just fit the current number of elements.
> * Ensures `capacity` doesn't fall below 1.
> * Creates a smaller array and copies elements over.
> * Helps **release unused memory**, useful in memory-constrained systems.

---

```
  Method add_at(index, element)
    If index < 0 Or index > size Then 
      Return "Index out of bounds"
    End If 

    If size = capacity Then 
      Call resize_array()

    For i <- size - 1 DownTo index Do 
      array[i + 1] <- array[i]
    End For 

    array[index] <- element 
    size <- size + 1 

```

> 💡 _**Explanation:**_
> 
> * This method inserts an element at a specific position.
> * First, it checks if the index is within valid bounds.
> * If full, it resizes the array.
> * Then it shifts elements from the index rightward to make space.
> * Finally, the new element is inserted and `size` is updated.
> * This operation is **O(n)** in the worst case due to shifting.

---

```
  Method remove()
    If size > 0 Then 
      array[size - 1] <- NULL // Optional: clear value      
      size <- size - 1
    End If 

```

> 💡 _**Explanation:**_
> 
> * Removes the **last element** from the array.
> * Decreases `size` by one.
> * Optionally clears the value (helps in languages with manual memory or GC).
> * Does **not shrink** memory unless explicitly called.

---

```
  Method remove_at(index)
    If index < 0 Or index >= size Then 
      Return "Index out of bounds"
    End If 

    For i <- index To size - 2 Do 
      array[i] <- array[i + 1]
    End For 

    array[size - 1] <- NULL // Optional: clear value
    size <- size - 1 
```

> 💡 _**Explanation:**_
> 
> * Removes an element at the given `index`.
> * First validates the index.
> * Shifts all elements after the index left by one.
> * Optionally clears the last slot, then reduces `size`.
> * Like `add_at`, this is **O(n)** due to shifting.

---

```
  Method get_element(index) 
    If index < 0 Or index >= size Then 
      Return "Index out of bounds"
    End If
    
    Return array[index] 
```

> 💡 _**Explanation:**_
> 
> * Safely retrieves the value at a given index.
> * If the index is invalid, returns an error.
> * Otherwise, returns the value at that index.
> * **O(1)** access time.

---

```
  Method set_element(index, element)
    If index < 0 Or index >= size Then 
      Return "Index out of bounds"
    End If

    array[index] <- element
```

> 💡 _**Explanation:**_
> 
> * Updates the value at a specific index.
> * Index must be valid; otherwise, return error.
> * Performs **in-place modification**, with constant time complexity.

---

```
  Method get_size()
    Return size 
```

> 💡 _**Explanation:**_
> 
> * Returns how many elements are currently stored.
> * A **simple getter** method.

---

```
  Method get_capacity()
    Return capacity
```

> 💡 _**Explanation:**_
> 
> * Returns the total allocated capacity of the array.
> * Useful for diagnostics or internal logic.

---

```
  Method print_array()
    For i <- 0 To size - 1 Do 
      Print array[i]
    End For 
```

> 💡 _**Explanation:**_
> 
> * Iterates over all valid elements and prints them.
> * Helpful for **debugging** and visualizing array contents.
> * Stops at `size - 1` to avoid printing garbage/uninitialized values.
