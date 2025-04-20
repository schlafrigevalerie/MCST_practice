#include <stdio.h>

int
main()
{
    char * file_in;
    char * file_out;
    int type_sort;

    printf("Выберите исходный файл для сортировки: \n");
    scanf("%s", file_in);
    char * filename_in = file_in;
    char message[256];
    printf("Выбранный исходный файл: ");
    printf("%s\n", file_in);
    printf("\n");

    FILE *fp_in = fopen(file_in, "r");
    if(fp_in)
    {
        fgets(message, 256, fp_in);
        fclose(fp_in);
    } 

    printf("Выберите выходной файл для сортировки: \n");
    scanf("%s", file_out);
    char * filename_out = file_out;
    printf("Выбранный выходной файл: ");
    printf("%s\n", file_out);
    printf("\n");

    printf("Выберите тип сортировки (введите номер выбранного варианта): \n");
    printf("1. В алфавитном порядке\n");
    printf("2. В обратном алфавитном порядке \n");
    printf("3. По длине строки (от меньшей к большей)\n");
    printf("4. По длине строки (от большей к меньшей)\n");
    scanf("%d", &type_sort);
    printf("Выбранный тип: ");
    if (type_sort == 1) {
        printf("В алфавитном порядке\n");
    } else if (type_sort == 2){
        printf("В обратном алфавитном порядке \n");
    } else if (type_sort == 3){
        printf("По длине строки (от меньшей к большей)\n");
    } else if (type_sort == 4){
        printf("По длине строки (от большей к меньшей)\n");
    } else {
        printf("Некорректное число, повторите попытку ввода.\n");
        return 0;
    }
    printf("%c\n", type_sort);
    printf("\n");

    FILE *fp_out = fopen(filename_out, "w");
    if(fp_out)
    {
        fputs(message, fp_out);
        fclose(fp_out);
        printf("мяу мяу записалось\n");
    }
}
