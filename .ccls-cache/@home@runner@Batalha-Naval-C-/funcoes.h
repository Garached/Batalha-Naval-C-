#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[50];  
    char senha[50]; 
} Usuario;

extern const char *ARQUIVO_USUARIOS_TXT; 
extern const char *ARQUIVO_USUARIOS_BIN;

void cadastrar_usuario();
int login_usuario();
int menu();
int menu_pos_login();

#endif
