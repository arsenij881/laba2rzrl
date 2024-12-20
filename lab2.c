#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab2.h"

#define MAX_LINE_LEN 1024

void replace_text(const char *filename, const char *old_text, const char *new_text) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("файла не существует");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        perror("ошибка создания временного файла");
        fclose(file);
        return;
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file)) {
        char *position = strstr(line, old_text);//ищем подстроку
        while (position) {
            *position = '\0';
            fprintf(temp, "%s%s", line, new_text);//печать в файл
            strcpy(line, position + strlen(old_text));
            position = strstr(line, old_text);
        }
        fprintf(temp, "%s", line);
    }

    fclose(file);
    fclose(temp);

    if (remove(filename) == 0) {
        rename("temp.txt", filename);
    }
}

void delete_lines(const char *filename, const char *pattern) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("файла не существует");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
 if (!temp) {
        perror("ошибка создания временного файла");
        fclose(file);
        return;
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file)) {//считывает строку из выбранного файла до конца файла
        if (!strstr(line, pattern)) {
            fprintf(temp, "%s", line);
        }
    }

    fclose(file);
    fclose(temp);

    if (remove(filename) == 0) {
        rename("temp.txt", filename);
    }
}

void insert_text(const char *filename, const char *text, int at_start) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("файла не существует");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        perror("ошибка создания временного файла");
        fclose(file);
        return;
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';//ищет определенный набор символов
        if (at_start) {
            fprintf(temp, "%s%s\n", text, line);
        } else {
            fprintf(temp, "%s%s\n", line, text);
        }
    }

    fclose(file);
    fclose(temp);

    if (remove(filename) == 0) {
 rename("temp.txt", filename);
    }
}
