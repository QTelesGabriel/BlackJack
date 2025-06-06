#include "../include/jogador.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

jogador *criar_jogador(int indice) {        // Função para criar um novo jogador
    jogador *novo_jogador = (jogador *)malloc(sizeof(jogador));
    if(!novo_jogador) {
        fprintf(stderr, "Falha ao criar novo jogador!\n");
        return NULL;
    } 
    
    inicializar_mao_jogador(novo_jogador);  

    novo_jogador->ja_fez_split = 0;
    novo_jogador->split = 0;
    novo_jogador->quantidade_de_cartas = 0;
    novo_jogador->jogando = 1;
    novo_jogador->proximo = NULL;
    novo_jogador->blackjack = 0;
    novo_jogador->indice_do_jogador = indice;
    if(novo_jogador->indice_do_jogador == 0) {
        novo_jogador->dinheiro = 20000000;
    }
    else {
        novo_jogador->dinheiro = 1000000;
    }
    novo_jogador->aposta = 0;

    return novo_jogador;
}

void inicializar_mao_jogador(jogador *jogador) {
    jogador->mao.topo = NULL;
}

void inicializar_lista_de_jogadores(jogadores *jogadores) {     // Função para inicializar a lista de jogadores
    jogadores->inicio = NULL;
}

void inserir_jogador(jogadores *jogadores, int indice) {        // Função para inserir um novo jogador na lista
    jogador *novo_jogador = criar_jogador(indice);

    if(jogadores->inicio == NULL) {
        jogadores->inicio = novo_jogador;
        novo_jogador->proximo = jogadores->inicio;
        return;
    }

    jogador *aux = jogadores->inicio;
    
    while (aux->proximo != jogadores->inicio) {
        aux = aux->proximo;
    }
    aux->proximo = novo_jogador;
    novo_jogador->proximo = jogadores->inicio;
}

void comprar_cartas(jogador *jogador, baralho *baralho) {
    if(!jogador) {
        fprintf(stderr, "Jogador inválido!\n");
        exit(1);
    }
    
    if(!baralho->topo) {
        criar_baralho_completo(baralho);
    }

    carta *carta_a_ser_comprada = pop(baralho);

    if(!jogador->mao.topo) {
        jogador->mao.topo = carta_a_ser_comprada;
        baralho->quantidade_de_cartas -= 1;
        return;
    }

    carta_a_ser_comprada->proximo = jogador->mao.topo;
    jogador->mao.topo = carta_a_ser_comprada;   
}

void mostrar_cartas_do_jogador(jogador *jogador_da_vez) {       // Função para mostrar as cartas de cada jogador
    char num[3];
    char naipe[4];

    carta *aux = jogador_da_vez->mao.topo;

    while (aux != NULL) {
        if(aux->naipe == 'P') {
            sprintf(naipe, "♣");
        }
        else if(aux->naipe == 'E') {
            sprintf(naipe, "♠");
        }
        else if(aux->naipe == 'O') {
            sprintf(naipe, "♦");
        }
        else if(aux->naipe == 'C') {
            sprintf(naipe, "♥");
        }

        if(aux->num > 1 && aux->num < 11) {
            sprintf(num, "%d", aux->num);
        }
        else if(aux->num == 1) {
            sprintf(num, "A");
        }
        else if(aux->num == 11) {
            sprintf(num, "J");
        }
        else if(aux->num == 12) {
            sprintf(num, "Q");
        }
        else if(aux->num == 13) {
            sprintf(num, "K");
        }

        if(jogador_da_vez->indice_do_jogador == 0 && jogador_da_vez->mao.topo == aux && jogador_da_vez->quantidade_de_cartas == 2) {
            
            printf(" ______   \n");
            printf("|_|__|_|  \n");
            printf("|_|__|_|  \n");
            printf("|_|__|_|  \n");
            printf("|_|__|_|  \n\n");
        }
        else {
            printf(" ______   \n");
            printf("|%s    %s|  \n", num, (aux->num == 10 ? "" : " "));
            printf("|%s     |  \n", naipe);
            printf("|      |  \n");
            printf("|______|  \n\n");
        }
        aux = aux->proximo;
    }    

    printf("//=================\\\\\n");
    
}

void mostrar_carta_comprada(jogador *jogador) {
    char num[3];
    char naipe[4];

    if(jogador->mao.topo->naipe == 'P') {
        sprintf(naipe, "♣");
    }
    else if(jogador->mao.topo->naipe == 'E') {
        sprintf(naipe, "♠");
    }
    else if(jogador->mao.topo->naipe == 'O') {
        sprintf(naipe, "♦");
    }
    else if(jogador->mao.topo->naipe == 'C') {
        sprintf(naipe, "♥");
    }

    if(jogador->mao.topo->num > 1 && jogador->mao.topo->num < 11) {
        sprintf(num, "%d", jogador->mao.topo->num);
    }
    else if(jogador->mao.topo->num == 1) {
        sprintf(num, "A");
    }
    else if(jogador->mao.topo->num == 11) {
        sprintf(num, "J");
    }
    else if(jogador->mao.topo->num == 12) {
        sprintf(num, "Q");
    }
    else if(jogador->mao.topo->num == 13) {
        sprintf(num, "K");
    }

    if(jogador->indice_do_jogador == 0) {
        printf("Carta para o dealer:\n");
    }
    else {
        printf("Carta para o jogador %d%s: \n", jogador->indice_do_jogador, (jogador->split == 1 ? ".2" : ""));
    }

    if(jogador->indice_do_jogador == 0 && jogador->quantidade_de_cartas == 2) {
        printf(" ______   \n");
        printf("|_|__|_|  \n");
        printf("|_|__|_|  \n");
        printf("|_|__|_|  \n");
        printf("|_|__|_|  \n\n");
    }
    else {
        printf(" ______   \n");
        printf("|%s    %s|  \n", num, (jogador->mao.topo->num == 10 ? "" : " "));
        printf("|%s     |  \n", naipe);
        printf("|      |  \n");
        printf("|______|  \n\n");
    }

    getchar();
}

void quanto_vale_o_as(jogador *jogador) {
    int soma_das_cartas = somatorio_das_cartas(jogador);

    if(jogador->mao.topo->num == 1) {
        if(jogador->indice_do_jogador != 0 || jogador->quantidade_de_cartas != 2) {
            if(soma_das_cartas > 21) {
                jogador->mao.topo->valor = 1;
                if(jogador->indice_do_jogador != 0 || jogador->quantidade_de_cartas != 2) {
                    printf("\nO Ás está valendo 1...\n");
                    getchar();
                }
            }
            else {
                jogador->mao.topo->valor = 11;
                if(jogador->indice_do_jogador != 0 || jogador->quantidade_de_cartas != 2) {
                    printf("O Ás está valendo 11...\n");
                    getchar();
                }
            }
        }
        else {
            if(jogador->quantidade_de_cartas != 2) {
                printf("O Ás está valendo 11...\n");
            }
            jogador->mao.topo->valor = 11;
        }
    }    
}

void reajustar_valor_do_as(jogador *jogador) {
    carta *aux = jogador->mao.topo;
    while(aux != NULL) {
        if(somatorio_das_cartas(jogador) > 21) {
            if(aux->valor == 11) {
                aux->valor = 1;
                printf("\nO valor do Ás foi de 11 para 1 para evitar estouro...\n");
                getchar();
            }
        }

        aux = aux->proximo;
    }
}

int somatorio_das_cartas(jogador *jogador) {
    int somatorio = 0;
    carta *aux = jogador->mao.topo;
    while(aux != NULL) {
        somatorio += aux->valor;
        aux = aux->proximo;
    }

    return somatorio;
}

void conferir_situacao_jogador(jogador *jogador) {
    if(jogador->indice_do_jogador == 0) {
        if(somatorio_das_cartas(jogador) > 21) {
            printf("\nO dealer estourou!\n");
            jogador->jogando = 0;
            getchar();
        }
        else if(somatorio_das_cartas(jogador) <= 21 && somatorio_das_cartas(jogador) > 16) {
            printf("\nO dealer decidiu parar...\n");
            jogador->jogando = 0;
            getchar();
        }
    }
    else {
        if(somatorio_das_cartas(jogador) > 21) {
            printf("\nO jogador %d%s estourou!\n", jogador->indice_do_jogador, (jogador->split == 1 ? ".2" : ""));
            getchar();
            jogador->jogando = 0;
        }
    }
}

void fez_blackjack(jogador *jogador) {
    if(jogador->mao.topo->valor + jogador->mao.topo->proximo->valor == 21) {
        if(jogador->indice_do_jogador != 0 && jogador->blackjack == 0) {
            printf("\nO jogador %d%s fez BlackJack!\n", jogador->indice_do_jogador, (jogador->split == 1 ? ".2" : ""));
        }
        else if(jogador->indice_do_jogador == 0 && jogador->blackjack == 0) {
            printf("\nO dealer fez BlackJack!\n");
        }
        jogador->blackjack = 1;
        jogador->jogando = 0;
        getchar();
    }
}