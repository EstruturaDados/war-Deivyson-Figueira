// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================
#include <stdio.h>
#include <string.h>

// --- Constantes Globais ---
// Define o número máximo de territórios e os tamanhos dos arrays de caracteres.
#define NUM_TERRITORIOS_MAX 5
#define TAM_NOME 30
#define TAM_COR 10

// --- Definição da Estrutura (struct) ---
// Agrupa as informações de um território: nome, cor do exército e número de tropas.
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// --- Função para limpar o buffer de entrada ---
// Garante que a entrada de dados do teclado não cause problemas em leituras futuras.
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função Principal (main) ---
// Orquestra o fluxo do programa através de um menu interativo.
int main() {
    // Declara um vetor estático para armazenar os territórios.
    Territorio mapa[NUM_TERRITORIOS_MAX];

    int opcao;
    int totalTerritorios = 0;

    // --- Laço Principal do Menu ---
    do {
        // Exibe o menu de opções.
        printf("====================================\n");
        printf("        DESAFIO WAR - NOVATO\n");
        printf("====================================\n");
        printf("1 - Cadastrar novo territorio\n");
        printf("2 - Listar todos os territorios\n");
        printf("0 - Sair\n");
        printf("------------------------------------\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        limparBufferEntrada();

        // --- Processamento das Opções ---
        switch (opcao) {
            case 1: // CADASTRO DE TERRITÓRIO
                printf("\n--- Cadastro de Novo Territorio ---\n\n");
                
                if (totalTerritorios < NUM_TERRITORIOS_MAX) {
                    // Laço 'for' para preencher os dados dos 5 territórios.
                    for (int i = 0; i < NUM_TERRITORIOS_MAX; i++) {
                        printf("Territorio %d:\n", i + 1);
                        
                        printf("  Nome (sem espacos): ");
                        scanf("%s", mapa[i].nome);
                        
                        printf("  Cor do exercito: ");
                        scanf("%s", mapa[i].cor);

                        printf("  Numero de tropas: ");
                        scanf("%d", &mapa[i].tropas);
                        
                        while (getchar() != '\n');
                        printf("\n");
                    }
                    totalTerritorios = NUM_TERRITORIOS_MAX; // Marca como preenchido.
                    printf("Todos os 5 territorios foram cadastrados com sucesso!\n");
                } else {
                    printf("Os territorios ja foram todos cadastrados.\n");
                }
                
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 2: // LISTAGEM DE TERRITÓRIOS
                printf("\n--- Lista de Territorios ---\n\n");
                
                if (totalTerritorios == 0) {
                    printf("Nenhum territorio cadastrado ainda.\n");
                } else {
                    // Laço 'for' para exibir os dados de todos os territórios cadastrados.
                    for (int i = 0; i < totalTerritorios; i++) {
                        printf("Territorio %d\n", i + 1);
                        printf("  Nome: %s\n", mapa[i].nome);
                        printf("  Cor: %s\n", mapa[i].cor);
                        printf("  Tropas: %d\n", mapa[i].tropas);
                        printf("------------------------------------\n");
                    }
                }

                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 0: // SAIR
                printf("\nSaindo do sistema...\n");
                break;

            default: // Opção Inválida
                printf("\nOpcao invalida! Tente novamente.\n");
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
        }

    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
