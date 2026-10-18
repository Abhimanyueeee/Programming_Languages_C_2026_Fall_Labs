/*
 * Name, Surname: Abhimanyujalan.Kaladevi-Shaju
 * Student ID:    241ADB125
 */

/* Week 5 - Task 3: student management system with file persistence. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN     50
#define DATA_FILE    "students.txt"

typedef struct Student {
    char  name[NAME_LEN];
    int   id;
    float gpa;
} Student;

/*
 * Reads one line from stdin into buf (at most size-1 chars), removes the
 * newline and throws away anything that did not fit.
 * Returns 1 on success, 0 on end of input.
 */
static int read_line(char *buf, size_t size)
{
    if (fgets(buf, (int)size, stdin) == NULL) {
        return 0;
    }
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {
        /* line was longer than the buffer: discard the rest of it */
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            /* skip */
        }
    }
    return 1;
}

/* Loads students from students.txt. Returns how many were loaded. */
int load_students(Student arr[], int max)
{
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        return 0;   /* no file yet (first run) is not an error */
    }

    char line[256];
    int count = 0;
    while (count < max && fgets(line, sizeof line, fp) != NULL) {
        Student s;
        memset(&s, 0, sizeof s);
        /* name may contain spaces, so read up to the first comma */
        if (sscanf(line, "%49[^,],%d,%f", s.name, &s.id, &s.gpa) == 3) {
            arr[count++] = s;
        }
        /* blank or malformed lines just fail the sscanf and get skipped */
    }

    fclose(fp);
    return count;
}

/* Overwrites students.txt with all records. Returns 0 on success, -1 on error. */
int save_students(const Student arr[], int count)
{
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL) {
        return -1;
    }

    for (int i = 0; i < count; i++) {
        if (fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa) < 0) {
            fclose(fp);
            return -1;
        }
    }

    if (fclose(fp) != 0) {
        return -1;
    }
    return 0;
}

/* Asks for name, ID and GPA, validates them and appends a new student. */
void add_student(Student arr[], int *count)
{
    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students (limit reached)\n");
        return;
    }

    char name[128], idbuf[64], gpabuf[64];
    char *end;

    printf("Enter name: ");
    if (!read_line(name, sizeof name)) {
        return;
    }
    printf("Enter ID: ");
    if (!read_line(idbuf, sizeof idbuf)) {
        return;
    }
    printf("Enter GPA: ");
    if (!read_line(gpabuf, sizeof gpabuf)) {
        return;
    }

    /* name: not empty, no comma, must fit in the array */
    if (name[0] == '\0' || strchr(name, ',') != NULL || strlen(name) >= NAME_LEN) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    /* ID: whole string must be a number */
    long id = strtol(idbuf, &end, 10);
    if (idbuf[0] == '\0' || *end != '\0') {
        printf("Invalid input. Student not added.\n");
        return;
    }

    /* GPA: whole string must be a number between 0.0 and 4.0 */
    float gpa = strtof(gpabuf, &end);
    if (gpabuf[0] == '\0' || *end != '\0' || !(gpa >= 0.0f && gpa <= 4.0f)) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    strcpy(arr[*count].name, name);
    arr[*count].id  = (int)id;
    arr[*count].gpa = gpa;
    (*count)++;
    printf("Student added successfully!\n");
}

/* Prints all students, one per line. */
void list_students(const Student arr[], int count)
{
    if (count == 0) {
        printf("No students found\n");
        return;
    }

    printf("ID    Name                 GPA\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
    }
}

int main(void)
{
    Student students[MAX_STUDENTS];
    int count = load_students(students, MAX_STUDENTS);
    printf("Loaded %d student(s) from %s\n", count, DATA_FILE);

    char choice[32];
    for (;;) {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");
        printf("Select an option: ");

        /* end of input behaves like option 3 */
        if (!read_line(choice, sizeof choice) || strcmp(choice, "3") == 0) {
            break;
        }

        if (strcmp(choice, "1") == 0) {
            list_students(students, count);
        } else if (strcmp(choice, "2") == 0) {
            add_student(students, &count);
        } else {
            printf("Invalid option. Please try again.\n");
        }
    }

    if (save_students(students, count) != 0) {
        fprintf(stderr, "Error: could not save %s\n", DATA_FILE);
        return 1;
    }
    printf("Data saved. Goodbye!\n");
    return 0;
}
