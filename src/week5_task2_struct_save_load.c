/*
 * Name, Surname: Abhimanyujalan.Kaladevi-Shaju
 * Student ID:    241ADB125
 */

/* Week 5 - Task 2: save one Student record to a text file and load it back. */

#include <stdio.h>
#include <string.h>

typedef struct Student {
    char  name[50];
    int   age;
    float gpa;
} Student;

/* Writes "name age gpa" on one line. Returns 0 on success, -1 on error. */
int save_student(const Student *s, const char *filename)
{
    if (s == NULL || filename == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        return -1;
    }

    int written = fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa);
    /* fclose can fail too (e.g. disk full), so check it as well */
    if (fclose(fp) != 0 || written < 0) {
        return -1;
    }
    return 0;
}

/* Reads one record from the file. Returns 0 on success, -1 on error. */
int load_student(const char *filename, Student *out)
{
    if (filename == NULL || out == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1;
    }

    Student tmp;
    memset(&tmp, 0, sizeof tmp);
    /* %49s keeps the name inside the 50-byte array (49 chars + '\0') */
    int n = fscanf(fp, "%49s %d %f", tmp.name, &tmp.age, &tmp.gpa);
    fclose(fp);

    if (n != 3) {
        return -1;
    }
    *out = tmp;
    return 0;
}

int main(void)
{
    Student s;
    memset(&s, 0, sizeof s);
    strcpy(s.name, "Alice");
    s.age = 21;
    s.gpa = 3.75f;

    printf("Saving student to file...\n");
    if (save_student(&s, "student.txt") != 0) {
        fprintf(stderr, "Error: could not save student.\n");
        return 1;
    }

    printf("Loading student from file...\n");
    Student loaded;
    if (load_student("student.txt", &loaded) != 0) {
        fprintf(stderr, "Error: could not load student.\n");
        return 1;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);
    return 0;
}
