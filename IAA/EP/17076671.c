#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define AREA 6

enum { False, True };
typedef struct {
    bool exists;
    bool belongs;
} Casela;
typedef Casela* Linha;
typedef Linha* Tabela;

int arredondar(double x);
void encontrarIlhas(int **mapa, int x, int y, int n, int m);
int removerLixo(int **mapa, int x, int y, int n, int m);

static bool **visitado;

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Uso: ./EP {PROFUNDIDADE} {LINHAS} {COLUNAS} {ARQUIVO}\n");
        return 1;
    }

    // Entrada de dados;
    int K = atoi(argv[1]);
    int n_linhas = atoi(argv[2]);
    int n_colunas = atoi(argv[3]);
    FILE *f = fopen(argv[4], "r");
    if (f == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return 2;
    }

    int **ilhas = malloc(sizeof(int *) * n_linhas);
    for (int i = 0; i < n_linhas; ++i)
        ilhas[i] = malloc(sizeof(int) * n_colunas);
    visitado = malloc(sizeof(bool *) * n_linhas);
    for (int i = 0; i < n_linhas; ++i)
        visitado[i] = malloc(sizeof(bool) * n_colunas);

    // Leitura de arquivo;
    for (int i = 0; i < n_linhas; ++i)
        for (int j = 0; j < n_colunas; ++j) {
            fscanf(f, "%d", &ilhas[i][j]);
            visitado[i][j] = False;
        }

    // Procura pela quantidade de ilhas;
    int n_ilhas = 0; // Nº de ilhas;
    for (int i = 0; i < n_linhas; ++i)
        for (int j = 0; j < n_colunas; ++j)
            if (ilhas[i][j] != 0 && !visitado[i][j]) {
                ++n_ilhas;
                encontrarIlhas(ilhas, i, j, n_linhas, n_colunas);
            }
    printf("%d\n", n_ilhas);

    // Destruir o lixo e colocar no conteiner;
    int *S = malloc(sizeof(int) * (n_ilhas + 1));
    S[0] = 0;
    int idx = 1;
    for (int i = 0; i < n_linhas; ++i)
        for (int j = 0; j < n_colunas; ++j)
            if (ilhas[i][j] != 0) {
                int P = removerLixo(ilhas, i, j, n_linhas, n_colunas);
                S[idx] = arredondar((double) P / AREA);
                if (idx == n_ilhas)
                    printf("%d\n", S[idx]);
                else
                    printf("%d ", S[idx]);
                ++idx;
            }

    // Problema da mochila;
    Tabela P = malloc(sizeof(Linha) * (n_ilhas + 1));
    for (int i = 0; i < n_ilhas + 1; ++i)
        P[i] = malloc(sizeof(Casela) * (K + 1));
    P[0][0].exists = True;
    for (int i = 1; i <= K; ++i)
        P[0][i].exists = False;
    for (int i = 1; i <= n_ilhas; ++i)
        for (int k = 0; k <= K; ++k) {
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
    if (!P[n_ilhas][K].exists)
        printf("Nao ha resposta valida!\n");
    else {
        int j = n_ilhas;
        int i = K;
        while (!P[j][i].belongs) --j;
        while (i > 0) {
            if (i - S[j] <= 0)
                printf("%d\n", S[j]);
            else
                printf("%d ", S[j]);
            i -= S[j];
            --j;
        }
    }

    // Fecha o arquivo;
    fclose(f);
    // Libera as matrizes;
    for (int i = 0; i < n_linhas; ++i) {
        free(ilhas[i]);
        free(visitado[i]);
    }
    free(ilhas);
    free(visitado);
    for (int i = 0; i < n_ilhas + 1; ++i)
        free(P[i]);
    free(P);
    // Libera o conjunto;
    free(S);

    return 0;
}

/* arredondar: arredonda x de acordo com a especificação */
int arredondar(double x) {
    if (x > 0 && x < 1) return 1;
    else return x;
}

/* Procura por ilhas e marca como visitada. Só existe para descobrir
 * o número de ilhas, necessária para criar o conjunto S; */
void encontrarIlhas(int **mapa, int x, int y, int n, int m) {
    if (x < 0 || y < 0 || x >= n || y >= m) return;
    if (visitado[x][y] == True || mapa[x][y] == 0) return;

    visitado[x][y] = True;
    encontrarIlhas(mapa, x - 1, y, n, m);
    encontrarIlhas(mapa, x, y + 1, n, m);
    encontrarIlhas(mapa, x + 1, y, n, m);
    encontrarIlhas(mapa, x, y - 1, n, m);
    return;
}

/* removerLixo: versão destrutiva da função encontrarIlhas, 
 * um tanto redundante */
int removerLixo(int **mapa, int x, int y, int n, int m) {
    if (x < 0 || y < 0 || x >= n || y >= m) return 0;
    if (mapa[x][y] == 0) return 0;

    int cnt = mapa[x][y];
    mapa[x][y] = 0;
    cnt += removerLixo(mapa, x - 1, y, n, m);
    cnt += removerLixo(mapa, x, y + 1, n, m);
    cnt += removerLixo(mapa, x + 1, y, n, m);
    cnt += removerLixo(mapa, x, y - 1, n, m);
    return cnt;
}
