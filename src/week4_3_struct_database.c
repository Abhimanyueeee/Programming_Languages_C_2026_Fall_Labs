/*
 * week4_3_struct_database.c
 * Author: Abhimanyujalan.Kaladevi-Shaju
 * Student ID: 241ADB125
 * Description:
 *   Simple in-memory "database" using an array of structs.
 *   Use malloc to allocate space for n Student records,
 *   read each record from the user, print them as a table,
 *   and then free the memory.
 *
 *   Output must match the format in the Week 4 instructions exactly
 *   (it is checked by the autograder).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Same Student definition as in Task 2
struct Student {
    char name[50];
    int id;
    float grade;
};

int main(void) {
    int n;
    struct Student *students = NULL;

    printf("Enter number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number.\n");
        return 1;
    }

    // One block of memory big enough to hold n Student records
    students = malloc(n * sizeof(struct Student));

    // malloc can fail and return NULL, so check before using the pointer
    if (students == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter data for student %d: ", i + 1);

        // %49s leaves room for the '\0' so a long name can't overflow name[50]
        // scanf returns 3 only if name, id and grade were all read correctly
        if (scanf("%49s %d %f", students[i].name, &students[i].id, &students[i].grade) != 3) {
            printf("Invalid input.\n");
            free(students);  // free before exiting so the error path doesn't leak memory
            return 1;
        }
    }

    // Empty line, then the table header and one row per student in input order
    printf("\n");
    printf("%-6s %-11s %s\n", "ID", "Name", "Grade");
    for (int i = 0; i < n; i++) {
        printf("%-6d %-11s %.1f\n", students[i].id, students[i].name, students[i].grade);
    }

    // Done with the records, give the memory back
    free(students);

    return 0;
}

    return 0;
}
