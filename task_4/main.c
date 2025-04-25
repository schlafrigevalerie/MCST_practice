#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
 
int is_valid_elbrus(const char *value) {
    const char *valid[] = {"1c+", "2c+", "2c3", "4c", "8c", "16c"};
    for (int i = 0; i < sizeof(valid)/sizeof(valid[0]); i++) {
        if (strcmp(value, valid[i]) == 0) return 1;
    }
    return 0;
}

