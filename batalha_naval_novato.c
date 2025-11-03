#include <stdio.h>
#include <stdbool.h> // Para usar o tipo 'bool' (true/false) nas validações

// --- Constantes de Configuração (Simplificações) ---
#define TAMANHO_TABULEIRO 10 // Tabuleiro fixo 10x10
#define TAMANHO_NAVIO 3      // Navios de tamanho fixo 3
#define AGUA 0               // Valor para representar água
#define NAVIO 3              // Valor para representar um navio

/**
 * @brief Inicializa o tabuleiro com água (valor 0).
 * * R1: Represente o Tabuleiro - Inicialize todas as posições com 0.
 * * @param tabuleiro A matriz 10x10 a ser inicializada.
 */
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Loop aninhado para percorrer cada célula da matriz
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

/**
 * @brief Exibe o estado atual do tabuleiro no console.
 * * R3: Exiba o Tabuleiro - Mostra a matriz 0s e 3s de forma organizada.
 * R10: Legibilidade - Adiciona cabeçalhos de linha e coluna.
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
 * @brief Verifica se a posição de um navio é válida no tabuleiro.
 * * R5: Validar Limites - Verifica se o navio cabe no tabuleiro.
 * R6: Validar Sobreposição - Verifica se já existe um navio no local.
 * * @param tabuleiro O tabuleiro 10x10.
 * @param linha A linha inicial do navio.
 * @param coluna A coluna inicial do navio.
 * @param ehVertical 'true' se o navio for vertical, 'false' se for horizontal.
 * @return 'true' se a posição for válida, 'false' caso contrário.
 */
bool verificarPosicaoValida(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                              int linha, int coluna, bool ehVertical) {
    
    // R5: Validação de Limites
    if (ehVertical) {
        // Se for vertical, verifica se a (linha + tamanho) ultrapassa o limite
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            printf("Erro de validacao: Navio vertical sai do tabuleiro.\n");
            return false;
        }
    } else {
        // Se for horizontal, verifica se a (coluna + tamanho) ultrapassa o limite
        if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            printf("Erro de validacao: Navio horizontal sai do tabuleiro.\n");
            return false;
        }
    }

    // R6: Validação de Sobreposição
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (ehVertical) {
            // Verifica cada célula que o navio vertical ocuparia
            if (tabuleiro[linha + i][coluna] == NAVIO) {
                printf("Erro de validacao: Sobreposicao de navios detectada.\n");
                return false;
            }
        } else {
            // Verifica cada célula que o navio horizontal ocuparia
            if (tabuleiro[linha][coluna + i] == NAVIO) {
                printf("Erro de validacao: Sobreposicao de navios detectada.\n");
                return false;
            }
        }
    }

    // Se passou por todas as verificações, a posição é válida
    return true;
}

/**
 * @brief Posiciona um navio no tabuleiro, marcando suas posições com o valor 3.
 * * R2: Posicione os Navios - Marca a matriz com o valor 3.
 * * @param tabuleiro O tabuleiro 10x10.
 * @param linha A linha inicial do navio.
 * @param coluna A coluna inicial do navio.
 * @param ehVertical 'true' para navio vertical, 'false' para horizontal.
 */
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                       int linha, int coluna, bool ehVertical) {
    
    // Loop para preencher as 3 posições do navio
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (ehVertical) {
            // Se for vertical, incrementa a linha
            tabuleiro[linha + i][coluna] = NAVIO;
        } else {
            // Se for horizontal, incrementa a coluna
            tabuleiro[linha][coluna + i] = NAVIO;
        }
    }
}

/**
 * @brief Função principal (main) do programa.
 * * Coordena a inicialização, posicionamento e exibição do tabuleiro.
 * R4: Entrada de Dados - Coordenadas definidas diretamente no código.
 * R9: Documentação - Comentários explicando o fluxo.
 * R10: Legibilidade - Código organizado.
 */
int main() {
    
    // R1: Declara a matriz (vetor bidimensional) para o tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // R4: Define as coordenadas iniciais dos navios diretamente no código
    // (Você pode alterar esses valores para testar as validações)
    int navioVertical_linha = 2;
    int navioVertical_coluna = 3;
    
    int navioHorizontal_linha = 5;
    int navioHorizontal_coluna = 5; // Tente (5, 8) para testar limite
                                   // Tente (3, 3) para testar sobreposição

    printf("Iniciando Batalha Naval - Nivel Novato (Setup)\n");

    // 1. Inicializa o tabuleiro com água (0s)
    inicializarTabuleiro(tabuleiro);
    printf("Tabuleiro inicializado com agua (0).\n");

    // 2. Tenta posicionar o Navio Vertical
    printf("Tentando posicionar Navio Vertical em (%d, %d)...\n", 
           navioVertical_linha, navioVertical_coluna);
           
    // R5/R6: Valida a posição ANTES de posicionar
    if (verificarPosicaoValida(tabuleiro, navioVertical_linha, navioVertical_coluna, true)) {
        // R2: Posição é válida, então posiciona o navio
        posicionarNavio(tabuleiro, navioVertical_linha, navioVertical_coluna, true);
        printf("Navio Vertical posicionado com sucesso!\n");
    } else {
        printf("Falha ao posicionar Navio Vertical.\n");
    }

    // 3. Tenta posicionar o Navio Horizontal
    printf("Tentando posicionar Navio Horizontal em (%d, %d)...\n", 
           navioHorizontal_linha, navioHorizontal_coluna);

    // R5/R6: Valida a posição ANTES de posicionar
    if (verificarPosicaoValida(tabuleiro, navioHorizontal_linha, navioHorizontal_coluna, false)) {
        // R2: Posição é válida, então posiciona o navio
        posicionarNavio(tabuleiro, navioHorizontal_linha, navioHorizontal_coluna, false);
        printf("Navio Horizontal posicionado com sucesso!\n");
    } else {
        printf("Falha ao posicionar Navio Horizontal.\n");
    }

    // 4. R3/R7: Exibe o tabuleiro final com os navios
    exibirTabuleiro(tabuleiro);

    // R8: Performance - O programa é leve e executa instantaneamente
    return 0; // Termina o programa com sucesso
}