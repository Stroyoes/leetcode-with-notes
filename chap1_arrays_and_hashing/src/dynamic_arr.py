class DynamicArray:
    """A simple generic dynamic array class in Python."""

    def __init__(self, initial_capacity=10):
        """
        Initialize the dynamic array.
        
        Parameters:
        - initial_capacity (int): Initial size of the underlying list before resizing is needed.
        """
        self._capacity = initial_capacity
        self._size = 0
        self._array = [None] * self._capacity  # Internal static array simulation

    def _resize(self):
        """Doubles the array capacity when full."""
        new_capacity = int(self._capacity * 1.5)
        new_array = [None] * new_capacity
        for i in range(self._size):
            new_array[i] = self._array[i]

        self._array = new_array
        self._capacity = new_capacity

    def append(self, item):
        """Appends an item to the end of the array."""
        if self._size >= self._capacity:
            self._resize()
        self._array[self._size] = item
        self._size += 1

    def insert_at(self, index, item):
        """
        Inserts an item at a specific index and shifts others.
        
        Raises:
        - IndexError if index is out of bounds (0 to size inclusive)
        """
        if index < 0 or index > self._size:
            raise IndexError("Index out of bounds")
        if self._size >= self._capacity:
            self._resize()
        for i in range(self._size, index, -1):
            self._array[i] = self._array[i - 1]
        self._array[index] = item
        self._size += 1

    def get(self, index):
        """
        Returns the element at the specified index.
        
        Raises:
        - IndexError if index is out of bounds
        """
        if index < 0 or index >= self._size:
            raise IndexError("Index out of bounds")
        return self._array[index]

    def set(self, index, item):
        """
        Replaces the element at the specified index.
        
        Raises:
        - IndexError if index is out of bounds
        """
        if index < 0 or index >= self._size:
            raise IndexError("Index out of bounds")
        self._array[index] = item

    def pop(self):
        """
        Removes the last element from the array.
        
        Raises:
        - IndexError if array is empty
        """
        if self._size == 0:
            raise IndexError("Pop from empty array")
        self._size -= 1
        val = self._array[self._size]
        self._array[self._size] = None  # Help GC
        return val

    def remove_at(self, index):
        """
        Removes the element at the specified index and shifts remaining elements.
        
        Raises:
        - IndexError if index is out of bounds
        """
        if index < 0 or index >= self._size:
            raise IndexError("Index out of bounds")
        removed_value = self._array[index]
        for i in range(index, self._size - 1):
            self._array[i] = self._array[i + 1]
        self._array[self._size - 1] = None
        self._size -= 1
        return removed_value

    def size(self):
        """Returns the number of elements in the array."""
        return self._size

    def capacity(self):
        """Returns the current capacity of the array."""
        return self._capacity

    def display(self):
        """Prints the contents of the dynamic array."""
        print("[", end="")
        for i in range(self._size):
            print(self._array[i], end=", " if i < self._size - 1 else "")
        print("]")

    def clear(self):
        """Clears the dynamic array removing all data."""
        self._array = []
        self._size = 0
        self._capacity = 0

