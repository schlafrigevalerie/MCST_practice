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
    
    printf("Тип файла: %s\n", argv[1]);
    file_type(fileStat.st_mode);

    printf("Размер (Size):                 %lu байт\n", fileStat.st_size);
    printf("Блок В/В (IO Block):  %ld байт\n", fileStat.st_blksize);
    printf("Блоков (Blocks):      %ld\n", fileStat.st_blocks);
    printf("ID устройства:          %lu\n", fileStat.st_rdev);
    printf("Inode:                %ld\n", fileStat.st_ino);
    printf("Ссылки (Links):       %ld\n", fileStat.st_nlink);
    printf("Права:                  %lo\n", (unsigned long)fileStat.st_mode);
    printf("Жёстких ссылок:         %lu\n", fileStat.st_nlink);
    printf("UID:                    %u\n", fileStat.st_uid);
    printf("GID:                    %u\n", fileStat.st_gid);
    printf("Доступ (Access):      %s", ctime(&fileStat.st_atime));
    printf("Модифицирован (Modify): %s", ctime(&fileStat.st_mtime));
    printf("Изменён (Change):     %s", ctime(&fileStat.st_ctime));

    return EXIT_SUCCESS;
}