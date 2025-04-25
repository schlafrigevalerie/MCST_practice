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

int main(int argc, char* argv[]) {
    if (argc != 2) {
    printf("Неверное количество аргументов. Необходимо 2, введено %d", argc);
    exit(EXIT_FAILURE);
  }

    const char* input_file = argv[1];
    const char* child_output = "child_output.txt";
    const char* parent_output = "parent_output.txt";

    pid_t pid = fork();

    if (pid < 0) {
        perror("Ошибка при вызове fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        copy_and_print(input_file, child_output, 1);
        exit(EXIT_SUCCESS);
    } else {
        wait(NULL); 
        copy_and_print(input_file, parent_output, 1);
    }

    return 0;
    
}