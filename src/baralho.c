#include "../include/baralho.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

carta *criar_carta(int num, char naipe) {
    carta *nova_carta = (carta *)malloc(sizeof(carta));
    if(!nova_carta) {
        fprintf(stderr, "Falha ao criar nova carta!");
        return NULL;
    }
    nova_carta->num = num;
    if(num != 11 && num != 12 && num != 13 && num != 1) {
        nova_carta->valor = num;
    } else if(num == 1) {
        nova_carta->valor = 11;
    } else {
        nova_carta->valor = 10;
    }
    nova_carta->naipe = naipe;
    nova_carta->proximo = NULL;

    return nova_carta;
}

void inicializar_baralho(baralho *baralho) {
    baralho->topo = NULL;
    baralho->quantidade_de_cartas = 0;
}

void inserir_cartas_no_baralho(baralho *baralho, int num, char naipe) {
    carta *nova_carta;
    nova_carta = criar_carta(num, naipe);
    
    if(!nova_carta) {
        fprintf(stderr, "Falha ao criar carta!\n");
        exit(1);
    }

    if(baralho->topo == NULL) {
        baralho->topo = nova_carta;
        return;
    }

    nova_carta->proximo = baralho->topo;
    baralho->topo = nova_carta;
}

void criar_baralho_completo(baralho *baralho) {     // Função para criar um baralho completo e ebaralhado
    srand(time(NULL));
    int num;    // Numero da carta
    char naipe[4] = {'C', 'P', 'E', 'O'};   // Naipes
    char naipe_escolhido;   // Naipe da carta

    // Zerar o baralho
    while(baralho->topo != NULL) {
        pop(baralho);
        inicializar_baralho(baralho);
    }

    // Criar uma carta aleatória
    for (int i = baralho->quantidade_de_cartas; i < 52; i++) {
        
        // Escolher um número que já não tenha em 4 cartas
        while(1) {
            num = (rand() % 13) + 1;
            if(nao_existem_quatro_cartas_iguais(baralho, num)) {
                break;
            }
        }

        // Escolher uma carta que de fato não existe ainda
        while(1) {
            naipe_escolhido = naipe[rand() % 4];
            if(nao_existe_carta_igual(baralho, num, naipe_escolhido)) {
                break;
            }
        }

        // Inserir a carta criada no baralho
        inserir_cartas_no_baralho(baralho, num, naipe_escolhido);
        
        // Atualizar o tamhanho do baralho
        baralho->quantidade_de_cartas += 1;
    }
}

int nao_existem_quatro_cartas_iguais(baralho *baralho, int num) {
    if(!baralho->topo) {
        return 1;
    }
    else {
        int contador = 0;
        carta *aux = baralho->topo;
        
        while(aux->proximo != NULL) {
            if(aux->num == num) {
                contador++;
            }
            if(contador >= 4) {
                return 0;
            }
            aux = aux->proximo;
        }
        if(aux->num == num) {
            contador++;
        }
        if(contador >= 4) {
            return 0;
        }
        return 1;
    }
}

int nao_existe_carta_igual(baralho *baralho, int num, char naipe) {
    if(!baralho->topo) {
        return 1;
    }
    else {
        carta *aux = baralho->topo;
        while(aux->proximo != NULL) {
            if(aux->num == num) {
                if(aux->naipe == naipe) {
                    return 0;
                }
            }
            aux = aux->proximo;
        }
        if(aux->num != num) {
            return 1;
        }
        else {
            if(aux->naipe == naipe) {
                return 0;
            }
            else {
                return 1;
            }
        }
    }
}

carta *pop(baralho *baralho) {
    if(!baralho->topo) {
        fprintf(stderr, "Acabaram as cartas!\n");
        exit(1);
    }

    carta *carta_a_ser_passada = (carta *)malloc(sizeof(carta));
    carta_a_ser_passada->num = baralho->topo->num;
    carta_a_ser_passada->valor = baralho->topo->valor;
    carta_a_ser_passada->naipe = baralho->topo->naipe;
    carta_a_ser_passada->proximo = NULL;

    carta *temp = baralho->topo;
    baralho->topo = baralho->topo->proximo;
    free(temp);

    baralho->quantidade_de_cartas -= 1;

    return carta_a_ser_passada;
}