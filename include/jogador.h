#ifndef JOGADOR_H
#define JOGADOR_H
#include "baralho.h"

typedef struct Cartas_do_jogador {
    carta *topo;
} cartas_do_jogador;

typedef struct Jogador {
    cartas_do_jogador mao;
    int jogando;
    int quantidade_de_cartas;
    int indice_do_jogador;
    double dinheiro;
    double aposta;
    struct Jogador *proximo;
    int blackjack;
    int ja_fez_split;
    int split;
} jogador;

typedef struct Jogadores {
    jogador *inicio;
} jogadores;

jogador *criar_jogador(int indice);
void inicializar_mao_jogador(jogador *jogador);
void inicializar_lista_de_jogadores(jogadores *jogadores);
void inserir_jogador(jogadores *jogadores, int indice);
void comprar_cartas(jogador *jogador, baralho *baralho);
void mostrar_cartas_do_jogador(jogador *jogador_da_vez);
void mostrar_carta_comprada(jogador *jogador);
void quanto_vale_o_as(jogador *jogador);
void reajustar_valor_do_as(jogador *jogador);
int somatorio_das_cartas(jogador *jogador);
void conferir_situacao_jogador(jogador *jogador);
void fez_blackjack(jogador *jogador);

#endif
