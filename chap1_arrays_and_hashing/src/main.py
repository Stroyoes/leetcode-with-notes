from dynamic_arr import DynamicArray

arr = DynamicArray()

# Append some values
arr.append(10)
arr.append(20)
arr.append(30)
arr.insert_at(1, 15)
arr.display()  # [10, 15, 20, 30]

# Get and print a value at index 2
print("Value at index 2:", arr.get(2))  # 20

# Set index 2 to 25
arr.set(2, 25)
arr.display()  # [10, 15, 25, 30]

# Remove element at index 1
arr.remove_at(1)
arr.display()  # [10, 25, 30]

# Pop the last element
arr.pop()
arr.display()  # [10, 25]

# Size and Capacity
print("Size:", arr.size())
print("Capacity:", arr.capacity())

# Cleanup - remove eveything 
arr.clear()

