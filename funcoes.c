#include "funcoes.h"

// Função para cadastrar um novo usuário
void cadastrar_usuario() {
    Usuario novo_usuario;
    FILE *arquivo_txt = fopen(ARQUIVO_USUARIOS_TXT, "a"); 

    printf("Digite seu nome: ");
    scanf("%s", novo_usuario.nome);
    printf("Digite sua senha: ");
    scanf("%s", novo_usuario.senha);

    // Salva o usuário no arquivo de texto
    fprintf(arquivo_txt, "%s %s\n", novo_usuario.nome, novo_usuario.senha);
    fclose(arquivo_txt);

    // Salva o usuário no arquivo binário
    FILE *arquivo_bin = fopen(ARQUIVO_USUARIOS_BIN, "ab");
    if (arquivo_bin) {
        fwrite(&novo_usuario, sizeof(Usuario), 1, arquivo_bin);
        fclose(arquivo_bin);
        printf("Usuário cadastrado com sucesso!\n"); 
    } else {
        printf("Erro ao abrir o arquivo de usuários em binário.\n");
    }
}

