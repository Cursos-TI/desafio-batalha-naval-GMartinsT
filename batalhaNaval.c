#include <stdio.h>

int main() {
    // Definir tabuleiro 10x10 inicializado com zeros
    int tabuleiro[10][10];
    for (int linha = 0; linha < 10; linha++) {
        for (int coluna = 0; coluna < 10; coluna++) {
            tabuleiro[linha][coluna] = 0;
        }
    }

    // Definir navios de tamanho 3
    const int tamanhoNavio = 3;
    // Coordenadas iniciais (linha, coluna)
    const int navioHorizontalLinha = 2;
    const int navioHorizontalColuna = 4;

    const int navioVerticalLinha = 5;
    const int navioVerticalColuna = 7;

    const int navioDiagonal1Linha = 0;
    const int navioDiagonal1Coluna = 0;

    const int navioDiagonal2Linha = 9;
    const int navioDiagonal2Coluna = 2;


    // Validar limites e sobreposição
    // Validar se o navio cabe no tabuleiro na horizontal
    if (navioHorizontalColuna + tamanhoNavio - 1 >= 10) {
        printf("Erro: navio horizontal ultrapassa limite do tabuleiro.\n");
        return 1;
    }
    // Validar se o navio cabe no tabuleiro na vertical
    if (navioVerticalLinha + tamanhoNavio - 1 >= 10) {
        printf("Erro: navio vertical ultrapassa limite do tabuleiro.\n");
        return 1;
    }
    // Diagonal principal (d1): linha+i, coluna+i
    if (navioDiagonal1Linha + tamanhoNavio - 1 >= 10 || navioDiagonal1Coluna + tamanhoNavio - 1 >= 10) {
        printf("Erro: navio diagonal principal ultrapassa limite do tabuleiro.\n"); return 1;
    }
    // Diagonal secundária (d2): linha-i, coluna-i
    if (navioDiagonal2Linha - (tamanhoNavio - 1) < 0 || navioDiagonal2Coluna - (tamanhoNavio - 1) < 0) {
        printf("Erro: navio diagonal secundaria ultrapassa limite do tabuleiro.\n"); return 1;
    }

    // Validar sobreposição entre os dois navios
    for (int i = 0; i < tamanhoNavio; i++) {
        // Navio horizontal
        int linH = navioHorizontalLinha;
        int colH = navioHorizontalColuna + i;
        // Navio vertical
        int linV = navioVerticalLinha + i;
        int colV = navioVerticalColuna;
        // Navio diagonal 1
        int linD1 = navioDiagonal1Linha + i;
        int colD1 = navioDiagonal1Coluna + i;
        // Navio diagonal 2
        int linD2 =  navioDiagonal2Linha - i;
        int colD2 = navioDiagonal2Coluna - i;

        // Pares de coordenadas
        int coordenadas[4][2] = {{linH, colH}, {linV, colV}, {linD1, colD1}, {linD2, colD2}};

        // Comparar cada par para verificar sobreposições
        for (int a = 0; a < 4; a++) {
            for (int b = a + 1; b < 4; b++) {
                if (coordenadas[a][0] == coordenadas[b][0] && coordenadas[a][1] == coordenadas[b][1]) {
                    printf("Erro: navios se sobrepoem na posicao (%d,%d).\n", coordenadas[a][0], coordenadas[a][1]);
                    return 1;
                }
            }
        }
    }
    
    // Posicionar navios
    for (int i = 0; i < tamanhoNavio; i++) {
        // Horizontal
        tabuleiro[navioHorizontalLinha][navioHorizontalColuna + i] = 3;
        // Vertical
        tabuleiro[navioVerticalLinha + i][navioVerticalColuna] = 3;
        // Diagonal 1
        tabuleiro[navioDiagonal1Linha + i][navioDiagonal1Coluna + i] = 3;
        // Diagonal 2
        tabuleiro[navioDiagonal2Linha - i][navioDiagonal2Coluna - i] = 3;
    }


    // Definir as matrizes de habilidade (tamanho 5x5) com 1=efeito, 0=sem efeito
    // Cone
    int cone[5][5] = {
        {0,0,1,0,0},
        {0,1,1,1,0},
        {1,1,1,1,1},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };
    // Cruz
    int cruz[5][5] = {
        {0,0,1,0,0},
        {0,0,1,0,0},
        {1,1,1,1,1},
        {0,0,1,0,0},
        {0,0,1,0,0}
    };
    // Octaedro
    int octaedro[5][5] = {
        {0,0,1,0,0},
        {0,1,1,1,0},
        {1,1,1,1,1},
        {0,1,1,1,0},
        {0,0,1,0,0}
    };

    // Pontos de origem no tabuleiro para cada habilidade
    const int origemConeLinha      = 1;
    const int origemConeColuna     = 2;
    const int origemCruzLinha      = 4;
    const int origemCruzColuna     = 5;
    const int origemOctaedroLinha  = 7;
    const int origemOctaedroColuna = 3;

    // Sobrepor cada habilidade (marca 5) usando loops aninhados e condicionais
    // Cone
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (cone[i][j] == 1) {
                // Subtrai 2 para alinhar o centro (índice 2,2 na matriz) com a origem no tabuleiro
                int ti = origemConeLinha - 2 + i; // Linha no tabuleiro
                int tj = origemConeColuna - 2 + j; // Coluna no tabuleiro
                if (ti >= 0 && ti < 10 && tj >= 0 && tj < 10) {
                    tabuleiro[ti][tj] = 5; // Marca a área de efeito da habilidade com o valor 5
                }
            }
        }
    }
    // Cruz
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (cruz[i][j] == 1) {
                int ti = origemCruzLinha - 2 + i;
                int tj = origemCruzColuna - 2 + j;
                if (ti >= 0 && ti < 10 && tj >= 0 && tj < 10) {
                    tabuleiro[ti][tj] = 5;
                }
            }
        }
    }
    // Octaedro
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (octaedro[i][j] == 1) {
                int ti = origemOctaedroLinha - 2 + i;
                int tj = origemOctaedroColuna - 2 + j;
                if (ti >= 0 && ti < 10 && tj >= 0 && tj < 10) {
                    tabuleiro[ti][tj] = 5;
                }
            }
        }
    }

    // Exibir o tabuleiro final (0=água, 3=navio, 5=habilidade)
    printf("\nTabuleiro com Habilidades (0=agua,3=navio,5=efeito):\n");
    for (int linha = 0; linha < 10; linha++) {
        for (int coluna = 0; coluna < 10; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }

    return 0;
}
