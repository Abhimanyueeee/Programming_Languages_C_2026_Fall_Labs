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

int main(void)
{
    int n;

    printf("Enter number of elements: ");
    /* scanf returns 1 only if a number was really read, so this also catches text input */
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    /* allocate n ints; sizeof(int) keeps it correct on any platform */
    int *arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers: ", n);
    long long sum = 0; /* long long so a big sum doesn't overflow */
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            /* free first, otherwise we leak the array on the error path */
            free(arr);
            printf("Invalid input.\n");
            return 1;
        }
        sum += arr[i];
    }

    /* cast to double before dividing, otherwise it would be integer division (7 8 -> 7.00) */
    double average = (double)sum / n;

    printf("Sum = %lld\n", sum);
    printf("Average = %.2f\n", average);

    free(arr); /* every successful malloc gets a free */
    return 0;
}
