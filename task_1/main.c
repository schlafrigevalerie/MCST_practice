#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void 
merge(int a[], int left, int mid, int right)
{
    int i1,i2,i3;
    int s1 = mid - left + 1;
    int s2 = right - mid;
    int leftHalf[s1];
    int rightHalf[s2];
    for (i1 = 0; i1 < s1; i1++){
        leftHalf[i1] = a[left + i1];
    }
    for (i2 = 0; i2 < s2; i2++){
        rightHalf[i2] = a[mid + 1 + i2];
    }

    i1 = 0;
    i2 = 0;
    i3 = left;
    while(i1 < s1 && i2 < s2){
        if (leftHalf[i1] <= rightHalf[i2])
        {
            a[i3] = leftHalf[i1];
            i1++;
        } else
        {
            a[i3] = rightHalf[i2];
            i2++;
        }
        i3++;
    }   
    while(i1 < s1){
        a[i3] = leftHalf[i1];
        i1++;
        i3++;
    }
    while(i2 < s2){
        a[i3] = rightHalf[i2];
        i2++;
        i3++;
    }
}

void 
merge_sort(int left, int right, int arr[])
{
    if (left < right){
        int mid = left + ((right - left) / 2);
        merge_sort(left, mid, arr);
        merge_sort(mid + 1, right, arr);
        merge(arr, left, mid, right);
    }
}

int 
main()
{
    srand(time(NULL));
    int size = rand() % 10 + 1;
    int* num = malloc(size * sizeof(int));
    int i;
    for (i = 0; i < size; i++){
        num[i] = rand()%100;
        printf("%d\n", num[i]);
    };

    printf("\n");

    merge_sort(0, size - 1, num);

    for (i = 0; i < size; i++){
        printf("%d ", num[i]);
    };
    free(num);
}

