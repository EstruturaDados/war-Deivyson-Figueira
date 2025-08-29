#include <stdio.h>
#include <stdlib.h> // Necessário para malloc, calloc, free
#include <string.h> // Necessário para strcmp e strcpy
#include <time.h>   // Necessário para srand e time

// --- Constantes Globais ---
#define TAM_NOME 30
#define TAM_COR 10

// --- Definição da Estrutura (struct) ---
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// --- Protótipos das Funções ---
void limparBufferEntrada();
void cadastrarTerritorios(Territorio* mapa, int numTerritorios);
void listarTerritorios(Territorio* mapa, int numTerritorios);
void atacar(Territorio* atacante, Territorio* defensor);
int rolarDado();
void liberarMemoria(Territorio* mapa);
int verificarVitoria(Territorio* mapa, int numTerritorios);

// --- Função Principal (main) ---
int main() {
    // Inicializa a semente para a geração de números aleatórios
    srand(time(NULL));

    int opcao = 1; // Mantém o loop ativo por padrão
    int numTerritorios = 0;
    Territorio* mapa = NULL; // Ponteiro para o array dinâmico

    // --- CADASTRO INICIAL DOS TERRITÓRIOS ---
    printf("====================================\n");
    printf("         DESAFIO WAR - AVENTUREIRO\n");
    printf("====================================\n");
    printf("\n--- CADASTRO INICIAL ---\n");
    printf("Por favor, digite a quantidade de territórios que serão cadastrados: ");
    if (scanf("%d", &numTerritorios) != 1 || numTerritorios <= 0) {
        printf("Entrada inválida. Encerrando o programa.\n");
        return 1;
    }
    limparBufferEntrada();

    // Alocação dinâmica de memória com calloc para inicializar com zero
    mapa = (Territorio*)calloc(numTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória. Encerrando o programa.\n");
        return 1;
    }
    
    cadastrarTerritorios(mapa, numTerritorios);
    printf("\nCadastro concluído!\n");
    
    // --- LAÇO PRINCIPAL DO JOGO ---
    do {
        int indiceAtacante, indiceDefensor;
        
        printf("\n--- FASE DE ATAQUE ---\n");
        // A lista é exibida no início de cada rodada para mostrar o estado atual
        listarTerritorios(mapa, numTerritorios);
        
        printf("Escolha o índice do território atacante (1 a %d): ", numTerritorios);
        scanf("%d", &indiceAtacante);

        printf("Escolha o índice do território defensor (1 a %d): ", numTerritorios);
        scanf("%d", &indiceDefensor);
        limparBufferEntrada();

        // Converte a entrada do usuário (1 a N) para o índice do array (0 a N-1)
        indiceAtacante--;
        indiceDefensor--;
        
        // Validação de entrada
        if (indiceAtacante < 0 || indiceAtacante >= numTerritorios || 
            indiceDefensor < 0 || indiceDefensor >= numTerritorios) {
            printf("\nÍndices de territórios inválidos. Tente novamente.\n");
        } else if (indiceAtacante == indiceDefensor) {
            printf("\nUm território não pode atacar a si mesmo. Tente novamente.\n");
        } else if (strcmp(mapa[indiceAtacante].cor, mapa[indiceDefensor].cor) == 0) {
            printf("\nVocê não pode atacar um território da mesma cor. Tente novamente.\n");
        } else {
            // Chamada da função de ataque
            atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);
            
            // Verifica se algum jogador venceu
            if (verificarVitoria(mapa, numTerritorios)) {
                printf("\n====================================\n");
                printf("         FIM DO JOGO!\n");
                printf("====================================\n");
                break;
            }
        }

        // Opção para continuar ou sair
        printf("\nPressione 'Enter' para continuar ou digite '0' para sair: ");
        char entrada[10];
        if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
            if (entrada[0] == '0' || entrada[1] == '0') {
                opcao = 0;
            }
        }
    } while (opcao != 0);

    // Libera a memória alocada antes de encerrar o programa
    liberarMemoria(mapa);

    return 0;
}

// --- Implementação das Funções ---

/**
 * @brief Limpa o buffer de entrada.
 */
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Cadastra os territórios com nome, cor e número de tropas.
 *
 * @param mapa Ponteiro para o primeiro território no array.
 * @param numTerritorios Número total de territórios a serem cadastrados.
 */
void cadastrarTerritorios(Territorio* mapa, int numTerritorios) {
    for (int i = 0; i < numTerritorios; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome (sem espaços): ");
        scanf("%s", (mapa + i)->nome);
        printf("Cor do exército: ");
        scanf("%s", (mapa + i)->cor);
        printf("Número de tropas: ");
        scanf("%d", &(mapa + i)->tropas);
        limparBufferEntrada();
    }
}

/**
 * @brief Lista todos os territórios cadastrados.
 *
 * @param mapa Ponteiro para o primeiro território no array.
 * @param numTerritorios Número total de territórios cadastrados.
 */
void listarTerritorios(Territorio* mapa, int numTerritorios) {
    if (mapa == NULL || numTerritorios <= 0) {
        printf("\nNenhum território para listar. Por favor, cadastre primeiro.\n");
        return;
    }
    printf("\n--- LISTA DE TERRITÓRIOS ATUALIZADA ---\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("Índice %d: %s (%s) - Tropas: %d\n", i + 1, (mapa + i)->nome, (mapa + i)->cor, (mapa + i)->tropas);
    }
    printf("----------------------------------------\n");
}

/**
 * @brief Simula um ataque entre dois territórios.
 *
 * @param atacante Ponteiro para a struct do território atacante.
 * @param defensor Ponteiro para a struct do território defensor.
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = rolarDado();
    int dadoDefensor = rolarDado();
    
    printf("\n--- Batalha entre %s (%s) e %s (%s) ---\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dados sorteados:\n");
    printf("O atacante (%s) rolou o dado e tirou %d\n", atacante->nome, dadoAtacante);
    printf("O defensor (%s) rolou o dado e tirou %d\n", defensor->nome, dadoDefensor);

    // Lógica para vitória do atacante
    if (dadoAtacante > dadoDefensor) {
        printf("\nO ataque de %s foi um sucesso!\n", atacante->nome);
        
        // Se o defensor tem mais de uma tropa, há um simples movimento de tropas
        if (defensor->tropas > 1) {
            defensor->tropas--;
            atacante->tropas++;
            printf("%s perdeu uma tropa, agora possui %d tropas.\n", defensor->nome, defensor->tropas);
            printf("E %s ganhou uma tropa, agora possui %d tropas.\n", atacante->nome, atacante->tropas);
        } else {
            // Conquista do território: defensor fica sem tropas
            strcpy(defensor->cor, atacante->cor);
            // Move uma tropa do atacante para o novo território
            atacante->tropas--;
            defensor->tropas = 1; 
            printf("O território de %s foi conquistado por %s!\n", defensor->nome, atacante->nome);
        }
    } 
    // Lógica para derrota do atacante
    else if (dadoAtacante < dadoDefensor) {
        printf("\nO ataque falhou. E %s perdeu uma tropa.\n", atacante->nome);
        
        // Se o atacante tem mais de uma tropa, há um simples movimento de tropas
        if (atacante->tropas > 1) {
            atacante->tropas--;
            defensor->tropas++;
            printf("%s perdeu uma tropa, agora possui %d tropas.\n", atacante->nome, atacante->tropas);
            printf("E %s ganhou uma tropa, agora possui %d tropas.\n", defensor->nome, defensor->tropas);
        } else {
            // Conquista do território: atacante fica sem tropas e perde o território para o defensor
            strcpy(atacante->cor, defensor->cor);
            // Move uma tropa do defensor para o novo território
            defensor->tropas--;
            atacante->tropas = 1;
            printf("O território de %s foi conquistado por %s!\n", atacante->nome, defensor->nome);
        }

    } 
    // Lógica para empate
    else { 
        printf("\nO ataque resultou em empate. Nenhuma tropa foi perdida ou ganha.\n");
    }
}


/**
 * @brief Rola um dado de 6 faces.
 *
 * @return Um número aleatório de 1 a 6.
 */
int rolarDado() {
    return rand() % 6 + 1;
}

/**
 * @brief Libera a memória alocada dinamicamente.
 *
 * @param mapa Ponteiro para a área de memória a ser liberada.
 */
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
        mapa = NULL;
    }
}

/**
 * @brief Verifica se um jogador conquistou todos os territórios.
 *
 * @param mapa Ponteiro para o primeiro território no array.
 * @param numTerritorios Número total de territórios cadastrados.
 * @return 1 se um jogador venceu, 0 caso contrário.
 */
int verificarVitoria(Territorio* mapa, int numTerritorios) {
    if (numTerritorios <= 1) {
        return 0; // O jogo continua apenas com mais de um território.
    }

    // Pega a cor do primeiro território como referência
    const char* corVencedora = mapa[0].cor;

    // Percorre o mapa a partir do segundo território
    for (int i = 1; i < numTerritorios; i++) {
        // Se encontrar um território com cor diferente, o jogo continua
        if (strcmp(mapa[i].cor, corVencedora) != 0) {
            return 0;
        }
    }

    // Se todos os territórios tiverem a mesma cor, há um vencedor
    printf("\nParabéns! %s venceu a guerra!\n", mapa[0].nome);
    return 1;
}
