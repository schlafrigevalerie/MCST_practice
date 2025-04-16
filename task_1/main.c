#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void marge()
{

}

void merge_sort(){

}

int main()
{
    srand(time(NULL));
    int size = rand() % 10 + 1;
    int* num = malloc(size * sizeof(int));
    int i;
    for (i = 0; i < size; i++){
        num[i] = rand()%100;
        printf("%d\n", num[i]);
    };
    free(num);
}

