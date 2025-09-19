#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "17076671.h"

// Acredite ou não, as variáveis globais deixam o código mais legível;
static int n, m;
static bool **visitado;

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Uso: ./EP {PROFUNDIDADE} {LINHAS} {COLUNAS} {ARQUIVO}\n");
        return 1;
    }

    Conteiner conteiner;
    conteiner.x = 3;
    conteiner.y = 2;
    // Entrada de dados;
    int p = atoi(argv[1]);
    n = atoi(argv[2]);
    m = atoi(argv[3]);
    FILE *f = fopen(argv[4], "r");
    if (f == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return 2;
    }

    int **ilhas = (int **) malloc(sizeof(int *) * n);
    for (int i = 0; i < n; ++i)
        ilhas[i] = (int *) malloc(sizeof(int) * m);
    visitado = (bool **) malloc(sizeof(bool *) * n);
    for (int i = 0; i < n; ++i)
        visitado[i] = malloc(sizeof(bool) * m);

    // Leitura de arquivo;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            fscanf(f, "%d", &ilhas[i][j]);
            visitado[i][j] = False;
        }

    // Procura pela quantidade de ilhas;
    int N = 0; // Nº de ilhas;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (ilhas[i][j] != 0 && !visitado[i][j]) {
                ++N;
                encontrarIlhas(i, j, ilhas);
            }
    printf("%d\n", N);

    // Destroi o lixo
    int *S = (int *) malloc(sizeof(int) * (N + 1));
    S[0] = 0;
    int idx = 1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (ilhas[i][j] != 0) {
                int P = destruirLixo(i, j, ilhas);
                S[idx] = arredondar((double) P / (conteiner.x * conteiner.y));
                printf("%d ", S[idx]);
                ++idx;
            }
    putchar('\b');
    putchar('\n');

    // Problema da mochila;
    Tabela P = (Tabela) malloc(sizeof(Linha) * (N + 1));
    for (int i = 0; i < N + 1; ++i)
        P[i] = (Linha) malloc(sizeof(Casela) * (p + 1));
    P[0][0].exists = True;
    for (int i = 1; i <= p; ++i)
        P[0][i].exists = False;
    for (int i = 1; i <= N; ++i)
        for (int k = 0; k <= p; ++k) {
            P[i][k].exists = False;
            if (P[i - 1][k].exists) {
                P[i][k].exists = True;
                P[i][k].belongs = False;
            }
            else if (k - S[i] >= 0 && P[i - 1][k - S[i]].exists) {
                P[i][k].exists = True;
                P[i][k].belongs = True;
            }
        }
    if (!P[N][p].exists)
        printf("Nao ha resposta valida!\n");
    else {
        int j = N;
        int i = p;
        while (!P[j][i].belongs) --j;
        while (i > 0) {
            printf("%d ", S[j]);
            i -= S[j];
            --j;
        }
        putchar('\b');
        putchar('\n');
    }

    // Fecha o arquivo;
    fclose(f);
    // Libera as matrizes;
    for (int i = 0; i < n; ++i) {
        free(ilhas[i]);
        free(visitado[i]);
    }
    free(ilhas);
    free(visitado);
    for (int i = 0; i < N + 1; ++i)
        free(P[i]);
    free(P);
    // Libera o conjunto;
    free(S);

    return 0;
}

int arredondar(double x) {
    if (x > 0 && x < 1) return 1;
    else return x;
}

/*
 * Procura por ilhas e marca como visitada. Só existe para descobrir
 * o número de ilhas, necessária para criar o conjunto S;
*/
void encontrarIlhas(int x, int y, int **mapa) {
    if (x < 0 || y < 0 || x >= n || y >= m) return;
    if (visitado[x][y] == True || mapa[x][y] == 0) return;

    visitado[x][y] = True;
    encontrarIlhas(x - 1, y, mapa);
    encontrarIlhas(x, y + 1, mapa);
    encontrarIlhas(x + 1, y, mapa);
    encontrarIlhas(x, y - 1, mapa);
    return;
}

/* 
 * A versão destrutiva da função encontrarIlhas, um tanto redundante; 
*/
int destruirLixo(int x, int y, int **mapa) {
    if (x < 0 || y < 0 || x >= n || y >= m) return 0;
    if (mapa[x][y] == 0) return 0;

    int cnt = mapa[x][y];
    mapa[x][y] = 0;
    cnt += destruirLixo(x - 1, y, mapa);
    cnt += destruirLixo(x, y + 1, mapa);
    cnt += destruirLixo(x + 1, y, mapa);
    cnt += destruirLixo(x, y - 1, mapa);
    return cnt;
}
