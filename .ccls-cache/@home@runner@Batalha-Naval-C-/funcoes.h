#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 10
#define NUM_NAVIOS 7

typedef struct {
    char nome[50];  
    char senha[50]; 
} Usuario;

typedef struct {
    int x;
    int y;
} Coordenada;

typedef struct {
    int linha;
    int coluna;
} Navio;


extern const char *ARQUIVO_USUARIOS_TXT; 
extern const char *ARQUIVO_USUARIOS_BIN;

void cadastrar_usuario();
int login_usuario();
int menu();
int menu_pos_login();
void exibirTabuleiroJogador(char tabuleiro[SIZE][SIZE]);
void exibirTabuleiroBot(char tabuleiro[SIZE][SIZE]);
void insereNaviosJogador(char tabuleiro[SIZE][SIZE], Navio *navios);

#endif
