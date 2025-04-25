#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20  
#define MAX_VALUE 50

int main() {
    int arr[SIZE];
    srand(time(NULL));
    printf("Массив: ");
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % MAX_VALUE;
        printf("%d ", arr[i]);
    }
    printf("\n");
    int max_sum = arr[0];
    int curr_sum = arr[0];
    int start = 0, end = 0, temp_start = 0;

    for (int i = 1; i < SIZE; i++) {
        if (arr[i] > arr[i - 1]) {
            curr_sum += arr[i];
        } else {
            if (curr_sum > max_sum) {
                max_sum = curr_sum;
                start = temp_start;
                end = i - 1;
            }
            curr_sum = arr[i];
            temp_start = i;
        }
    }
    
    if (curr_sum > max_sum) {
        max_sum = curr_sum;
        start = temp_start;
        end = SIZE - 1;
    }
    printf("Максимальная возрастающая подпоследовательность с максимальной суммой: ");
    for (int i = start; i <= end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nСумма: %d\n", max_sum);
    return 0;
}
