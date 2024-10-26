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

// Função para fazer login
int login_usuario() {
  Usuario usuario;
  char nome[50], senha[50];
  FILE *arquivo_bin = fopen(ARQUIVO_USUARIOS_BIN, "rb");

  printf("Digite seu nome: ");
  scanf("%s", nome);
  printf("Digite sua senha: ");
  scanf("%s", senha);

  // Verifica se o usuário existe no arquivo binário
  if (arquivo_bin) {
    while (fread(&usuario, sizeof(Usuario), 1, arquivo_bin) == 1) {
      if (strcmp(usuario.nome, nome) == 0 &&
          strcmp(usuario.senha, senha) == 0) {
        fclose(arquivo_bin);
        printf("Login bem-sucedido! Bem-vindo, %s!\n", usuario.nome);
        return 1;
      }
    }
    fclose(arquivo_bin);
  } else {
    printf("Erro ao abrir o arquivo de usuários em binário.\n");
  }

  printf("Nome ou senha inválidos!\n");
  return 0;
}

// Menu principal
int menu() {
  int opcao;

  do {
    printf("Escolha uma opção:\n");
    printf("1 - Cadastrar Usuário\n");
    printf("2 - Fazer Login\n");
    printf("3 - Sair\n");
    printf("Digite a opção escolhida: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
      cadastrar_usuario();
    } else if (opcao == 2) {
      if (login_usuario()) {
        return 1;
      }
    }
  } while (opcao != 3);

  printf("Saindo...\n");
  return 0;
}

// Menu pós-login
int menu_pos_login() {
  int opcao;

  do {
    printf("\nEscolha uma opção:\n");
    printf("1 - Jogar\n");
    printf("2 - Sair\n");
    printf("Digite a opção escolhida: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
      return 1; // Jogar
    } else if (opcao == 2) {
      printf("Saindo do jogo...\n");
      return 0; // Sair
    }
  } while (opcao != 2);

  return 0;
}

// Função para exibir o tabuleiro do jogador
void exibirTabuleiroJogador(char tabuleiro[SIZE][SIZE]) {
  printf("Tabuleiro do Jogador:\n");
  printf("   ");
  for (int i = 1; i <= SIZE; i++) {
    printf(" %d", i);
  }
  printf("\n");

  for (int i = 0; i < SIZE; i++) {
    printf("%2d ", i + 1);
    for (int j = 0; j < SIZE; j++) {
      printf(" %c", tabuleiro[i][j]);
    }
    printf("\n");
  }
}

// Função para exibir o tabuleiro do bot
void exibirTabuleiroBot(char tabuleiro[SIZE][SIZE]) {
    printf("Tabuleiro do Bot:\n");
    printf("   ");
    for (int i = 1; i <= SIZE; i++) {
        printf(" %d", i);
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf(" %c", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para inserir navios do jogador
void insereNaviosJogador(char tabuleiro[SIZE][SIZE], Navio *navios) {
  int x, y;

  for (int i = 0; i < NUM_NAVIOS; i++) {
    printf("Navio %d: ", i + 1);
    scanf("%d %d", &x, &y);

    // Ajusta as coordenadas para o índice do array (subtrai 1)
    navios[i].linha = x - 1;  
    navios[i].coluna = y - 1; 

    tabuleiro[navios[i].linha][navios[i].coluna] = 'N'; // 'N' indica a presença de um navio
  }
}

// Função para gerar posições dos navios do bot
void posicaoBot(Coordenada *naviosBot) {
    srand(time(NULL)); // Inicializa a semente para a geração de números aleatórios

    for (int i = 0; i < NUM_NAVIOS; i++) {
        naviosBot[i].x = rand() % SIZE; // Gera coordenada X
        naviosBot[i].y = rand() % SIZE; // Gera coordenada Y
    }
}

// Função para realizar as jogadas do jogador
int jogadas_jogador(char tabuleiroBot[SIZE][SIZE], int *naviosRestantes) {
    int x, y;

    for (int i = 0; i < 5; i++) { // Limite de 5 jogadas
        printf("Digite as coordenadas do seu ataque (ex: x y): ");
        scanf("%d %d", &x, &y);

        x -= 1;
        y -= 1;

        // Verifica se a jogada está dentro do tabuleiro
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            printf("Coordenadas fora do tabuleiro! Tente novamente.\n");
            i--; // Permite repetir a jogada
            continue;
        }

        // Verifica se a coordenada já foi atacada
        if (tabuleiroBot[x][y] == 'X' || tabuleiroBot[x][y] == 'O') {
            printf("Você já atacou essa posição. Escolha outra.\n");
            i--; // Permite repetir a jogada
            continue;
        }

        // Verifica se acertou um navio
        if (tabuleiroBot[x][y] == 'N') {
            printf("%sAcertou um navio!%s\n", BGreen, reset);
            tabuleiroBot[x][y] = 'X'; // Marca como acerto
            (*naviosRestantes)--;     // Diminui o número de navios restantes do bot
        } else {
            printf("%sÁgua!%s\n", BRed, reset);
            tabuleiroBot[x][y] = 'O'; // Marca como erro
        }
    }

    return 0; // Retorna 0 ao final das jogadas
}

// Função para a jogada do bot
void jogada_bot(char tabuleiroJogador[SIZE][SIZE], int *naviosRestantes) {
    int x, y;
    char resultado[SIZE][SIZE]; // Para armazenar os resultados dos ataques
    char ataques[5][50]; // Armazenar as mensagens de ataque
    int ataqueIndex = 0; // Índice para a mensagem de ataque

    // Inicializa o tabuleiro de resultados
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            resultado[i][j] = '~'; // Espaços vazios
        }
    }

    for (int i = 0; i < 5; i++) { // Limita a 5 jogadas
        do {
            x = rand() % SIZE;
            y = rand() % SIZE;
        } while (tabuleiroJogador[x][y] == 'X' || tabuleiroJogador[x][y] == 'O');

        // Verifica se acertou um navio
        if (tabuleiroJogador[x][y] == 'N') {
            snprintf(ataques[ataqueIndex], sizeof(ataques[ataqueIndex]), "O bot acertou um navio na posição (%d, %d)!", x + 1, y + 1);
            resultado[x][y] = 'X'; // Marca como acerto
            (*naviosRestantes)--;  // Diminui o número de navios restantes do jogador
        } else {
            snprintf(ataques[ataqueIndex], sizeof(ataques[ataqueIndex]), "O bot atirou na água na posição (%d, %d).", x + 1, y + 1);
            resultado[x][y] = 'O'; // Marca como erro
        }
        ataqueIndex++; // Avança o índice de ataque
    }

    // Exibe o tabuleiro do bot apenas uma vez após todas as jogadas
    printf("\nTabuleiro do Jogador:\n");
    printf("   ");
    for (int i = 1; i <= SIZE; i++) {
        printf(" %d", i);
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            if (tabuleiroJogador[i][j] == 'N') {
                printf(" N"); // Mostra os navios no tabuleiro
            } else {
                printf(" %c", resultado[i][j]); // Mostra os resultados dos ataques
            }
        }
        printf("\n");
    }

    // Exibe as mensagens de ataque após o tabuleiro
    printf("\nResultados dos ataques do bot:\n");
    for (int i = 0; i < ataqueIndex; i++) {
        printf("%s\n", ataques[i]);
    }
}
