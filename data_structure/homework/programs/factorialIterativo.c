#include <stdio.h>

unsigned long long factIter(int n) {
    if (n < 0)
        return 0; // Factorial no definido para negativos
    if (n == 0)
        return 1; // 0! = 1

    unsigned long long a = 1;
    while (n > 1) {
        a = a * n;
        n--;
    }
    return a;
}

int main() {
    int num;
    printf("Ingrese un numero entero para calcular su factorial: ");
    scanf("%d", &num);

    unsigned long long resultado = factIter(num);

    if (num < 0) {
        printf("El factorial no esta definido para numeros negativos.\n");
    } else {
        printf("El factorial de %d es %llu\n", num, resultado);
    }

    return 0;
}
