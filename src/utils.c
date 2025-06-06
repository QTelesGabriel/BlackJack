#include "../include/utils.h"
#include "../include/jogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

void menu_inicial() {    
    int op;
    int loop = 1;

    while(loop) {
        system("clear");
        print_logo();
        printf("\n\n1) Jogar\n2) Regras\n3) Sair\n\n-> ");
        
        scanf("%d", &op);

        switch(op) {
            case 1:
                jogar();
                break;

            case 2:
                regras();
                break;

            case 3:
                loop = 0;
                break;
            
            default:
                printf("\nOpção inválida!\nEscolha outra...\n");
                getchar();
                break;
        }
    }
}

void regras() {

    system("clear");

    printf("Objetivo: Obter uma mão com um valor mais próximo de 21 do que a mão do dealer, sem exceder 21.\n\n");
    printf("Valores das cartas:\n\n");
    printf("    - As cartas numéricas de 2 a 10 têm seu valor normal\n");
    printf("    - As cartas de valete, dama e rei valem 10 pontos cada.\n");
    printf("    - O ás pode valer 1 ponto ou 11 pontos, dependendo da melhor estratégia para a mão.\n\n");
    printf("Desenvolvimento do Jogo:\n\n");
    printf("Aposta: Os jogadores fazem suas apostas antes das cartas serem distribuídas.\n\n");
    printf("Distribuição de cartas: O dealer distribui duas cartas para cada jogador, incluindo para si mesmo. As cartas do jogador são distribuídas viradas para cima, enquanto o dealer recebe uma carta virada para cima e outra virada para baixo (carta 'buraco').\n\n");
    printf("Jogada do Jogador: Os jogadores têm várias opções:\n");
    printf("    - Pedir (Hit): Receber uma carta adicional para tentar chegar mais perto de 21.\n");
    printf("    - Ficar (Stand): Não pedir mais cartas e manter o valor atual da mão.\n");
    printf("    - Dobrar (Double Down): Dobrar a aposta inicial e receber exatamente mais uma carta.\n");
    printf("    - Dividir (Split): Se as duas primeiras cartas tiverem o mesmo valor, o jogador pode dividir em duas mãos separadas.\n\n");
    printf("Jogada do Dealer: Depois que os jogadores finalizam suas jogadas, o dealer revela a carta virada para baixo e deve pedir cartas até atingir um total de 17 ou mais.\n\n");
    printf("Comparação das Mãos: As mãos do jogador são comparadas com a do dealer para determinar o vencedor. Se o jogador tiver mais perto de 21 do que o dealer, sem exceder, ou se o dealer ultrapassar 21, o jogador vence.\n\n");
    printf("Pagamento das Apostas: Os ganhos são pagos de acordo com as seguintes regras:\n");
    printf("    - 1:1 para vitória padrão\n");
    printf("    - 3:2 para um blackjack (um ás e uma carta de valor 10).\n\n");
    printf("Blackjack (Natural): Um blackjack ocorre quando um jogador ou o dealer recebe um ás e uma carta de valor 10 como as duas primeiras cartas, resultando em um pagamento melhor (3:2).\n\n");
    printf("Neste jogo todos jogadores começam com R$1.000.000,00.\n\nAlém disso, em todo final de rodada há a opção de alguém sair do jogo ou de adicionar novos jogadores.\n");

    getchar();
    getchar();
}

void print_logo() {     // Função para imprimir o nome do jogo
    printf("888      888                   888       d8b                   888      \n");
    printf("888      888                   888       Y8P                   888      \n");
    printf("888      888                   888                             888      \n");
    printf("88888b.  888  8888b.   .d8888b 888  888 8888  8888b.   .d8888b 888  888 \n");
    printf("888 '88b 888     '88b d88P'    888 .88P '888     '88b d88P'    888 .88P \n");
    printf("888  888 888 .d888888 888      888888K   888 .d888888 888      888888K  \n");
    printf("888 d88P 888 888  888 Y88b.    888 '88b  888 888  888 Y88b.    888 '88b \n");
    printf("88888P'  888 'Y888888  'Y8888P 888  888  888 'Y888888  'Y8888P 888  888 \n");
    printf("                                         888                            \n");
    printf("                                        d88P                            \n");
    printf("                                      888P'                             \n");
}