#include <stdio.h>
#include <stdbool.h> // Para 'bool'
#include <stdlib.h>  // Para 'abs()' (cálculo do Octaedro/Losango)

// --- Constantes Globais ---
#define TAMANHO_TABULEIRO 10 // Tabuleiro principal 10x10
#define TAMANHO_NAVIO 3      // Navios de tamanho fixo 3
#define TAMANHO_HABILIDADE 5 // R: Matrizes de habilidade 5x5

// --- Constantes de Visualização ---
#define AGUA 0               // Valor para representar água
#define NAVIO 3              // Valor para representar um navio
#define EFEITO_HABILIDADE 5  // R: Valor para área de efeito (ex: 5)

/**
 * @brief Define os tipos de orientação que um navio pode ter.
 */
typedef enum {
    VERTICAL,
    HORIZONTAL,
    DIAGONAL_TL_BR, // Top-Left para Bottom-Right (linha++, coluna++)
    DIAGONAL_TR_BL  // Top-Right para Bottom-Left (linha++, coluna--)
} Orientacao;

/**
 * @brief Define os tipos de habilidades especiais.
 * * R1: Criar matrizes para Cone, Cruz e Octaedro.
 */
typedef enum {
    CONE,
    CRUZ,
    OCTAEDRO // (Formato Losango/Diamante)
} HabilidadeTipo;


// --- Funções do Nível Anterior (Inicialização e Navios) ---

/**
 * @brief Inicializa o tabuleiro com água (valor 0).
 * * R: Definir o Tabuleiro 10x10.
 */
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

/**
 * @brief Verifica se a posição de um navio é válida.
 */
bool verificarPosicaoValida(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                              int linha, int coluna, Orientacao orient) {
    // Validação de Limites
    switch (orient) {
        case VERTICAL:
            if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return false;
            break;
        case HORIZONTAL:
            if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return false;
            break;
        case DIAGONAL_TL_BR:
            if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || 
                coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return false;
            break;
        case DIAGONAL_TR_BL:
            if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || 
                coluna - (TAMANHO_NAVIO - 1) < 0) return false;
            break;
    }

    // Validação de Sobreposição
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l_check = linha;
        int c_check = coluna;
        
        switch (orient) {
            case VERTICAL:       l_check += i; break;
            case HORIZONTAL:     c_check += i; break;
            case DIAGONAL_TL_BR: l_check += i; c_check += i; break;
            case DIAGONAL_TR_BL: l_check += i; c_check -= i; break;
        }
        // Se a célula já for um navio OU um efeito, a posição é inválida
        // (Modificado para não permitir posicionar navio em cima de efeito)
        if (tabuleiro[l_check][c_check] != AGUA) { 
            //printf("Debug: Sobreposicao detectada em (%d, %d)\n", l_check, c_check);
            return false;
        }
    }
    return true;
}

/**
 * @brief Posiciona um navio no tabuleiro (marca com valor NAVIO).
 */
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                       int linha, int coluna, Orientacao orient) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        switch (orient) {
            case VERTICAL:
                tabuleiro[linha + i][coluna] = NAVIO;
                break;
            case HORIZONTAL:
                tabuleiro[linha][coluna + i] = NAVIO;
                break;
            case DIAGONAL_TL_BR:
                tabuleiro[linha + i][coluna + i] = NAVIO;
                break;
            case DIAGONAL_TR_BL:
                tabuleiro[linha + i][coluna - i] = NAVIO;
                break;
        }
    }
}

// --- Novas Funções (Nível Avançado - Habilidades) ---

/**
 * @brief Cria a matriz de forma da habilidade (0s e 1s).
 * * R1, R2, R6: Usa loops aninhados e condicionais para definir as formas.
 * * R8: Documentação explicando a lógica de cada forma.
 * @param matriz A matriz (ex: 5x5) a ser preenchida.
 * @param tipo O tipo de habilidade (CONE, CRUZ, OCTAEDRO).
 */
void criarMatrizHabilidade(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], HabilidadeTipo tipo) {
    int centro = TAMANHO_HABILIDADE / 2; // Centro da matriz (ex: 2 para 5x5)

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            
            matriz[i][j] = 0; // R2: Inicializa com 0 (não afetado)
            
            // R6: Utilizar Condicionais
            switch (tipo) {
                case CONE:
                    // R8: Lógica do Cone: O centro (2,2) é o topo.
                    // Afeta as linhas abaixo do centro (i >= centro).
                    // A largura (abs(j-centro)) deve ser <= à distância do topo (i-centro).
                    if (i >= centro && abs(j - centro) <= (i - centro)) {
                        matriz[i][j] = 1; // R2: Afetado
                    }
                    break;
                    
                case CRUZ:
                    // R8: Lógica da Cruz: Afeta a linha do centro OU a coluna do centro.
                    if (i == centro || j == centro) {
                        matriz[i][j] = 1; // R2: Afetado
                    }
                    break;
                    
                case OCTAEDRO: // (Losango/Diamante)
                    // R8: Lógica do Octaedro: Usa "Distância de Manhattan".
                    // A soma das distâncias (vertical + horizontal) do centro
                    // deve ser <= ao raio (o próprio centro).
                    if (abs(i - centro) + abs(j - centro) <= centro) {
                        matriz[i][j] = 1; // R2: Afetado
                    }
                    break;
            }
        }
    }
}

/**
 * @brief Sobrepõe a matriz de habilidade no tabuleiro principal.
 * * R4: Sobrepor as matrizes, marcando o tabuleiro com EFEITO_HABILIDADE.
 * R6: Usa loops e condicionais para validar os limites do tabuleiro.
 * * @param tabuleiro O tabuleiro 10x10.
 * @param habilidade A matriz 5x5 com a forma da habilidade (0s e 1s).
 * @param origem_l Linha de origem (centro) no tabuleiro 10x10.
 * @param origem_c Coluna de origem (centro) no tabuleiro 10x10.
 */
void sobreporHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                          int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], 
                          int origem_l, int origem_c) {
    
    int centro_h = TAMANHO_HABILIDADE / 2; // Centro da matriz de habilidade (ex: 2)

    // R6: Estruturas de repetição aninhadas
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            
            // Se a matriz de habilidade (5x5) marca [i][j] como 1 (afetado)
            if (habilidade[i][j] == 1) {
                
                // R8: Lógica de Translação:
                // Calcula a coordenada correspondente no tabuleiro 10x10.
                // (i - centro_h) dá o deslocamento relativo (-2, -1, 0, 1, 2)
                int l_tabuleiro = origem_l + (i - centro_h);
                int c_tabuleiro = origem_c + (j - centro_h);

                // R6/S4: Condicional para validar limites do tabuleiro
                // Garante que a habilidade não "vaze" para fora do 10x10
                if (l_tabuleiro >= 0 && l_tabuleiro < TAMANHO_TABULEIRO &&
                    c_tabuleiro >= 0 && c_tabuleiro < TAMANHO_TABULEIRO) {
                    
                    // R4: Marca a posição do tabuleiro com o valor da habilidade
                    tabuleiro[l_tabuleiro][c_tabuleiro] = EFEITO_HABILIDADE;
                }
            }
        }
    }
}

/**
 * @brief Exibe o estado final do tabuleiro no console.
 * * R5: Exibir o tabuleiro com símbolos diferentes para Água, Navio e Efeito.
 * R9: Legibilidade.
 */
void exibirTabuleiroFinal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== TABULEIRO FINAL - BATALHA NAVAL ===\n");
    
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d  ", i); 
        
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            int celula = tabuleiro[i][j];
            
            // R5: Utiliza caracteres diferentes
            switch (celula) {
                case AGUA:
                    printf("~ "); // Água
                    break;
                case NAVIO:
                    printf("N "); // Navio
                    break;
                case EFEITO_HABILIDADE:
                    printf("* "); // Área afetada
                    break;
                default:
                    printf("? "); // Desconhecido (debug)
                    break;
            }
        }
        printf("\n");
    }
    printf("=======================================\n");
    printf("Legenda: ~ = Agua, N = Navio, * = Efeito Habilidade\n");
}


/**
 * @brief Função principal (main) do programa.
 * * R7: Performance (execução eficiente).
 * R9: Código organizado e legível.
 */
int main() {
    
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // --- 1. Inicialização ---
    inicializarTabuleiro(tabuleiro);
    printf("Iniciando Batalha Naval - Nivel Avancado (Setup)\n");

    // --- 2. Posicionamento dos Navios (Nível Intermediário) ---
    // (Posições escolhidas para interceptar as habilidades)
    if (verificarPosicaoValida(tabuleiro, 1, 1, VERTICAL))
        posicionarNavio(tabuleiro, 1, 1, VERTICAL); // (1,1), (2,1), (3,1)
    
    if (verificarPosicaoValida(tabuleiro, 1, 6, HORIZONTAL))
        posicionarNavio(tabuleiro, 1, 6, HORIZONTAL); // (1,6), (1,7), (1,8)
        
    if (verificarPosicaoValida(tabuleiro, 3, 3, DIAGONAL_TL_BR))
        posicionarNavio(tabuleiro, 3, 3, DIAGONAL_TL_BR); // (3,3), (4,4), (5,5)

    if (verificarPosicaoValida(tabuleiro, 5, 8, DIAGONAL_TR_BL))
        posicionarNavio(tabuleiro, 5, 8, DIAGONAL_TR_BL); // (5,8), (6,7), (7,6)
        
    printf("Navios posicionados.\n");

    // --- 3. Criação das Matrizes de Habilidade (R1, R2) ---
    int matrizCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int matrizCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int matrizOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    
    criarMatrizHabilidade(matrizCone, CONE);
    criarMatrizHabilidade(matrizCruz, CRUZ);
    criarMatrizHabilidade(matrizOctaedro, OCTAEDRO);
    printf("Matrizes de habilidade criadas.\n");
    
    // --- 4. Sobreposição das Habilidades (R3, R4) ---
    // S1: Posições das habilidades definidas no código.
    
    // Habilidade 1: CRUZ (centrada em 2,1 - vai acertar o navio vertical)
    int cruz_l = 2, cruz_c = 1;
    sobreporHabilidade(tabuleiro, matrizCruz, cruz_l, cruz_c);
    
    // Habilidade 2: OCTAEDRO (centrado em 5,7 - vai acertar os 2 navios diagonais)
    int octa_l = 5, octa_c = 7;
    sobreporHabilidade(tabuleiro, matrizOctaedro, octa_l, octa_c);
    
    // Habilidade 3: CONE (centrado em 7,7 - vai apontar para baixo e ser cortado)
    // S4: Validação de limites (o cone não vai "vazar" para linha 10, 11)
    int cone_l = 7, cone_c = 7;
    sobreporHabilidade(tabuleiro, matrizCone, cone_l, cone_c);

    printf("Habilidades sobrepostas no tabuleiro.\n");

    // --- 5. Exibição Final (R5) ---
    exibirTabuleiroFinal(tabuleiro);

    return 0; // Termina o programa com sucesso
}