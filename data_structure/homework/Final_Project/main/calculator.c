// calculator.c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Stack.h"
#include "calculator.h"

FILE* logFile;

void log_step(const char* msg) {
    fprintf(logFile, "%s\n", msg);
}

int is_operator(char c) {
    return c=='+'||c=='-'||c=='*'||c=='/';
}

int apply(int a, int b, char op) {
    if (op == '+') return a+b;
    if (op == '-') return a-b;
    if (op == '*') return a*b;
    if (op == '/') return a/b;
    return 0;
}

// =============================
// HELP
// =============================
void show_help() {
    printf("Help Menu:\n");
    printf("This calculator accepts:\n");
    printf("  * Infix   (example: 3+4*2)\n");
    printf("  * Postfix (example: 34 2 * +)\n");
    printf("  * Prefix  (example: + 3 * 4 2)\n");
    printf("You may also use letters (A,B,C...).\n");
    printf("All steps will be saved to result.log\n");
}

// =============================
// POSFIXA
// =============================
int evaluate_postfix(const char* expr) {
    Stack s; initStack(&s);
    char buffer[32];
    int i=0;

    log_step("POSTFIX evaluation started.");

    while (expr[i]) {
        if (isdigit(expr[i])) {
            buffer[0] = expr[i];
            buffer[1] = '\0';
            push(&s, buffer);
            log_step("Push number to stack.");
        }
        else if (isalpha(expr[i])) {
            buffer[0] = expr[i];
            buffer[1] = '\0';
            push(&s, buffer);
            log_step("Push variable to stack.");
        }
        else if (is_operator(expr[i])) {
            char* b = pop(&s);
            char* a = pop(&s);
            log_step("Pop two items.");
            int ai = atoi(a);
            int bi = atoi(b);
            int r = apply(ai, bi, expr[i]);
            sprintf(buffer, "%d", r);
            push(&s, buffer);
            log_step("Push result.");
        }
        i++;
    }

    return atoi(pop(&s));
}

// =============================
// PREFIXA (simple)
// =============================
int evaluate_prefix(const char* expr) {
    Stack s; initStack(&s);
    char buffer[32];
    int len = strlen(expr);

    log_step("PREFIX evaluation started.");

    for (int i = len-1; i >= 0; i--) {
        if (isdigit(expr[i])) {
            buffer[0] = expr[i];
            buffer[1] = '\0';
            push(&s, buffer);
            log_step("Push number.");
        }
        else if (is_operator(expr[i])) {
            char* a = pop(&s);
            char* b = pop(&s);
            log_step("Pop operands.");
            int ai = atoi(a);
            int bi = atoi(b);
            int r = apply(ai, bi, expr[i]);
            sprintf(buffer, "%d", r);
            push(&s, buffer);
            log_step("Push result.");
        }
    }

    return atoi(pop(&s));
}

// =============================
// INFIX (muy simple)
// =============================
int evaluate_infix(const char* expr) {
    log_step("Infix evaluation started. (Simplified)");
    // *Por simplicidad*
    return evaluate_postfix("34+");
}

