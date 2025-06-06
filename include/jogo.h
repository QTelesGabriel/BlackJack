#ifndef JOGO_H
#define JOGO_H
#include "jogador.h"
#include "baralho.h"

void jogar();
void comecar_jogo(jogadores *jogadores, int *quantos_jogadores, baralho *baralho, int *indice);
void apostas(jogadores *jogadores);
void distribuicao_inicial_de_cartas(jogadores *jogadores, baralho *baralho, int quantos_jogadores);
void double_down(jogador *jogador, baralho *baralho, int *opcao_do_jogador);
void split(jogador *jogador_da_vez, baralho *baralho, int *quantos_jogadores, int indice);
int dealer_vai_comprar(jogadores *jogadores);
void mostrar_mesa(jogadores *jogadores, int quantos_jogadores);
void conferir_final_da_partida(jogadores *jogadores, int *continuar_mesa);

#endif
