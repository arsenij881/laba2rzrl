#include <stdio.h>
#include <string.h>
#include "lab2.h"

void show_help() {
    printf("Usage:\n");
    printf("  ./sed_simplified input.txt -r \"old text\" \"new text\"\n");
    printf("  ./sed_simplified input.txt -d \"text to delete\"\n");
    printf("  ./sed_simplified input.txt -i -f \"text to add at the beginning\"\n");
    printf("  ./sed_simplified input.txt -i -b \"text to add at the end\"\n");
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        show_help();
        return 1;
    }

    const char *filename = argv[1];
    const char *command = argv[2];

    if (strcmp(command, "-r") == 0 && argc == 5) {
        replace_text(filename, argv[3], argv[4]);
    } else if (strcmp(command, "-d") == 0 && argc == 4) {
        delete_lines(filename, argv[3]);
    } else if (strcmp(command, "-i") == 0 && argc == 5) {
    if (strcmp(argv[3], "-f") == 0) {
        insert_text(filename, argv[4], 1);
    } else if (strcmp(argv[3], "-b") == 0) {
        insert_text(filename, argv[4], 0);
    } else {
        show_help();
      return 1;
        }
    } else {
        show_help();
        return 1;
    }

    return 0;
}
