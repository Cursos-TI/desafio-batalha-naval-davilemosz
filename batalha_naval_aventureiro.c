#include <stdio.h>
#include <stdbool.h> // Para usar o tipo 'bool' (true/false)

// --- Constantes de Configuração (Simplificações) ---
#define TAMANHO_TABULEIRO 10 // R1: Tabuleiro 10x10
#define TAMANHO_NAVIO 3      // S2: Navios de tamanho fixo 3
#define AGUA 0               // Valor para representar água
#define NAVIO 3              // Valor para representar um navio

/**
 * @brief Define os tipos de orientação que um navio pode ter.
 * * Essencial para R2 (Permitir navios diagonais).
 */
typedef enum {
    VERTICAL,
    HORIZONTAL,
    DIAGONAL_TL_BR, // Top-Left para Bottom-Right (linha++, coluna++)
    DIAGONAL_TR_BL  // Top-Right para Bottom-Left (linha++, coluna--)
} Orientacao;

/**
 * @brief Inicializa o tabuleiro com água (valor 0).
 * * R1: Criar um Tabuleiro 10x10 - Inicializa com 0.
 * * @param tabuleiro A matriz 10x10 a ser inicializada.
 */
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // R7: Documentação - Loop para percorrer cada célula
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

/**
 * @brief Exibe o estado atual do tabuleiro no console.
 * * R5: Exibir o Tabuleiro Completo - Mostra a matriz 0s e 3s.
 * * R8: Legibilidade - Adiciona cabeçalhos de linha/coluna e espaços.
 * * @param tabuleiro A matriz 10x10 a ser exibida.
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n");
    
    // Imprime o cabeçalho das colunas (0 a 9)
    printf("   "); // Espaço para o cabeçalho da linha
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");

    // Imprime as linhas
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Imprime o cabeçalho da linha (0 a 9)
        printf("%d  ", i); 
        
        // Imprime o conteúdo da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n"); // Pula para a próxima linha
    }
    printf("==================================\n");
    printf("Legenda: %d = Agua, %d = Navio\n", AGUA, NAVIO);
}

/**
 * @brief Verifica se a posição de um navio é válida (dentro dos limites e sem sobreposição).
 * * R3: Validar Limites (para todas as 4 orientações).
 * R4: Validar Sobreposição (para todas as 4 orientações).
 * * @param tabuleiro O tabuleiro 10x10.
 * @param linha A linha inicial do navio.
 * @param coluna A coluna inicial do navio.
 * @param orient A orientação (VERTICAL, HORIZONTAL, DIAGONAL_TL_BR, DIAGONAL_TR_BL).
 * @return 'true' se a posição for válida, 'false' caso contrário.
 */
bool verificarPosicaoValida(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                              int linha, int coluna, Orientacao orient) {
    
    // --- 1. Validação de Limites (R3) ---
    // R7: Documentação - Verifica se o navio CABE no tabuleiro
    switch (orient) {
        case VERTICAL:
            if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
                printf("Erro de validacao: Navio Vertical (L%d,C%d) sai do tabuleiro.\n", linha, coluna);
                return false;
            }
            break;
        case HORIZONTAL:
            if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
                printf("Erro de validacao: Navio Horizontal (L%d,C%d) sai do tabuleiro.\n", linha, coluna);
                return false;
            }
            break;
        case DIAGONAL_TL_BR: // Precisa de espaço na linha E na coluna
            if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || 
                coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
                printf("Erro de validacao: Navio Diagonal TL_BR (L%d,C%d) sai do tabuleiro.\n", linha, coluna);
                return false;
            }
            break;
        case DIAGONAL_TR_BL: // Precisa de espaço na linha E na coluna (para trás)
            // (coluna - (TAMANHO_NAVIO - 1)) deve ser >= 0
            if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || 
                coluna - (TAMANHO_NAVIO - 1) < 0) {
                printf("Erro de validacao: Navio Diagonal TR_BL (L%d,C%d) sai do tabuleiro.\n", linha, coluna);
                return false;
            }
            break;
    }

    // --- 2. Validação de Sobreposição (R4, S3) ---
    // R7: Documentação - Verifica se alguma célula já está ocupada por NAVIO
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l_check = linha; // Coordenada da linha a checar
        int c_check = coluna; // Coordenada da coluna a checar
        
        // Calcula a célula [l_check][c_check] correta para esta parte do navio
        switch (orient) {
            case VERTICAL:       l_check += i; break;
            case HORIZONTAL:     c_check += i; break;
            case DIAGONAL_TL_BR: l_check += i; c_check += i; break;
            case DIAGONAL_TR_BL: l_check += i; c_check -= i; break;
        }

        // Se a célula calculada já for um navio, a posição é inválida
        if (tabuleiro[l_check][c_check] == NAVIO) {
            printf("Erro de validacao: Sobreposicao de navios em (%d, %d).\n", l_check, c_check);
            return false;
        }
    }

    // Se passou por todas as verificações, a posição é válida
    return true;
}

/**
 * @brief Posiciona um navio no tabuleiro (marca com valor 3).
 * * R2: Posicionar Quatro Navios - Função chamada para cada navio.
 * * @param tabuleiro O tabuleiro 10x10.
 * @param linha A linha inicial do navio.
 * @param coluna A coluna inicial do navio.
 * @param orient A orientação do navio.
 */
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                       int linha, int coluna, Orientacao orient) {
    
    // R7: Documentação - Loop para preencher as 3 posições do navio
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        // R8: Legibilidade - Usa switch para determinar qual célula pintar
        switch (orient) {
            case VERTICAL:
                tabuleiro[linha + i][coluna] = NAVIO;
                break;
            case HORIZONTAL:
                tabuleiro[linha][coluna + i] = NAVIO;
                break;
            case DIAGONAL_TL_BR: // (l++, c++)
                tabuleiro[linha + i][coluna + i] = NAVIO;
                break;
            case DIAGONAL_TR_BL: // (l++, c--)
                tabuleiro[linha + i][coluna - i] = NAVIO;
                break;
        }
    }
}

/**
 * @brief Função principal (main) do programa.
 * * Coordena a inicialização, posicionamento (4 navios) e exibição.
 * S1: Coordenadas definidas diretamente no código.
 * R6: Performance - Execução eficiente.
 */
int main() {
    
    // R1: Declara a matriz 10x10
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // S1: Define as coordenadas iniciais dos 4 navios
    
    // R2: Navio 1 (Vertical)
    int l1 = 1, c1 = 1; Orientacao o1 = VERTICAL;
    // Posições: (1,1), (2,1), (3,1)
    
    // R2: Navio 2 (Horizontal)
    int l2 = 1, c2 = 6; Orientacao o2 = HORIZONTAL;
    // Posições: (1,6), (1,7), (1,8)
    
    // R2: Navio 3 (Diagonal TL_BR)
    int l3 = 3, c3 = 3; Orientacao o3 = DIAGONAL_TL_BR;
    // Posições: (3,3), (4,4), (5,5)

    // R2: Navio 4 (Diagonal TR_BL)
    int l4 = 5, c4 = 8; Orientacao o4 = DIAGONAL_TR_BL;
    // Posições: (5,8), (6,7), (7,6)

    printf("Iniciando Batalha Naval - Nivel Intermediario (Setup)\n");

    // 1. R1: Inicializa o tabuleiro com água (0s)
    inicializarTabuleiro(tabuleiro);
    printf("Tabuleiro inicializado com agua (0).\n");

    // --- 2. Posicionamento dos Navios (R2, R3, R4) ---

    // Navio 1 (Vertical)
    if (verificarPosicaoValida(tabuleiro, l1, c1, o1)) {
        posicionarNavio(tabuleiro, l1, c1, o1);
        printf("Navio 1 (Vertical) posicionado com sucesso!\n");
    } else {
        printf("Falha ao posicionar Navio 1.\n");
    }

    // Navio 2 (Horizontal)
    if (verificarPosicaoValida(tabuleiro, l2, c2, o2)) {
        posicionarNavio(tabuleiro, l2, c2, o2);
        printf("Navio 2 (Horizontal) posicionado com sucesso!\n");
    } else {
        printf("Falha ao posicionar Navio 2.\n");
    }

    // Navio 3 (Diagonal TL_BR)
    if (verificarPosicaoValida(tabuleiro, l3, c3, o3)) {
        posicionarNavio(tabuleiro, l3, c3, o3);
        printf("Navio 3 (Diagonal TL-BR) posicionado com sucesso!\n");
    } else {
        printf("Falha ao posicionar Navio 3.\n");
    }
    
    // Navio 4 (Diagonal TR_BL)
    if (verificarPosicaoValida(tabuleiro, l4, c4, o4)) {
        posicionarNavio(tabuleiro, l4, c4, o4);
        printf("Navio 4 (Diagonal TR-BL) posicionado com sucesso!\n");
    } else {
        printf("Falha ao posicionar Navio 4.\n");
    }

    // 3. R5: Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    // R6: Performance - Execução instantânea
    return 0; // Termina o programa com sucesso
}