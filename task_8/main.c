#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define SIZE 1000

int row = 0, col = 0;
int sigint_count = 0;

void sigint_handler(int sig) {
    if (sigint_count == 0) {
        printf("\n[signal()] Caught SIGINT! Current row = %d, col = %d\n", row, col);
        signal(SIGINT, SIG_DFL);  // Восстановить поведение по умолчанию
        sigint_count++;
    }
}

int main() {
    int **A = malloc(SIZE * sizeof(int*));
    int **B = malloc(SIZE * sizeof(int*));
    int **C = malloc(SIZE * sizeof(int*));
    for (int i = 0; i < SIZE; i++) {
        A[i] = malloc(SIZE * sizeof(int));
        B[i] = malloc(SIZE * sizeof(int));
        C[i] = malloc(SIZE * sizeof(int));
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = 1;
            B[i][j] = 1;
            C[i][j] = 0;
        }
    }

    signal(SIGINT, sigint_handler);

    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            for (int k = 0; k < SIZE; k++) {
                C[row][col] += A[row][k] * B[k][col];
            }
            sleep(1);  // Задержка в 1 секунду
        }
    }

    printf("Multiplication complete.\n");

    // Освобождение памяти
    for (int i = 0; i < SIZE; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
