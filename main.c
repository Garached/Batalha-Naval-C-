#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

const char *BRed = "\033[1;31m"; 
const char *BGreen = "\033[1;32m";
const char *reset = "\033[0m"; 

const char *ARQUIVO_USUARIOS_TXT = "usuarios.txt"; 
const char *ARQUIVO_USUARIOS_BIN = "usuarios.bin";

int main(void) {
    srand(time(NULL)); // Inicializa a semente para o gerador de números aleatórios

    int op = menu();

      if (op == 1) {
            if (menu_pos_login()) {
                char tabuleiroJogador[SIZE][SIZE];
                char tabuleiroBot[SIZE][SIZE];
                Navio naviosJogador[NUM_NAVIOS];
                Coordenada naviosBot[NUM_NAVIOS];
                int numNaviosBot = NUM_NAVIOS; // Inicializa o número de navios do bot
                int numNaviosJogador = NUM_NAVIOS; // Inicializa o número de navios do jogador
                // Inicializa os tabuleiros
                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j < SIZE; j++) {
                        tabuleiroJogador[i][j] = '~'; // Espaços vazios
                        tabuleiroBot[i][j] = '~';
                    }
                }
                // Insere as coordenadas dos navios do jogador
                printf("Insira as %d coordenadas dos seus navios (ex: x y):\n", NUM_NAVIOS);
                insereNaviosJogador(tabuleiroJogador, naviosJogador);
                // Gera a posição dos navios do bot
                posicaoBot(naviosBot);
                for (int i = 0; i < NUM_NAVIOS; i++) {
                    tabuleiroBot[naviosBot[i].x][naviosBot[i].y] = 'N'; // Marca os navios no tabuleiro do bot
                }
                exibirTabuleiroJogador(tabuleiroJogador); // Mostra o tabuleiro do jogador
                printf("\n--- Agora é sua vez de atacar o Bot! ---\n");
                // Loop para as jogadas do jogador
                    jogadas_jogador(tabuleiroBot, &numNaviosBot);
                
                    // Exibe o tabuleiro do bot após todas as jogadas do jogador
                    printf("\nEstado do tabuleiro do Bot após a jogada do jogador:\n");
                    exibirTabuleiroBot(tabuleiroBot); 
                
                            
                    // Exibe o estado final do tabuleiro do jogador
                    printf("\nEstado do tabuleiro do jogador após a jogada do bot:\n");
                    // exibirTabuleiroJogador(tabuleiroJogador);
                    jogada_bot(tabuleiroJogador, &numNaviosJogador);
                
                    // Verifica o resultado do jogo
                    if (numNaviosBot < numNaviosJogador) {
                        printf("Parabéns! Você venceu o jogo!\n");
                    } 
                    else if (numNaviosJogador < numNaviosBot) {
                        printf("Você perdeu! O Bot derrubou mais navios que você!\n");
                    } 
                    else {
                        printf("Empate! O jogo terminou.\n");
                    }
                    return 0; 
            } 
        } 
        return 0; 
    }
