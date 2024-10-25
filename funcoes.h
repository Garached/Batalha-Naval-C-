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

const char *ARQUIVO_USUARIOS_TXT = "usuarios.txt"; 
const char *ARQUIVO_USUARIOS_BIN = "usuarios.bin"; 

void cadastrar_usuario();
int login_usuario();

#endif