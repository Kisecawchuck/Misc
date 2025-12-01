#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define TAMANHO 10000

enum { _Lista, _Arvore };
typedef struct _NO_ARVORE {
    char palavra[46];
    int linha;
    struct _NO_ARVORE *esq;
    struct _NO_ARVORE *dir;
} No;
typedef struct {
    No *raiz;
} Arvore;

Arvore *cria_arvore() {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
    return arvore;
}

No * insere_ord_rec(No *raiz, No *novo){
	if (raiz) {
		if (strcasecmp(novo->palavra, raiz->palavra) != 0) {
			if (strcasecmp(novo->palavra, raiz->palavra) < 0) raiz->esq = insere_ord_rec(raiz->esq, novo);
			else raiz->dir = insere_ord_rec(raiz->dir, novo);
		}
		return raiz;
	}
	return novo;
}

bool insere_ord(Arvore *arvore, char *e, int l) {
	No * novo = malloc(sizeof(No));
	
	strcpy(novo->palavra, e);
	novo->esq = novo->dir = NULL;
    novo->linha = l;

    No *p = arvore->raiz;
	arvore->raiz = insere_ord_rec(arvore->raiz, novo);
	return p == arvore->raiz ? false : true;
}

No * busca_rec(No * no, char *e){
	No * aux;
	if (no) {
		if (strcasecmp(e, no->palavra) == 0) return no;

		aux = busca_rec(no->esq, e);
		if (aux) return aux;
		return busca_rec(no->dir, e);
	}
	return NULL;
}

No * busca(Arvore * arvore, char *e){
	return busca_rec(arvore->raiz, e);	
}

int imprime_rec(No * no){

	// percurso in-ordem para a impressão dos elementos

	if(no){
		int m = imprime_rec(no->esq) + 1;
		printf(" %s", no->palavra);
		return imprime_rec(no->dir) + m;
	}
    return 0;
}

int imprime(Arvore * arvore){

	printf("Elementos na arvore:");
	return imprime_rec(arvore->raiz);
}


int max(int a, int b) { return a > b ? a : b; } 

int altura(No * no){

	if(no) {

		return max(altura(no->esq), altura(no->dir)) + 1;
	}

	return -1;
}

/*
Lista *cria_lista() {
    Lista *lista = malloc(sizeof(Lista));
    lista->primeiro = NULL;

    return lista;
}

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

destroi_lista: Libera a lista ligada; 
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
*/

int main(int argc, char *argv[]) {
    FILE *ENTRADA;
    if (argc < 3) {
        printf("Uso: %s <nome_do_arquivo>.txt <tipo_de_índice>\n", argv[0]);
    } else {
        printf("Arquivo: \'%s\'\n", argv[1]);
        printf("Tipo de indice: \'%s\'\n", argv[2]);
        ENTRADA = fopen(argv[1], "r");
        if (ENTRADA == NULL) {
            printf("Erro! Impossível abrir o arquivo de entrada!\n");
            exit(1);
        }

        int n_linhas = 0;
        int n_palavras = 0;
        int indice = strcasecmp(argv[2], "arvore") ? _Lista : _Arvore;
        Arvore *arvore = cria_arvore();
        char buffer[TAMANHO + 1];
        while (ENTRADA && fgets(buffer, TAMANHO, ENTRADA)) {
            n_linhas++;

            char *token = strtok(buffer, " -,./\n");
            while (token) {
                n_palavras++;
                if (indice == _Arvore && insere_ord(arvore, token, n_linhas))
                    n_palavras--;

                token = strtok(NULL, " -,./\n");
            }
        }
        int n = imprime(arvore);
        printf("Numero de linhas no arquivo: %d\n", n_linhas);
        printf("Total de palavras unicas indexadas: %05d\n", n);
        if (indice == _Arvore) {
            printf("Altura da arvore: %05d\n", altura(arvore->raiz));
        }

        char comando[100];
        bool fim = false;
        while (!fim) {
            printf("> ");
            scanf("%s", comando);
            if (strcmp(comando, "fim") == 0) return 0;
            else if (strcmp(comando, "busca") == 0) {
                scanf("%s", comando);
                No *p = busca(arvore, comando);
                if (p) {
                    rewind(ENTRADA);
                    for (int i = 0; i < p->linha; i++)
                        fgets(buffer, sizeof(buffer), ENTRADA);
                    printf("%04d: %s", p->linha, buffer);
                }
            }
            else printf("Opcao invalida!\n");
      }
    }
    fclose(ENTRADA);
}
