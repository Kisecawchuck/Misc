#include <stdio.h>

int main() {
    while (1) {
        printf("===============================\n   Calculadora Simples\n===============================\n");
        printf("Selecione uma operação:\n");
        printf("1. Adição\n2. Subtração\n3. Multiplicação\n4. Divisão\n5. Sair\nOpção: ");
        int opt;
        do {
            scanf("%d", &opt);
        } while (opt < 1 || opt > 5);
        if (opt == 5) {
            printf("Saindo...\n");
            return 0;
        }

        double a, b;
        printf("Digite o primeiro número: ");
        scanf("%lf", &a);
        printf("Digite o segundo número: ");
        scanf("%lf", &b);
        if (opt == 1) {
            printf("%lf + %lf = %lf\n", a, b, a + b);
        } else if (opt == 2) {
            printf("%lf - %lf = %lf\n", a, b, a - b);
        } else if (opt == 3) {
            printf("%lf * %lf = %lf\n", a, b, a * b);
        } else if (opt == 4) {
            if (b == 0) {
                printf("Erro: Divisão por zero não é permitida.\n");
            } else {
                printf("%lf / %lf = %lf\n", a, b, a / b);
            }
        }

        char r;
        printf("Deseja realizar outra operação? ");
        scanf("%c", &r);
        scanf("%c", &r);
        if (r == 's') continue;
        else {
            printf("Obrigado por usar a calculadora! Até a próxima.\n");
            return 0;
        }
    }
}
