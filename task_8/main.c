#include <stdio.h>
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
