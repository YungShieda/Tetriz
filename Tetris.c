#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[16];
    int pontuacoes[12];
    int pontuacaoFinal;
    int classificacao;
} Jogador;

int compararJogadores(const void *a, const void *b) {
    const Jogador *jogadorA = (const Jogador *)a;
    const Jogador *jogadorB = (const Jogador *)b;

    if (jogadorA->pontuacaoFinal != jogadorB->pontuacaoFinal) {
        return jogadorB->pontuacaoFinal - jogadorA->pontuacaoFinal;
    }

    return strcmp(jogadorA->nome, jogadorB->nome);
}

int main() {
    int teste = 1;
    int numJogadores;

    while (1) {
        printf("Digite o número de jogadores ou pressione 0 para sair: ");
        scanf("%d", &numJogadores);

        if (numJogadores == 0) {
            break;
        }

        Jogador *jogadores = (Jogador *)malloc(numJogadores * sizeof(Jogador));

        for (int i = 0; i < numJogadores; i++) {
            printf("Digite o nome do jogador: ");
            scanf("%s", jogadores[i].nome);
            jogadores[i].pontuacaoFinal = 0;

            printf("Digite as 12 pontuações do jogador separadas por espaço: ");
            for (int j = 0; j < 12; j++) {
                if (scanf("%d", &jogadores[i].pontuacoes[j]) != 1) {
                    fprintf(stderr, "Erro na leitura das pontuações.\n");
                    exit(EXIT_FAILURE);
                }
            }

            qsort(jogadores[i].pontuacoes, 12, sizeof(int), compararJogadores);

            for (int k = 1; k < 11; k++) {
                jogadores[i].pontuacaoFinal += jogadores[i].pontuacoes[k];
            }
        }

        qsort(jogadores, numJogadores, sizeof(Jogador), compararJogadores);

        printf("Teste %d\n", teste++);
        int posicao = 1;
        for (int i = 0; i < numJogadores; i++) {
            if (i > 0 && jogadores[i].pontuacaoFinal != jogadores[i - 1].pontuacaoFinal) {
                posicao = i + 1;
            }
            printf("%d %d %s\n", posicao, jogadores[i].pontuacaoFinal, jogadores[i].nome);
            posicao++;
        }

        free(jogadores);

        printf("\n");
    }

    return 0;
}
