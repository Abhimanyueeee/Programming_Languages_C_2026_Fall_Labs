/*
 * Name, Surname: Abhimanyujalan.Kaladevi-Shaju
 * Student ID:    241ADB125
 */

/* Week 5 - Task 1: write a few lines to a text file, then read them back. */

#include <stdio.h>

int main(int argc, char *argv[])
{
    /* default file name, can be overridden from the command line */
    const char *filename = "data.txt";
    if (argc > 1) {
        filename = argv[1];
    }

    /* ---- writing ---- */
    printf("Writing lines to %s...\n", filename);
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("fopen (write)");
        return 1;
    }
    fprintf(fp, "Hello, file I/O in C!\n");
    fprintf(fp, "This is another line.\n");
    fclose(fp);

    /* ---- reading ---- */
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fopen (read)");
        return 1;
    }

    printf("Reading contents:\n");
    char line[256];
    int count = 0;
    while (fgets(line, sizeof line, fp) != NULL) {
        printf("%s", line);
        count++;
    }
    fclose(fp);

    printf("Lines read: %d\n", count);
    return 0;
}
