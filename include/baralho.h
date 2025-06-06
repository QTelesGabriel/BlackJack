#ifndef BARALHO_H
#define BARALHO_H

typedef struct Carta {
    int num;
    int valor;
    char naipe;
    struct Carta *proximo;
} carta;

typedef struct Pilha_Baralho {
    carta *topo;
    int quantidade_de_cartas;
} baralho;

carta *criar_carta(int num, char naipe);
void inicializar_baralho(baralho *baralho);
void inserir_cartas_no_baralho(baralho *baralho, int num, char naipe);
void criar_baralho_completo(baralho *baralho);
int nao_existem_quatro_cartas_iguais(baralho *baralho, int num);
int nao_existe_carta_igual(baralho *baralho, int num, char naipe);
carta *pop(baralho *baralho);

#endif
