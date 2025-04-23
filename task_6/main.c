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
            printf("Тип: Обычный файл\n");
            break;
        case S_IFDIR:
            printf("Тип: Каталог\n");
            break;
        case S_IFCHR:
            printf("Тип: Символьное устройство\n");
            break;
        case S_IFBLK:
            printf("Тип: Блочное устройство\n");
            break;
        case S_IFIFO:
            printf("Тип: Канал FIFO\n");
            break;
        case S_IFLNK:
            printf("Тип: Символическая ссылка\n");
            break;
        case S_IFSOCK:
            printf("Тип: Сокет\n");
            break;
        default:
            printf("Тип: Неизвестно\n");
            break;
    }
}