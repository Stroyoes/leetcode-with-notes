#include "dynamic_arr.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

const size_t Initial_Capacity = 10;
const float Growth_Factor = 1.5f;

// A helper function, only accessible within this file 
static int resize_if_needed(dynamic_arr_t *dynamic_arr) {
  if (dynamic_arr->arr_size >= dynamic_arr->capacity) {
    size_t new_capacity = (size_t)(dynamic_arr->capacity * Growth_Factor);

    void *new_block = realloc(dynamic_arr->array, new_capacity * dynamic_arr->item_size);

    if (!new_block) {
      fprintf(stderr, "\nERROR: Memory allocation failed!\n");
      return -1; // Indicating an error 
    }

    dynamic_arr->array = new_block;
    dynamic_arr->capacity = new_capacity;
  }
  return 0;
}

dynamic_arr_t *dynamic_arr_init(size_t item_size) {
  dynamic_arr_t *dynamic_arr = malloc(sizeof(item_size));

  if (!dynamic_arr) {
    fprintf(stderr, "\nERROR: Failed allocating space for the dynamic arr struct!\n");

    return NULL;
  }

  dynamic_arr->item_size = item_size;
  dynamic_arr->capacity = Initial_Capacity;
  dynamic_arr->arr_size = 0; // No elements in the array 
  dynamic_arr->array = malloc(item_size * Initial_Capacity);

  if (!dynamic_arr->array) {
    free(dynamic_arr);

    fprintf(stderr, "\nERROR: Failed allocating the buffer for the dynamic array!\n");

    return NULL;
  }
  
  return dynamic_arr;
}

//  INFO: A detailed explanation is given for one function. The other functions work in a similar manner.

// Retrieves the element at the specified index and stores it in output 
int dynamic_arr_get(dynamic_arr_t *dynamic_arr, size_t index, void *output){ 
  //  NOTE: Here '*output' is a pointer to memory where the data should be copied

  if (!dynamic_arr) {
    fprintf(stderr, "\nERROR: The dynamic array wasn't initialized correctly!\n");
    return -1;
  } else if (index >= dynamic_arr->arr_size) {
    fprintf(stderr, "\nERROR: Index out of bounds!\n");
    return -1;
  } else if (!output) {
    fprintf(stderr, "\nERROR: Missing the pointer to memory where the element at index should be copied to!\n");
    return -1;
  }

  /** 
   * Inside the function, assuming:
   * - 'array' points to 'myIntArray'
   * - 'index' is 2
   * - 'output' points to '&retrievedValue' (an 'int' variable's memory location)
   * - Also no errors were encountered so far.
   * - Let the array be [10, 20, 30, 40, ...]
   *
   * Calculate offset:
   * offset = 2 * 4; // Assuming item size is 4 bytes for an int
   * offset = 8;
   *
   * Explanation: To find the 3rd element (at index 2), we need to
   * move 8 bytes (2 items * 4 bytes/item) from the beginning of the array's
   * internal memory block.
   */
  size_t memory_offset = index * dynamic_arr->item_size;

  /**
   * Copy data using memcpy:
   *
   * Let's visualize the memory:
   * Assume dynamic_arr->array starts at memory address 0x1000
   *
   * Memory Layout:
   * Address | Value (int) | Bytes (char)
   * ----------------------------------------------------------------
   * 0x1000  | 10          | 0x0A 0x00 0x00 0x00
   * 0x1004  | 20          | 0x14 0x00 0x00 0x00
   * 0x1008  | 30          | 0x1E 0x00 0x00 0x00  <-- Target element starts here
   * 0x100C  | 40          | 0x28 0x00 0x00 0x00
   * ...
   *
   * Breakdown of memcpy arguments:
   * - destination: 'output' (e.g., memory address 0x2000 for 'retrievedValue')
   *
   * - source: '(char *)dynamic_arr->array + offset'
   * - 'dynamic_arr->array' is 0x1000
   * - '(char *)dynamic_arr->array' casts it to a 'char*' for byte-level arithmetic.
   * - '0x1000 + 8' results in the memory address '0x1008'.
   * This is the exact starting address of the integer '30' in memory.
   *
   * - number of bytes: 'dynamic_array->item_size' which is 4.
   *
   * What 'memcpy' does:
   * It copies 4 bytes of data starting from memory address 0x1008
   * (which contains the byte representation of '30')
   * to the memory address 0x2000 (where 'retrievedValue' is stored).
   *
   * After memcpy, 'retrievedValue' will now hold the integer '30'.
   */
  memcpy(output, (char *)(dynamic_arr->array + memory_offset), dynamic_arr->item_size);

  return 0;
}

// Sets the value at the specified index in the dynamic array
int dynamic_arr_set(dynamic_arr_t *dynamic_arr, size_t index, const void *input) {

  if (!dynamic_arr) {
    fprintf(stderr, "\nERROR: The dynamic array wasn't initialized correctly!\n");
    return -1;
  } else if (index >= dynamic_arr->arr_size) {
    fprintf(stderr, "\nERROR: Index out of bounds!\n");
    return -1;
  } else if (!input) {
    fprintf(stderr, "\nERROR: Missing the pointer to the data to be stored at the specified index in the array!\n");
    return -1;
  }

  size_t memory_offset = index * dynamic_arr->item_size;

  memcpy((char *)dynamic_arr->array + memory_offset, input, dynamic_arr->item_size);

  return 0;
}



