#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 10000

typedef struct {
    char palavra[46];
    int linha;
} Ele;
typedef struct _NO {
    char palavra[46];
    int linha;
    struct _NO *proximo;
} No;
typedef struct {
    No *primeiro;
} Lista;
int cmp(const void *A, const void *B) {
    Ele a = *(Ele*)A;
    Ele b = *(Ele*)B; 

    return strcasecmp(a.palavra, b.palavra);
}

Lista *cria_lista() {
    Lista *lista = malloc(sizeof(Lista));
    lista->primeiro = NULL;

    return lista;
}

/* insere: Insere um paciente na lista ligada; */
void insere(Lista *lista, char *wd, int linha) {
    No *novo = malloc(sizeof(No));

    strncpy(novo->palavra, wd, 45);
    novo->linha = linha;
    novo->proximo = lista->primeiro;
    lista->primeiro = novo;
}

void imprime(Lista *lista) {
    No *p = lista->primeiro;
    printf("Lista:");
    while (p) {
        printf(" %s", p->palavra);
        p = p->proximo;
    }
    putchar('\n');
}

/* destroi_lista: Libera a lista ligada; */
void destroi_lista(Lista *lista) {
    No *p = lista->primeiro;
    No *tmp;

    while(p) {
        tmp = p;
        p = p->proximo;
        free(tmp);
    }
    free(lista);
}

int main(int argc, char *argv[]) {
    FILE *INPUT;
    if (argc < 3) {
        printf("Uso: %s <nome_do_arquivo>.txt <tipo_de_índice>\n", argv[0]);
    } else {
        printf("Arquivo: \'%s\'\n", argv[1]);
        printf("Tipo de indice: \'%s\'\n", argv[2]);
        INPUT = fopen(argv[1], "r");
        if (INPUT == NULL) {
            printf("Erro! Impossível abrir o arquivo de entrada!\n");
            exit(1);
        }

        char buffer[TAMANHO];
        int n_linhas = 0;
        int n_palavras = 0;
        Lista *Palavras = cria_lista();
        while (fgets(buffer, TAMANHO, INPUT)) {
            n_linhas++;
            n_palavras++;
            char *token = strtok(buffer, " -,.");
            insere(Palavras, token, n_linhas);
            while ((token = strtok(NULL, " -,.\n"))) {
                insere(Palavras, token, n_linhas);
                n_palavras++;
            }
        }
        printf("Numero de linhas no arquivo: %d\n", n_linhas);
        Ele *palavras = malloc(sizeof(Ele) * n_palavras);
        No *p = Palavras->primeiro;
        for (int i = 0; i < n_palavras; i++) {
            strcpy(palavras[i].palavra, p->palavra);
            palavras[i].linha = p->linha;
            p = p->proximo;
        }
        destroi_lista(Palavras);
        qsort(palavras, n_palavras, sizeof(Ele), cmp);
        printf("Lista:\n");
        for (int i = 0; i < n_palavras; i++)
            printf(" %s", palavras[i].palavra);
        putchar('\n');
        /*
        int j = n_palavras - 1;
        for (int i = 1; i <= n_linhas; i++) {
            printf("Linha %04d:", i);
            while (palavras[j].linha == i) {
                printf(" %s", palavras[j].palavra);
                j--;
            }
            putchar('\n');
        }
        */

        char comando[100];
        bool fim = false;
        while (!fim) {
            printf("> ");
            scanf("%s", comando);
            if (strcmp(comando, "fim") == 0) return 0;
            if (strcmp(comando, "busca") != 0) printf("Opcao invalida!\n");
            else {

            }
      }
    }
}
