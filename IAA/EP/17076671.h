#ifndef a17076671_H
#define a17076671_H

enum { False, True };
typedef struct {
    bool exists;
    bool belongs;
} Casela;
typedef struct {
    int x;
    int y;
    int z;
} Conteiner;
// Cria o tipo para Array de Casela (Linha) e Matriz de Casela (Tabela);
typedef Casela* Linha;
typedef Linha* Tabela;

int arredondar(double x);
void encontrarIlhas(int x, int y, int **mapa);
int destruirLixo(int x, int y, int **mapa);

#endif
