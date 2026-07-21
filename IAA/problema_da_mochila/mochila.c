#include <stdio.h>
#include <stdlib.h>
#include "meubool.h"
#include "mochila.h"

int main() {
    int n, K;
    printf("n: ");
    scanf("%d", &n);
    printf("K: ");
    scanf("%d", &K);

    int *S = (int *) malloc(sizeof(int) * (n + 1));
    S[0] = 0;
    for (int i = 1; i <= n; ++i) {
        printf("%d: ", i);
        scanf("%d", &S[i]);
    }

    Tabela P = (Tabela) malloc(sizeof(Linha) * (n + 1));
    for (int i = 0; i <= n; ++i)
        P[i] = (Linha) malloc(sizeof(Casela) * (K + 1));

    P[0][0].exists = True;
    for (int i = 1; i <= K; ++i)
        P[0][i].exists = False;
    for (int i = 1; i <= n; ++i) {
        for (int k = 0; k <= K; ++k) {
            P[i][k].exists = False;
            if (P[i - 1][k].exists == True) {
                P[i][k].exists = True;
                P[i][k].belongs = False;
            } 
            else if (k - S[i] >= 0 && P[i - 1][k - S[i]].exists == True) {
                P[i][k].exists = True;
                P[i][k].belongs = True;
            }
        }
    }

    printf("Tabela Existe: \n");
    printf("  ");
    for (int i = 0; i <= K; ++i)
        printf("%d ", i);
    putchar('\n');
    for (int i = 0; i <= n; ++i) {
        printf("%d ", i);
        for (int j = 0; j <= K; ++j)
            printf("%d ", P[i][j].exists);
        putchar('\n');
    }
    printf("Tabela Pertence: \n");
    printf("  ");
    for (int i = 0; i <= K; ++i)
        printf("%d ", i);
    putchar('\n');
    for (int i = 0; i <= n; ++i) {
        printf("%d ", i);
        for (int j = 0; j <= K; ++j)
            printf("%d ", P[i][j].belongs);
        putchar('\n');
    }

    free(S);
    for (int i = 0; i <= n; ++i)
        free(P[i]);
    free(P);
}
