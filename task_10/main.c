#include <ctype.h>
#include <string.h>

typedef struct {
    char name;
    int value;
} Variable;

int get_var_value(char var, Variable *vars, int count) {
    for (int i = 0; i < count; i++) {
        if (vars[i].name == var)
            return vars[i].value;
    }
    return 0;
}

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

int precedence(char op) {
    switch (op) {
        case '!': return 3; // NOT
        case '&': return 2; // AND
        case '|': return 1; // OR
        default: return 0;
    }
}

void to_rpn(const char *infix, char *postfix) {
    char ops[512];
    int top = -1, j = 0;
    for (int i = 0; infix[i]; i++) {
        char ch = infix[i];
        if (isspace(ch)) continue;
        if (isalpha(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            ops[++top] = ch;
        } else if (ch == ')') {
            while (top >= 0 && ops[top] != '(') {
                postfix[j++] = ops[top--];
            }
            top--;
        } else {
            while (top >= 0 && precedence(ops[top]) >= precedence(ch)) {
                postfix[j++] = ops[top--];
            }
            ops[++top] = ch;
        }
    }
    while (top >= 0) {
        postfix[j++] = ops[top--];
    }
    postfix[j] = '\0';
}

int eval_rpn(const char *postfix, Variable *vars, int var_count) {
    int stack[512], top = -1;
    for (int i = 0; postfix[i]; i++) {
        char ch = postfix[i];
        if (isalpha(ch)) {
            stack[++top] = get_var_value(ch, vars, var_count);
        } else if (ch == '!') {
            int val = stack[top--];
            stack[++top] = !val;
        } else if (ch == '&') {
            int b = stack[top--];
            int a = stack[top--];
            stack[++top] = a && b;
        } else if (ch == '|') {
            int b = stack[top--];
            int a = stack[top--];
            stack[++top] = a || b;
        }
    }
    return stack[top];
}


int main() {

}
