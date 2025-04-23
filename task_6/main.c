#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void file_type(mode_t mode) {
    switch (mode & S_IFMT) {
        case S_IFREG:
            printf("Тип: обычный файл\n");
            break;
        case S_IFDIR:
            printf("Тип: каталог\n");
            break;
        case S_IFCHR:
            printf("Тип: символьное устройство\n");
            break;
        case S_IFBLK:
            printf("Тип: блочное устройство\n");
            break;
        case S_IFIFO:
            printf("Тип: канал FIFO\n");
            break;
        case S_IFLNK:
            printf("Тип: символическая ссылка\n");
            break;
        case S_IFSOCK:
            printf("Тип: сокет\n");
            break;
        default:
            printf("Тип: неизвестно\n");
            break;
    }
}

int main(int argc, char *argv[]){
    //проверка данных
    if (argc != 2) {
        fprintf(stderr, "Некоректные данные\n");
        exit(EXIT_FAILURE);
    }

    struct stat fileStat;
    //проверяем успешность завершения вызова
    if (stat(argv[1], &fileStat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
}