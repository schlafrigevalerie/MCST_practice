#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1024
#define MAX_LINE_LEN 256

int 
alpha_sort(const void *a, const void *b) 
{
    return strcmp(*(const char **)a, *(const char **)b);
}

int 
reverse_alpha_sort(const void *a, const void *b) 
{
    return -strcmp(*(const char **)a, *(const char **)b);
}

int 
length_sort(const void *a, const void *b) 
{
    return strlen(*(const char **)a) - strlen(*(const char **)b);
}

int 
reverse_length_sort(const void *a, const void *b) 
{
    return strlen(*(const char **)b) - strlen(*(const char **)a);
}

int 
main() 
{
    char file_in[256];
    char file_out[256];
    int type_sort;

    printf("Выберите исходный файл для сортировки:\n");
    scanf("%255s", file_in);

    printf("Выберите выходной файл:\n");
    scanf("%255s", file_out);

    printf("Выберите тип сортировки (введите номер):\n");
    printf("1. В алфавитном порядке\n");
    printf("2. В обратном алфавитном порядке\n");
    printf("3. По длине строки (от меньшей к большей)\n");
    printf("4. По длине строки (от большей к меньшей)\n");
    scanf("%d", &type_sort);

    FILE *fin = fopen(file_in, "r");
    if (!fin) {
        perror("Ошибка при открытии входного файла");
        return 1;
    }
    char *lines[MAX_LINES];
    int count = 0;
    char buffer[MAX_LINE_LEN];

    while (fgets(buffer, sizeof(buffer), fin) && count < MAX_LINES) {
        lines[count] = strdup(buffer); // копируем строку
        if (!lines[count]) {
            perror("Ошибка при выделении памяти");
            fclose(fin);
            return 1;
        }
        count++;
    }
    fclose(fin);

    int (*cmp)(const void *, const void *);
    switch (type_sort) {
        case 1: cmp = alpha_sort; break;
        case 2: cmp = reverse_alpha_sort; break;
        case 3: cmp = length_sort; break;
        case 4: cmp = reverse_length_sort; break;
        default:
            printf("Неверный тип сортировки.\n");
            return 1;
    }

    qsort(lines, count, sizeof(char *), cmp);

    FILE *fout = fopen(file_out, "w");
    if (!fout) {
        perror("Ошибка при открытии выходного файла");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        fputs(lines[i], fout);
        free(lines[i]); // Освобождаем память
    }

    fclose(fout);
    printf("Сортировка завершена и записана в файл %s\n", file_out);
    return 0;
}
