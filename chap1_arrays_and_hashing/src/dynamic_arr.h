#ifndef DYNAMIC_ARR_H
#define DYNAMIC_ARR_H

#include <stdlib.h>

typedef struct {
  size_t item_size; // The size of a single item 
  size_t capacity; // The capacity of the array, i.e. how much room until resize is needed 
  size_t arr_size; // Actual number of items, always <= capacity 
  void *array; // Generic pointer to the raw memory buffer holding all elements
} dynamic_arr_t;

dynamic_arr_t *dynamic_arr_init(size_t item_size); 
int dynamic_arr_get(dynamic_arr_t *dynamic_arr, size_t index, void *output); 

/**
 * Replaces the element at the specified index with a new value
 * Does not increase the size of the array
 * Fails if the index is out of bounds (i.e., >= arr_size)
 */
int dynamic_arr_set(dynamic_arr_t *dynamic_arr, size_t index, const void *input); 

int dynamic_arr_append(dynamic_arr_t *dynamic_arr, const void *input);

/**
 * Inserts a new element at the specified index and shifts subsequent elements to the right
 * Increases the arr_size by one
 * Valid index is from 0 to arr_size (inclusive)
 * Fails if index is invalid or memory reallocation Fails
 */
int dynamic_arr_append_at(dynamic_arr_t *dynamic_arr, size_t index, const void *input);

int dynamic_arr_remove(dynamic_arr_t *dynamic_arr);
int dynamic_arr_remove_at(dynamic_arr_t *dynamic_arr, size_t index);

size_t dynamic_arr_get_size(dynamic_arr_t *dynamic_arr);
size_t dynamic_arr_get_capacity(dynamic_arr_t *dynamic_arr);

/** 
 * Prints all elements in the dynamic array using a user-provided print function.
 * Since the array is generic (void *), the caller must supply a function 
 * that knows how to print the specific data type stored in the array.
 * print_func is a pointer (*) to a function that takes (const void *) and returns (void).
 */
void dynamic_arr_display(dynamic_arr_t *dynamic_arr, void (*print_func)(const void *item));

/**
 * Free all the allocated spaces for the array 
 */ 
void dynamic_arr_dispose(dynamic_arr_t *dynamic_arr);

#endif
