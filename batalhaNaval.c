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
    // Validar sobreposição entre os dois navios
    for (int i = 0; i < tamanhoNavio; i++) {
        int linH = navioHorizontalLinha;
        int colH = navioHorizontalColuna + i;
        int linV = navioVerticalLinha + i;
        int colV = navioVerticalColuna;
        if (linH == linV && colH == colV) {
            printf("Erro: navios estao se sobrepondo na posicao (%d,%d).\n", linH, colH);
            return 1;
        }
    }

    // Posicionar navio horizontal
    for (int i = 0; i < tamanhoNavio; i++) {
        tabuleiro[navioHorizontalLinha][navioHorizontalColuna + i] = 3;
    }
    // Posicionar navio vertical
    for (int i = 0; i < tamanhoNavio; i++) {
        tabuleiro[navioVerticalLinha + i][navioVerticalColuna] = 3;
    }

    // Exibir tabuleiro
    printf("\nTabuleiro 10x10 (0=agua, 3=navio):\n");
    for (int linha = 0; linha < 10; linha++) {
        for (int coluna = 0; coluna < 10; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }

    return 0;
}
