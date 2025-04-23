#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void copy_and_print(const char* input_file, const char* output_file, int print_after) {
    int in_fd = open(input_file, O_RDONLY);
    if (in_fd < 0) {
        perror("Ошибка при открытии входного файла");
        exit(EXIT_FAILURE);
    }

    int out_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_fd < 0) {
        perror("Ошибка при создании выходного файла");
        close(in_fd);
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    ssize_t bytes_read;
    while ((bytes_read = read(in_fd, buffer, 1024)) > 0) {
        write(out_fd, buffer, bytes_read);
    }

    close(in_fd);
    close(out_fd);

    if (print_after) {
        FILE* out = fopen(output_file, "r");
        if (out) {
            printf("Содержимое файла %s:\n", output_file);
            char ch;
            while ((ch = fgetc(out)) != EOF) {
                putchar(ch);
            }
            fclose(out);
            printf("\n");
        } else {
            perror("Ошибка при открытии файла для чтения");
        }
    }
}
