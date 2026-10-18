/*
 * Name, Surname: Abhimanyujalan.Kaladevi-Shaju
 * Student ID:    241ADB125
 */

/* Week 5 - Bonus Task 4: binary vs text storage of a Student record. */

#include <stdio.h>
#include <string.h>

typedef struct Student {
    char  name[50];
    int   age;
    float gpa;
} Student;

/* Text version from Task 2: "name age gpa". */
static int save_student_text(const Student *s, const char *filename)
{
    if (s == NULL || filename == NULL) {
        return -1;
    }
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        return -1;
    }
    int written = fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa);
    if (fclose(fp) != 0 || written < 0) {
        return -1;
    }
    return 0;
}

/* Writes the whole struct as raw bytes. Returns 0 on success, -1 on error. */
int save_student_binary(const Student *s, const char *filename)
{
    if (s == NULL || filename == NULL) {
        return -1;
    }
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        return -1;
    }
    size_t n = fwrite(s, sizeof(Student), 1, fp);
    if (fclose(fp) != 0 || n != 1) {
        return -1;
    }
    return 0;
}

/* Reads the whole struct back. Returns 0 on success, -1 on error. */
int load_student_binary(const char *filename, Student *out)
{
    if (filename == NULL || out == NULL) {
        return -1;
    }
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }
    Student tmp;
    size_t n = fread(&tmp, sizeof(Student), 1, fp);
    fclose(fp);
    if (n != 1) {
        return -1;
    }
    tmp.name[sizeof tmp.name - 1] = '\0';   /* make sure the name is terminated */
    *out = tmp;
    return 0;
}

/* Returns the file size in bytes, or -1 on error. */
long file_size(const char *filename)
{
    if (filename == NULL) {
        return -1;
    }
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }
    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return -1;
    }
    long size = ftell(fp);
    fclose(fp);
    return size;
}

int main(void)
{
    Student s = {0};   /* zero-init so no leftover bytes get written */
    strcpy(s.name, "Alice");
    s.age = 21;
    s.gpa = 3.75f;

    printf("Saving student in binary format...\n");
    if (save_student_binary(&s, "student.bin") != 0) {
        fprintf(stderr, "Error: could not save binary file.\n");
        return 1;
    }
    if (save_student_text(&s, "student.txt") != 0) {
        fprintf(stderr, "Error: could not save text file.\n");
        return 1;
    }

    printf("Loading student from binary file...\n");
    Student loaded = {0};
    if (load_student_binary("student.bin", &loaded) != 0) {
        fprintf(stderr, "Error: could not load binary file.\n");
        return 1;
    }
    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);

    long tsize = file_size("student.txt");
    long bsize = file_size("student.bin");
    if (tsize < 0 || bsize < 0) {
        fprintf(stderr, "Error: could not get file sizes.\n");
        return 1;
    }
    printf("Text file size: %ld bytes\n", tsize);
    printf("Binary file size: %ld bytes\n", bsize);
    return 0;
}
