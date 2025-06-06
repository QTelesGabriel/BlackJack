#include "../include/jogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

void jogar() {      // Função ara começar o jogo
    system("clear");
    printf("Quantos jogadores serão?\n-> ");

    int indice = 0;
    int quantos_jogadores;
    scanf("%d", &quantos_jogadores);
    quantos_jogadores++;

    // Criar e inicializar lista de jogadores
    jogadores jogadores;
    inicializar_lista_de_jogadores(&jogadores);

    // Inicializar e criar um baralho completo de 52 cartas embaralho
    baralho baralho;
    inicializar_baralho(&baralho);

    // Inserir os jogadores na lista de jogadores
    for(int i = 0; i < quantos_jogadores; i++) {
        inserir_jogador(&jogadores, indice);
        indice++;
    }

    printf("\nJogo pronto para começar!\nAperte enter...");
    getchar();
    getchar();

    // Começar o jogo
    comecar_jogo(&jogadores, &quantos_jogadores, &baralho, &indice);
}

void comecar_jogo(jogadores *jogadores, int *quantos_jogadores, baralho *baralho, int *indice) {  // Função em que o código do jogo funciona
    int continuar_jogo = 1;     // Para saber se a rodada vai acabar
    int continuar_mesa = 1;     // Para saber se a mesa vai acabar
    int opcao_do_jogador;       // Escolher comprar o parar

    while(continuar_mesa) {
        // O jogo reiniciará
        continuar_jogo = 1;
        // Criar novo baralho embaralhado de 52 cartas
        criar_baralho_completo(baralho);
        // Esvaziar mão dos jogadores
        jogador *aux = jogadores->inicio;
        do {
            aux->quantidade_de_cartas = 0;
            aux->ja_fez_split = 0;           
            while(aux->mao.topo != NULL) {
                carta *temp = aux->mao.topo;
                aux->mao.topo = aux->mao.topo->proximo;
                free(temp); 
            }
            aux->blackjack = 0;
            aux->jogando = 1;
            aux = aux->proximo;
        } while(aux != jogadores->inicio);

        // Começar a rodada a partir do jogador 1 e não do dealer(jogador 0)
        jogador *jogador_da_vez = jogadores->inicio->proximo;
        apostas(jogadores);

        // Distribuição inicial de 2 cartas para cada jogador
        distribuicao_inicial_de_cartas(jogadores, baralho, *quantos_jogadores);

        while(continuar_jogo) {

            int valido = 1;     // Opção do jogador é valida

            // Conferir se o jogador não ganhou um black jack na distribuição e se ganhou, ganha automaticamente a rodada
            jogador_da_vez->quantidade_de_cartas++;
            mostrar_mesa(jogadores, *quantos_jogadores);
            fez_blackjack(jogador_da_vez);
            jogador_da_vez->quantidade_de_cartas--;

            // Conferir se o jogador está jogando na rodada
            if(jogador_da_vez->jogando) {

                // Se for o dealer
                if(jogador_da_vez->indice_do_jogador == 0) {
                    
                    // Enquanto o dealer tiver que comprar
                    do {
                        jogador_da_vez->quantidade_de_cartas += 1;
                        if(dealer_vai_comprar(jogadores)) {
                            mostrar_mesa(jogadores, *quantos_jogadores);
                            printf("\n\nVez do Dealer jogar\n");
                            comprar_cartas(jogador_da_vez, baralho);
                            jogador_da_vez->quantidade_de_cartas++;
                            mostrar_carta_comprada(jogador_da_vez);
                            quanto_vale_o_as(jogador_da_vez);
                            reajustar_valor_do_as(jogador_da_vez);
                        }
                        else {
                            mostrar_mesa(jogadores, *quantos_jogadores);
                            printf("\n\nVez do Dealer jogar\n");
                            jogador_da_vez->jogando = 0;
                            getchar();
                        }
                        jogador_da_vez->quantidade_de_cartas-=1;
                    } while(dealer_vai_comprar(jogadores));
                }

                // Se for qualquer outro jogador
                else {
                    // Enquanto o jogador não quiser parar
                    do {
                        // Enquanto a opção escolhida pelo jogador não for válida
                        do {
                            mostrar_mesa(jogadores, *quantos_jogadores);

                            printf("\n\nVez do jogador %d%s\nDeseja...\n1) Comprar carta\n2) Parar\n%s%s-> ", jogador_da_vez->indice_do_jogador, (jogador_da_vez->split == 1 ? ".2" : ""), (jogador_da_vez->quantidade_de_cartas == 2 ? "3) Double Down\n" : ""), ((jogador_da_vez->quantidade_de_cartas == 2 && jogador_da_vez->mao.topo->num == jogador_da_vez->mao.topo->proximo->num && jogador_da_vez->ja_fez_split == 0) ? "4) Split\n" : ""));
                            scanf("%d", &opcao_do_jogador);
                            getchar();

                            if(opcao_do_jogador == 1) {
                                valido = 1;
                                jogador_da_vez->quantidade_de_cartas += 1;
                                comprar_cartas(jogador_da_vez, baralho);
                                mostrar_carta_comprada(jogador_da_vez);
                                quanto_vale_o_as(jogador_da_vez);
                                reajustar_valor_do_as(jogador_da_vez);
                                if(somatorio_das_cartas(jogador_da_vez) >= 21) {
                                    opcao_do_jogador = 2;
                                }
                            }
                            else if(opcao_do_jogador == 2) {
                                valido = 1;
                                jogador_da_vez->jogando = 0;
                                printf("\nO jogador %d%s escolheu parar de comprar cartas\n", jogador_da_vez->indice_do_jogador, (jogador_da_vez->split == 1 ? ".2" : ""));
                                getchar();
                            }
                            else if(opcao_do_jogador == 3 && jogador_da_vez->quantidade_de_cartas == 2) {
                                valido = 1;
                                double_down(jogador_da_vez, baralho, &opcao_do_jogador);
                            }
                            else if(opcao_do_jogador == 4 && jogador_da_vez->mao.topo->num == jogador_da_vez->mao.topo->proximo->num && jogador_da_vez->quantidade_de_cartas == 2 && jogador_da_vez->ja_fez_split == 0) {
                                valido = 1;
                                split(jogador_da_vez, baralho, quantos_jogadores, *indice);
                            }
                            else {
                                valido = 0;
                            }
                        } while(!valido);
                    } while(opcao_do_jogador != 2);
                }

                // Conferir se o jogador fez blackjack ou se estourou
                conferir_situacao_jogador(jogador_da_vez);
            }
            if(jogador_da_vez == jogadores->inicio) {
                continuar_jogo = 0;
            }
            
            jogador_da_vez = jogador_da_vez->proximo;
        } 

        // Se todo mundo parou final da partida
        conferir_final_da_partida(jogadores, &continuar_mesa);
        continuar_jogo = 0;

        if(continuar_mesa == 1) {
            // Limpar tela e perguntar se alguém deseja sair da mesa
            system("clear");
            
            // Verificar se alguém deseja sair da mesa
            jogador *temp = jogadores->inicio->proximo;
            while(temp != jogadores->inicio) {
                int op;
                printf("O jogador %d%s deseja sair da mesa?\n1) Sim\n2) Não\n-> ", temp->indice_do_jogador, (temp->split == 1 ? ".2" : ""));
                do {
                    scanf("%d", &op);
                } while(op != 1 && op != 2);
                if(op == 1) {

                    printf("\nOBRIGADO POR JOGAR JOGADOR %d%s!\n", temp->indice_do_jogador, (temp->split == 1 ? ".2" : ""));
                    printf("===========================================\n");

                    // Jogador saiu da mesa
                    jogador *aux = temp;
                    while(temp->proximo != aux) {
                        temp = temp->proximo;
                    }
                    if(temp->proximo->split == 0 && temp->proximo->proximo->split == 0) {
                        aux = temp->proximo;
                        temp->proximo = temp->proximo->proximo;
                        free(aux);

                        // Atualizar quantidade de jogadores
                        (*quantos_jogadores)--;
                    }
                    else if(temp->proximo->split == 0 && temp->proximo->proximo->split == 1) {
                        do {
                            aux = temp->proximo;
                            temp->proximo = temp->proximo->proximo;
                            free(aux);

                            // Atualizar quantidade de jogadores
                            (*quantos_jogadores)--;
                        } while(temp->proximo->split == 1);
                    }
                    else if(temp->proximo->split == 1) {
                        aux = temp->proximo;
                        temp->proximo = temp->proximo->proximo;
                        free(aux);

                        // Atualizar quantidade de jogadores
                        (*quantos_jogadores)--;
                    }
                }
                putchar('\n');
                
                temp = temp->proximo;
            }

            int op;
            printf("\nDeseja adicionar alguém na mesa?\n1) Sim\n2) Não\n-> ");
            do {
                scanf("%d", &op);
            } while(op != 1 && op != 2);
            if(op == 1) {
                int quantidade;
                printf("Quantas pessoas?\n-> ");
                scanf("%d", &quantidade);
                
                // Inserir novos jogadores na lista de jogadores
                for(int i = 0; i < quantidade; i++) {
                    inserir_jogador(jogadores, *indice);

                    // Atualizar quantidade de jogadores
                    (*quantos_jogadores)++;
                    (*indice)++;
                }
            }

            // Conferir se ainda há alguém na mesa
            if(*quantos_jogadores == 1) {
                continuar_mesa = 0;
            }
        }

        getchar();
    }
}

void apostas(jogadores *jogadores) {
    jogador *jogador_da_vez = jogadores->inicio->proximo;

    // Limpar tela
    system("clear");
    printf("Apostas para a rodada:\n\n");
    
    // Passar por todos jogadores
    while(jogador_da_vez != jogadores->inicio) {

        // Caso só tenha uma mão
        if(jogador_da_vez->split == 0 && jogador_da_vez->proximo->split == 0) {
            printf("Jogador %d: R$", jogador_da_vez->indice_do_jogador);
            scanf("%lf", &jogador_da_vez->aposta);
            jogador_da_vez->dinheiro -= jogador_da_vez->aposta;
            jogador_da_vez = jogador_da_vez->proximo;
        }

        // Tratar as mãos separadas de um jogador
        else if(jogador_da_vez->proximo->split == 1 && jogador_da_vez->split == 0) {
            int contador = 0;
            jogador *aux = jogador_da_vez;
            do {
                printf("Jogador %d%s: R$", aux->indice_do_jogador, (aux->split == 1 ? ".2" : ""));
                scanf("%lf", &aux->aposta);
                jogador_da_vez->dinheiro -= aux->aposta;

                aux = aux->proximo;
                contador++;
            } while(aux->split != 0);

            for(int i = 0; i < contador; i++) {
                jogador_da_vez->proximo->dinheiro = jogador_da_vez->dinheiro;
                jogador_da_vez = jogador_da_vez->proximo;
            }
        }
    }
    getchar();
}

void distribuicao_inicial_de_cartas(jogadores *jogadores, baralho *baralho, int quantos_jogadores) {
    jogador *aux = jogadores->inicio->proximo;
    
    for(int i = 0; i < quantos_jogadores * 2; i++) {
        
        system("clear");
        aux->quantidade_de_cartas += 1;
        comprar_cartas(aux, baralho);
        mostrar_carta_comprada(aux);
        quanto_vale_o_as(aux);

        aux = aux->proximo;
    }

}

void double_down(jogador *jogador, baralho *baralho, int *opcao_do_jogador) {
    
    // Dobrar a aposta
    printf("O jogador %d escolheu fazer o double down\n\n", jogador->indice_do_jogador);
    jogador->dinheiro -= jogador->aposta;
    jogador->aposta += jogador->aposta;
    printf("Nova aposta: R$%.2lf\n", jogador->aposta);

    // Compra da terceira carta
    comprar_cartas(jogador, baralho);
    mostrar_carta_comprada(jogador);
    quanto_vale_o_as(jogador);
    reajustar_valor_do_as(jogador);

    // Acabou a vez do jogador
    jogador->jogando = 0;
    *opcao_do_jogador = 2;

}

void split(jogador *jogador_da_vez, baralho *baralho, int *quantos_jogadores, int indice) {
    
    // Criar a outra mão
    printf("\nO jogador %d%s escolheu fazer o split\n\n", jogador_da_vez->indice_do_jogador, (jogador_da_vez->split == 1 ? ".2" : ""));
    
    jogador *nova_mao = criar_jogador(indice);
    
    // Corrigir dados
    nova_mao->split = 1;
    nova_mao->ja_fez_split = 1;
    jogador_da_vez->ja_fez_split = 1;
    nova_mao->dinheiro = jogador_da_vez->dinheiro;
    nova_mao->indice_do_jogador = jogador_da_vez->indice_do_jogador;
    nova_mao->aposta = jogador_da_vez->aposta;
    jogador_da_vez->dinheiro -= jogador_da_vez->aposta;
    
    nova_mao->proximo = jogador_da_vez->proximo;
    jogador_da_vez->proximo = nova_mao;

    // Passar uma das cartas para a outra mão
    nova_mao->mao.topo = jogador_da_vez->mao.topo;
    jogador_da_vez->mao.topo = jogador_da_vez->mao.topo->proximo;
    nova_mao->mao.topo->proximo = NULL;

    if(nova_mao->mao.topo->num == 1) {
        printf("O valor do Ás voltou a ser 11\n\n");
        nova_mao->mao.topo->valor = 11;
        jogador_da_vez->mao.topo->valor = 11;
    }

    // Corrigir quantidade de jogadores
    (*quantos_jogadores)++;

    // Comprar uma nova carta para cada mão e mostrar
    comprar_cartas(jogador_da_vez, baralho);
    mostrar_carta_comprada(jogador_da_vez);
    quanto_vale_o_as(jogador_da_vez);
    reajustar_valor_do_as(jogador_da_vez);

    comprar_cartas(nova_mao, baralho);
    mostrar_carta_comprada(nova_mao);
    quanto_vale_o_as(nova_mao);
    reajustar_valor_do_as(nova_mao);
    nova_mao->quantidade_de_cartas = 2;

}

int dealer_vai_comprar(jogadores *jogadores) {
    int soma_das_cartas = somatorio_das_cartas(jogadores->inicio);

    // Regra do 17
    // 1) O dealer deve comprar até bater 16
    // 2) O dealer deve parar de comprar se tiver 17 ou mais
    if(soma_das_cartas >= 17) {
        return 0;
    }

    return 1;
}

void mostrar_mesa(jogadores *jogadores, int quantos_jogadores) {
    system("clear");

    jogador *aux = jogadores->inicio;
    printf("\n        Dealer\n\n");
    printf("\\\\=================//\n");
    mostrar_cartas_do_jogador(aux);
    printf("\n");
    aux = aux->proximo;

    for(int indice = 1; indice < quantos_jogadores; indice++) {
        printf("\n      Jogador%d%s\n\n", aux->indice_do_jogador, (aux->split == 1 ? ".2" : ""));
        printf("\\\\=================//\n");
        mostrar_cartas_do_jogador(aux);
        printf("\n");

        aux = aux->proximo;
    }
}

void conferir_final_da_partida(jogadores *jogadores, int *continuar_mesa) {
    system("clear");
    
    jogador *aux = jogadores->inicio;
    int pontos_dealer = somatorio_das_cartas(aux);
    if(pontos_dealer > 21) {
        pontos_dealer = 0;
    }
    aux = aux->proximo;

    while(aux != jogadores->inicio) {

        // Se tiver apenas uma mão
        if(aux->proximo->split == 0) {

            // Tratando casos comuns e de BlackJack
            if((somatorio_das_cartas(aux) > 21 || somatorio_das_cartas(aux) < pontos_dealer) || (aux->blackjack == 0 && jogadores->inicio->blackjack == 1)) {
                printf("O jogador %d%s perdeu!\n", aux->indice_do_jogador, (aux->split == 1 ? ".2" : ""));
                printf("Dinheiro perdido: R$%.2lf\n", aux->aposta);
                jogadores->inicio->dinheiro += aux->aposta;
            }
            else if((somatorio_das_cartas(aux) == pontos_dealer) || (aux->blackjack == 1 && jogadores->inicio->blackjack == 1)) {
                printf("O jogador %d%s empatou!\n", aux->indice_do_jogador, (aux->split == 1 ? ".2" : ""));
                printf("Dinheiro devolvido: R$%.2lf\n", aux->aposta);
                aux->dinheiro += aux->aposta;
            }
            else if((somatorio_das_cartas(aux) > pontos_dealer) || (aux->blackjack == 1 && jogadores->inicio->blackjack == 0)) {
                printf("O jogador %d%s ganhou!\n", aux->indice_do_jogador, (aux->split == 1 ? ".2" : ""));
                if(aux->blackjack == 1) {
                    printf("Dinheiro devolvido: R$%.2lf\n", aux->aposta * 2.5);
                    aux->dinheiro += aux->aposta * 2.5;
                    jogadores->inicio->dinheiro -= aux->aposta * 2.5;
                }
                else {
                    printf("Dinheiro devolvido: R$%.2lf\n", aux->aposta * 2);
                    aux->dinheiro += aux->aposta * 2;
                    jogadores->inicio->dinheiro -= aux->aposta * 2;
                }
            }

                if(aux->dinheiro < 0) {
                    printf("Dinheiro que você deve: R$%.2lf  ''⌐(ಠ۾ಠ)¬''\n\n", aux->dinheiro - 2 * aux->dinheiro);
                }
                else {
                    printf("Dinheiro total: R$%.2lf\n\n", aux->dinheiro);
                }

            aux = aux->proximo;
        }

        // Se tiver feito split
        else {
            int contador = 0;
            jogador *temp = aux;
            do {
                // Tratando casos comuns e de BlackJack
                if((somatorio_das_cartas(temp) > 21 || somatorio_das_cartas(temp) < pontos_dealer) || (temp->blackjack == 0 && jogadores->inicio->blackjack == 1)) {
                    printf("O jogador %d%s perdeu!\n", temp->indice_do_jogador, (temp->split == 1 ? ".2" : ""));
                    printf("Dinheiro perdido: R$%.2lf\n", temp->aposta);
                    jogadores->inicio->dinheiro += temp->aposta;
                }
                else if((somatorio_das_cartas(temp) == pontos_dealer) || (temp->blackjack == 1 && jogadores->inicio->blackjack == 1)) {
                    printf("O jogador %d%s empatou!\n", temp->indice_do_jogador, (temp->split == 1 ? ".2" : ""));
                    printf("Dinheiro devolvido: R$%.2lf\n", temp->aposta);
                    aux->dinheiro += temp->aposta;
                }
                else if((somatorio_das_cartas(temp) > pontos_dealer) || (temp->blackjack == 1 && jogadores->inicio->blackjack == 0)) {
                    printf("O jogador %d%s ganhou!\n", temp->indice_do_jogador, (temp->split == 1 ? ".2" : ""));
                    if(temp->blackjack == 1) {
                        printf("Dinheiro devolvido: R$%.2lf\n", temp->aposta * 2.5);
                        aux->dinheiro += temp->aposta * 2.5;
                        jogadores->inicio->dinheiro -= temp->aposta * 2.5;
                    }
                    else {
                        printf("Dinheiro devolvido: R$%.2lf\n", temp->aposta * 2);
                        aux->dinheiro += temp->aposta * 2;
                        jogadores->inicio->dinheiro -= temp->aposta * 2;
                    }
                }

                contador++;
                temp = temp->proximo;
            } while(temp->split != 0);

            temp = aux;
            do {
                temp->dinheiro = aux->dinheiro;
                temp = temp->proximo;
            } while(temp->split == 1);

            if(aux->dinheiro < 0) {
                printf("Dinheiro que você deve: R$%.2lf  ''⌐(ಠ۾ಠ)¬''\n\n", aux->dinheiro - 2 * aux->dinheiro);
            }
            else {
                printf("Dinheiro total: R$%.2lf\n\n", aux->dinheiro);
            }

            for(int i = 0; i < contador; i++) {
                aux = aux->proximo;
            }
        }
    }

    getchar();

    if(jogadores->inicio->dinheiro <= 0) {
        system("clear");
        printf("    e88~-_       e      ,d88~~\\      e          ,88~-_   888   | 888~~  888~~\\  888~-_     ,88~-_   888   | \n");
        printf("   d888   \\     d8b     8888        d8b        d888   \\  888   | 888___ 888   | 888   \\   d888   \\  888   | \n");
        printf("   8888        /Y88b    `Y88b      /Y88b      88888    | 888   | 888    888 _/  888    | 88888    | 888   | \n");
        printf("   8888       /  Y88b    `Y88b,   /  Y88b     88888    | 888   | 888    888  \\  888   /  88888    | 888   | \n");
        printf("   Y888   /  /____Y88b     8888  /____Y88b     Y888 \\ /  Y88   | 888    888   | 888_-~    Y888   /  Y88   | \n");
        printf("    '88_-~  /      Y88b \\__88P' /      Y88b     `88__X    '8__/  888___ 888__/  888 ~-_    `88_-~    '8__/  \n");

        *continuar_mesa = 0;
                        
        getchar();   
    }
}