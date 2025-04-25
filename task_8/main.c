#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define SIZE 1000

volatile sig_atomic_t sigint_received = 0;
volatile int current_i = 0;
volatile int current_j = 0;
//используем signal()
void handle_sigint(int sig) {
    if (!sigint_received) {
        printf("\nSIGINT received. Current indices: i = %d, j = %d\n", current_i, current_j);
        sigint_received = 1;
        signal(SIGINT, SIG_DFL); // восстанавливаем поведение по умолчанию
    }
}

int main() {
    static int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = 1;
            B[i][j] = 2;
        }
    }
    signal(SIGINT, handle_sigint); //обработчик сигнала
    //перемножаем матрицы
    for (int i = 0; i < SIZE; i++) {
        current_i = i;
        for (int j = 0; j < SIZE; j++) {
            current_j = j;
            C[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
            sleep(1); 
        }
    }
    printf("Multiplication completed.\n");
    return 0;
}
