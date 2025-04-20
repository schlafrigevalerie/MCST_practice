#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct merge_sort_args {
    int left;
    int right;
    int* a;
};

void merge(int a[], int left, int mid, int right) {
    int i1, i2, i3;
    int s1 = mid - left + 1;
    int s2 = right - mid;
    int* leftHalf = malloc(s1 * sizeof(int));
    int* rightHalf = malloc(s2 * sizeof(int));
    for (i1 = 0; i1 < s1; i1++) {
        leftHalf[i1] = a[left + i1];
    }
    for (i2 = 0; i2 < s2; i2++) {
        rightHalf[i2] = a[mid + 1 + i2];
    }

    i1 = 0;
    i2 = 0;
    i3 = left;
    while (i1 < s1 && i2 < s2) {
        if (leftHalf[i1] <= rightHalf[i2]) {
            a[i3] = leftHalf[i1];
            i1++;
        } else {
            a[i3] = rightHalf[i2];
            i2++;
        }
        i3++;
    }
    while (i1 < s1) {
        a[i3] = leftHalf[i1];
        i1++;
        i3++;
    }
    while (i2 < s2) {
        a[i3] = rightHalf[i2];
        i2++;
        i3++;
    }
    free(leftHalf);
    free(rightHalf);
}

void* merge_sort(void* args) {
    struct merge_sort_args* arg = (struct merge_sort_args*)args;
    int left = arg->left;
    int right = arg->right;
    int* arr = arg->a;

    if (left < right) {
        int mid = left + ((right - left) / 2);
        struct merge_sort_args left_args = {left, mid, arr};
        struct merge_sort_args right_args = {mid + 1, right, arr};

        pthread_t left_thread, right_thread;
        pthread_create(&left_thread, NULL, merge_sort, (void*)&left_args);
        pthread_create(&right_thread, NULL, merge_sort, (void*)&right_args);
        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);

        merge(arr, left, mid, right);
    }
    return 0;
}

int main() {
    srand(time(NULL));

    int size = rand() % 10 + 1;
    int* num = malloc(size * sizeof(int));
    int i;

    for (i = 0; i < size; i++) {
        num[i] = rand() % 100;
        printf("%d\n", num[i]);
    }
    printf("\n");

    struct merge_sort_args* args = malloc(sizeof(struct merge_sort_args));
    args->left = 0;
    args->right = size - 1;
    args->a = num;

    pthread_t main_thread;
    pthread_create(&main_thread, NULL, merge_sort, (void*)args);
    pthread_join(main_thread, NULL);

    for (i = 0; i < size; i++) {
        printf("%d ", num[i]);
    }
    printf("\n");

    free(args);
    free(num);
    return 0;
}
