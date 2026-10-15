/*
 * week4_1_dynamic_array.c
 * Author: Abhimanyujalan.Kaladevi-Shaju
 * Student ID: 241ADB125
 * Description:
 *   Demonstrates creation and usage of a dynamic array using malloc.
 *   Allocate memory for n integers, read them from the user,
 *   print their sum and average, and then free the memory.
 *
 *   Output must match the format in the Week 4 instructions exactly
 *   (it is checked by the autograder).
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    int *arr = NULL;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    // Allocate space for n ints; sizeof(int) keeps the size correct on any platform
    arr = malloc(n * sizeof(int));

    // malloc returns NULL if it fails, so check before using the pointer
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers: ", n);
    long long sum = 0;  // long long so a big sum doesn't overflow an int
    for (int i = 0; i < n; i++) {
        // scanf returns 1 only if an integer was really read
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input.\n");
            free(arr);  // free before exiting so the error path doesn't leak memory
            return 1;
        }
        sum += arr[i];
    }

    // Cast to double before dividing, otherwise it is integer division (7 8 would give 7.00)
    double average = (double)sum / n;

    printf("Sum = %lld\n", sum);
    printf("Average = %.2f\n", average);

    // Every successful malloc needs a free
    free(arr);

    return 0;
}
