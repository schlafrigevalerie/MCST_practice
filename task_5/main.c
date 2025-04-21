#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main() {
    const char *filename = "nonexistent_file.txt";
    int fd = open(filename, O_RDONLY); 

    if (fd == -1) {
        printf("1. Ошибка во время системного вызова open(). Код ошибки (errno): %d\n", errno);

        printf("2. Описание ошибки (strerror): %s\n", strerror(errno));//sys_errlist устарел, используется strerror()

        printf("3. perror(): ");
        perror("Ошибка при открытии файла");

        printf("4. Некорректные данные или отсутствует файл: %s\n", filename);
    } else {
        close(fd);
    }

    return 0;
}
