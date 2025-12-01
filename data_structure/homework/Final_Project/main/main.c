// main.c
#include <stdio.h>
#include <string.h>
#include "calculator.h"

int main() {
    char input[128];
    int mode;

    FILE* f = fopen("result.log", "w");
    fclose(f);

    printf("********** C DATA STRUCTURE CALCULATOR **********\n");
    printf("1) Infix\n");
    printf("2) Postfix\n");
    printf("3) Prefix\n");
    printf("4) Help\n");
    printf("Choose option: ");
    scanf("%d", &mode);

    if (mode == 4) {
        show_help();
        return 0;
    }

    printf("Enter operation: ");
    scanf("%s", input);

    int result = 0;

    f = fopen("result.log", "a");
    logFile = f;

    if (mode == 1)
        result = evaluate_infix(input);
    else if (mode == 2)
        result = evaluate_postfix(input);
    else if (mode == 3)
        result = evaluate_prefix(input);

    fclose(f);

    printf("Result: %d\n", result);
    printf("Steps saved to result.log\n");

    return 0;
}

