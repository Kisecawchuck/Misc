#ifndef JOGADOR_17076671_H 
#define JOGADOR_17076671_H

#include "../baralho.h"

const char* nome_17076671();
void iniciar_17076671(const int meu_id, const int total_jogadores);
void nova_rodada_17076671(const int rodada, const Carta carta_virada, const int n_cartas, Carta* minha_mao);
int apostar_17076671(const int* apostas);
int jogar_17076671(const Carta* mesa, const int num_na_mesa, const int vitorias);

#endif // JOGADOR_17076671_H
