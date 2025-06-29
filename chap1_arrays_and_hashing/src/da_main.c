// Rename this file to main.c

#include <stdio.h>

#include "dynamic_arr.h"

// Print function for integers (required by dynamic_arr_display)
void print_int(const void *item) {
    printf("%d", *(const int *)item);
}

int main() {
    // Initialize a dynamic array for integers
    dynamic_arr_t *arr = dynamic_arr_init(sizeof(int));
    if (!arr) {
        return 1; // Exit if initialization failed
    }

    // Append elements [10, 20, 30]
    int a = 10, b = 20, c = 30;
    dynamic_arr_append(arr, &a);
    dynamic_arr_append(arr, &b);
    dynamic_arr_append(arr, &c);

    printf("After appending 10, 20, 30:\n");
    dynamic_arr_display(arr, print_int); // [10, 20, 30]

    // Insert 15 at index 1
    int x = 15;
    dynamic_arr_append_at(arr, 1, &x);
    printf("After inserting 15 at index 1:\n");
    dynamic_arr_display(arr, print_int); // [10, 15, 20, 30]

    // Get element at index 2
    int value;
    if (dynamic_arr_get(arr, 2, &value) == 0) {
        printf("Element at index 2: %d\n", value); // Should be 20
    }

    // Set element at index 2 to 25
    int newVal = 25;
    dynamic_arr_set(arr, 2, &newVal);
    printf("After setting index 2 to 25:\n");
    dynamic_arr_display(arr, print_int); // [10, 15, 25, 30]

    // Remove element at index 1 (15)
    dynamic_arr_remove_at(arr, 1);
    printf("After removing element at index 1:\n");
    dynamic_arr_display(arr, print_int); // [10, 25, 30]

    // Pop last element
    dynamic_arr_pop(arr);
    printf("After popping last element:\n");
    dynamic_arr_display(arr, print_int); // [10, 25]

    // Size and Capacity
    printf("Size: %zu\n", dynamic_arr_get_size(arr));
    printf("Capacity: %zu\n", dynamic_arr_get_capacity(arr));

    // Clean up
    dynamic_arr_dispose(arr);

    return 0;
}

