#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Node {
    long val;
    struct Node* prox;
} Node;

Node* inserirDivisor(long divisor, Node* divisores);
int imprimirDivisores(Node* divisores, int dividendo);
void destruirDivisores(Node* divisores);
Node* popularDivisores(long NUM);
int verificarPrimazia(long n);

/* Verifica se um número é primo e imprime os divisores */
int main(int argc, char* argv[]) {
    if (argc >= 2) {
        if (strcmp("--help", argv[1]) == 0 || strcmp("-h", argv[1]) == 0) {
            printf("Usage: primo [OPTIONS] NUMS\n");
            printf("Verifica se um número é primo e imprime os divisores\n");
            printf("Exemplo: primo 56 331\n");
            printf("Todos os NUMS serão avaliados\n");
            putchar('\n');
            printf("Miscelânea:\n");
            printf(" -r, --random\tExibe um número que parece primo, mas não é.\n");
        } else if (strcmp("-r", argv[1]) == 0 || strcmp("-random", argv[1]) == 0) {
            // TODO: Fazer essa função aleatória.
            return 3;
        } else {
            for (int i = 1; i < argc; i++) {
                long n = atoi(argv[i]);
                if (n < 1) {
                    printf("NUM inválido.\n");
                    return 1;
                }
                int err = verificarPrimazia(n);
                if (err != 0) 
                    return err;
            }
        }
    } else {
        long n;
        char opt = 0;
        printf("Primo? ");
        if (scanf("%ld", &n) == 0) {
            printf("NUM inválido.\n");
            return 1;
        }
        int err = verificarPrimazia(n);
        if (err != 0)
            return err;
    }

    return 0;
}

/* Insere os divisores em ordem cescente */
Node* inserirDivisor(long val, Node* head) {
    Node* cur = head;
    while (cur != NULL && cur->prox != NULL && cur->prox->val < val) {
        cur = cur->prox;
    }
    Node* novoNode = (Node*) malloc(sizeof(Node));
    if (novoNode == NULL)
        return NULL;
    novoNode->val = val;
    if (cur != NULL && cur->prox != NULL && cur->prox->val > val)
        novoNode->prox = cur->prox;
    else
        novoNode->prox = NULL;
    if (cur != NULL)
        cur->prox = novoNode;

    return novoNode;
}

int imprimirDivisores(Node* head, int a) {
    int n = 0;
    Node* cur = head;
    printf("Divisores: ");
    while (cur != NULL) {
        ++n;
        printf("%ld, ", cur->val);
        cur = cur->prox;
    }
    printf("\b\b.\n");

    return n;
}

Node* popularDivisores(long n) {
    Node* divisor = inserirDivisor(1, NULL);
    if (divisor == NULL)
        return NULL;
    Node* err = NULL;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            err = inserirDivisor(i, divisor);
            if (err == NULL)
                return NULL;
            err = inserirDivisor(n / i, divisor);
            if (err == NULL)
                return NULL;
        }
    }
    if (n > 1)
        inserirDivisor(n, divisor);
    return divisor;
}

void destruirDivisores(Node* node) {
    if (node->prox != NULL)
        destruirDivisores(node->prox);
    free(node);
}

int verificarPrimazia(long n) {
    Node* divisores = popularDivisores(n);
    if (divisores == NULL) {
        printf("Erro ao alocar o divisor.\n");
        return 2;
    }
    int len = imprimirDivisores(divisores, n);
    if (len == 2)
        printf("%ld é primo.\n", n);
    else
        printf("%ld não é primo.\n", n);
    destruirDivisores(divisores);
    return 0;
}
