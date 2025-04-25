#include <string.h>

typedef struct {
    char name;
    int value;
} Variable;

void normalize(char *expr) {
    char tmp[512];
    int j = 0;
    for (int i = 0; expr[i]; ) {
        if (strncmp(&expr[i], "AND", 3) == 0) {
            tmp[j++] = '&';
            i += 3;
        } else if (strncmp(&expr[i], "OR", 2) == 0) {
            tmp[j++] = '|';
            i += 2;
        } else if (strncmp(&expr[i], "NOT", 3) == 0) {
            tmp[j++] = '!';
            i += 3;
        } else {
            tmp[j++] = expr[i++];
        }
    }
    tmp[j] = '\0';
    strcpy(expr, tmp);
}

int main() {

}
