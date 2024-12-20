#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 1024

void replace_text(const char *filename, const char *old_text, const char *new_text) {
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file)) {
        char *position = strstr(line, old_text);
        while (position) {
            *position = '\0';
            fprintf(temp, "%s%s", line, new_text);
            strcpy(line, position + strlen(old_text));
            position = strstr(line, old_text);
        }
        fprintf(temp, "%s", line);
    }

    fclose(file);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);
}

void delete_lines(const char *filename, const char *pattern) {
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file)) {
        if (!strstr(line, pattern)) {
            fprintf(temp, "%s", line);
        }
    }

    fclose(file);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);
}

void insert_text(const char *filename, const char *text, int at_start) {
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline character
        if (at_start) {
            fprintf(temp, "%s%s\n", text, line);
        } else {
            fprintf(temp, "%s%s\n", line, text);
        }
    }

    fclose(file);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);
}

void show_help() {
    printf("Usage:\n");
    printf("  ./sed_simplified input.txt -r \"old text\" \"new text\"\n");
    printf("  ./sed_simplified input.txt -d \"text to delete\"\n");
    printf("  ./sed_simplified input.txt -i -f \"text to add at the beginning\"\n");
    printf("  ./sed_simplified input.txt -i -b \"text to add at the end\"\n");
}

int main(int argc, char *argv[]) {
    const char *filename = argv[1];
    const char *command = argv[2];

    if (strcmp(command, "-r") == 0) {
        replace_text(filename, argv[3], argv[4]);
    } else if (strcmp(command, "-d") == 0) {
        delete_lines(filename, argv[3]);
    } else if (strcmp(command, "-i") == 0) {
        if (strcmp(argv[3], "-f") == 0) {
            insert_text(filename, argv[4], 1);
        } else if (strcmp(argv[3], "-b") == 0) {
            insert_text(filename, argv[4], 0);
        }
    }

    return 0;
}
