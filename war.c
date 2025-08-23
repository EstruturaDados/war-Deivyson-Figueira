// ============================================================================
// ============================================================================
//      --- PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO - NÍVEL NOVATO ---
// ============================================================================
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
