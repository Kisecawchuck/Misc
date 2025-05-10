#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogador_17076671.h" // <-- Substitua XXXXX pelo seu número USP

// Variáveis globais para armazenar o estado do jogador
static int id;
static int num_jogadores;
static Carta mao[6];
static int num_cartas;

// Retorna o nome do jogador (usado no placar final)
const char* nome_jogador_17076671() {
	// Substitua abaixo pelo nome que deseja exibir no placar
	return "Igor";
}

// Esta função é chamada uma vez no início do jogo.
// Você recebe seu id (posição na mesa) e o número total de jogadores.
// Guarde essas informações se quiser usá-las em sua estratégia.
void iniciar_17076671(int meu_id, int total_jogadores) {
    id = meu_id;
    num_jogadores = total_jogadores;
}

// Esta função é chamada no início de cada rodada.
// Você recebe:
// - A carta virada
// - A manilha
// - Sua mão (de 2 a 6 cartas)
// Copie as cartas para a variável global `mao[]` para usar em `apostar` e `jogar`.
void nova_rodada_17076671(int rodada, Carta carta_virada, Valor manilha, int n_cartas, Carta* minha_mao) {
	// Exemplo:
	// num_cartas = n_cartas;
	// for (int i = 0; i < n_cartas; i++) {
	// mao[i] = minha_mao[i];
	// }
    for (int i = 0; i < n_cartas; i++) {
        mao[i] = minha_mao[i];
    }
}

// Esta função define quantas mãos você pretende vencer na rodada.
// Analise sua mão e a manilha para tomar essa decisão.
// Retorne um valor entre 0 e `num_cartas`.
int apostar_17076671() {
	// Exemplo simples: apostar sempre metade das cartas (arredondado para baixo)
	// return num_cartas / 2;
	return num_cartas / 2; // Substitua pelo valor da sua aposta
}

// Esta função escolhe qual carta jogar.
// Você deve retornar o índice (posição) da carta na sua mão (`mao[]`).
// IMPORTANTE: cada carta só pode ser jogada uma vez.
// Use uma estratégia para marcar cartas já usadas, por exemplo:
// - marcar com `mao[i].valor = -1`
// - procurar a próxima carta com `mao[i].valor >= 0`
int jogar_17076671(Carta* mesa, int num_na_mesa) {
	// Exemplo mínimo: sempre retorna a primeira carta válida
	// for (int i = 0; i < num_cartas; i++) {
	// if (mao[i].valor >= 0) return i;
	// }
	return 0; // Substitua pela sua lógica de jogo
}

int main() {
    return 0;
}
