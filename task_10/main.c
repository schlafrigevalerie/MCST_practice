#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char name;
    int value;
} Variable;

int get_var_value(char ch, Variable *vars, int var_count, int *ok) {
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

int eval_rpn(const char *rpn, Variable *vars, int var_count, int *ok) {
    int stack[512];
    int top = -1;

    for (int i = 0; rpn[i]; ++i) {
        char token = rpn[i];
        if (isalpha(token)) {
            int val = get_var_value(token, vars, var_count, ok);
            if (!*ok) return 0;
            stack[++top] = val;
        } else if (token == '!') {
            if (top < 0) {
                printf("Error: NOT operator missing operand\n");
                *ok = 0;
                return 0;
            }
            stack[top] = !stack[top];
        } else if (token == '&' || token == '|') {
            if (top < 1) {
                printf("Error: binary operator missing operands\n");
                *ok = 0;
                return 0;
            }
            int b = stack[top--];
            int a = stack[top--];
            stack[++top] = (token == '&') ? (a && b) : (a || b);
        } else {
            printf("Error: unknown operator '%c'\n", token);
            *ok = 0;
            return 0;
        }
    }

    if (top != 0) {
        printf("Error: invalid expression\n");
        *ok = 0;
        return 0;
    }

    return stack[0];
}


int main() {
    int var_count;
    Variable vars[512];
    char expr[512];
    char rpn[512];
    int ok = 1;

    printf("Enter number of variables (max %d): ", 512);
    if (scanf("%d", &var_count) != 1 || var_count <= 0 || var_count > 512) {
        printf("Error: invalid number of variables\n");
        return 1;
    }

    for (int i = 0; i < var_count; ++i) {
        int val;
        printf("%c = ", 'A' + i);
        if (scanf("%d", &val) != 1 || (val != 0 && val != 1)) {
            printf("Error: variable must be 0 or 1\n");
            return 1;
        }
        vars[i].name = 'A' + i;
        vars[i].value = val;
    }

    getchar(); // eat newline
    printf("Enter logical expression (use A-Z, !, &, |, parentheses):\n");
    if (!fgets(expr, sizeof(expr), stdin)) {
        printf("Error: failed to read expression\n");
        return 1;
    }
    expr[strcspn(expr, "\n")] = '\0';

    if (strlen(expr) == 0) {
        printf("Error: empty expression\n");
        return 1;
    }

    if (!to_rpn(expr, rpn)) {
        return 1;
    }

    int result = eval_rpn(rpn, vars, var_count, &ok);
    if (!ok) {
        return 1;
    }

    printf("RESULT: %d\n", result);
    return 0;
}
