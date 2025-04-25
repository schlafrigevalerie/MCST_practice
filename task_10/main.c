#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char name;
    int value;
} Variable;

int get_var_value(char ch, Variable *vars, int var_count) {
    for (int i = 0; i < var_count; i++) {
        if (vars[i].name == ch) return vars[i].value;
    }
    fprintf(stderr, "Error: Undefined variable '%c'\n", ch);
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

int to_rpn(const char *expr, char *output) {
    char stack[512];
    int top = -1;
    int out_i = 0;
    int open_parens = 0;

    for (int i = 0; expr[i]; ++i) {
        if (isspace(expr[i])) continue;

        if (isalpha(expr[i])) {
            output[out_i++] = expr[i];
        } else if (expr[i] == '(') {
            stack[++top] = expr[i];
            open_parens++;
        } else if (expr[i] == ')') {
            open_parens--;
            if (open_parens < 0) {
                fprintf(stderr, "Error: mismatched parentheses\n");
                return 0;;
            }
            while (top >= 0 && stack[top] != '(')
                output[out_i++] = stack[top--];
            if (top < 0) {
                fprintf(stderr, "Error: mismatched parentheses\n");
                return 0;;
            }
            top--; // Убрать '('
        } else if (strchr("!&|", expr[i])) {
            char op = expr[i];
            while (top >= 0 && precedence(stack[top]) >= precedence(op))
                output[out_i++] = stack[top--];
            stack[++top] = op;
        } else {
            fprintf(stderr, "Error: invalid character '%c'\n", expr[i]);
            return 0;;
        }
    }

    if (open_parens != 0) {
        fprintf(stderr, "Error: mismatched parentheses\n");
        return 0;;
    }

    while (top >= 0) {
        if (stack[top] == '(') {
            fprintf(stderr, "Error: mismatched parentheses\n");
            return 0;;
        }
        output[out_i++] = stack[top--];
    }

    output[out_i] = '\0';
    return 1;
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
    int var_count;
    printf("Enter number of variables (max 26): ");
    scanf("%d", &var_count);
    getchar(); // clear newline

    if (var_count > 26) var_count = 26;

    Variable vars[26];
    for (int i = 0; i < var_count; i++) {
        vars[i].name = 'A' + i;
        printf("%c = ", vars[i].name);
        scanf("%d", &vars[i].value);
        getchar();
    }

    char expr[512];
    printf("Enter logical expression:\n");
    fgets(expr, 512, stdin);
    expr[strcspn(expr, "\n")] = 0; // remove newline

    normalize(expr);

    char rpn[512];
    to_rpn(expr, rpn);

    int result = eval_rpn(rpn, vars, var_count);
    printf("RESULT: %d\n", result);

    return 0;
}
