#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

typedef struct {
    char nome[100];
    int producaoPadraoHora;
    int producaoTotal;
} Produto;

Produto criarProduto(const char *nome, int producaoPadraoHora, int producaoTotal) {
    Produto p;
    snprintf(p.nome, sizeof(p.nome), "%s", nome);
    p.producaoPadraoHora = producaoPadraoHora;
    p.producaoTotal = producaoTotal;
    return p;
}

int calcularDiferencaProducao(int producaoEsperada, int producaoReal) {
    return producaoEsperada - producaoReal;
}

int calcularMinutosDePerda(int producaoPadraoHora, int diferencaProducao) {
    return (int)((60.0 / producaoPadraoHora) * diferencaProducao);
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int metodoDeCalculo;
    char continuarMetodo;

    do {
        system("cls");
        printf("===== Menu =====\n");
        printf("1. Método de Cálculo 1\n");
        printf("2. Método de Cálculo 2\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &metodoDeCalculo);

        if (metodoDeCalculo == 1) {
            char continuar;
            do {
                char nome[100];
                int producaoPadraoHora, producaoEsperada, producaoReal;

                system(CLEAR_SCREEN);
                printf("\nNome do produto: ");
                getchar();
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Produção padrão por hora: ");
                scanf("%d", &producaoPadraoHora);

                producaoEsperada = producaoPadraoHora * 7;
                printf("Produção total esperada no dia: %d\n", producaoEsperada);

                printf("Produção total real no dia: ");
                scanf("%d", &producaoReal);

                Produto produto = criarProduto(nome, producaoPadraoHora, producaoEsperada);
                int diferencaProducao = calcularDiferencaProducao(producaoEsperada, producaoReal);
                int minutosPerda = calcularMinutosDePerda(produto.producaoPadraoHora, diferencaProducao);

                printf("\n--- Resultados ---\n");
                printf("Produto: %s\n", produto.nome);
                printf("Perda de produção: %d unidades\n", diferencaProducao);
                printf("Minutos de perda de produção: %d minutos\n", minutosPerda);

                printf("\nDeseja adicionar outro produto com este método? (s/n): ");
                scanf(" %c", &continuar);

            } while (continuar == 's' || continuar == 'S');

        } else if (metodoDeCalculo == 2) {
            do {
                char nome1[100], nome2[100];
                int producaoPadraoHora, producaoPadraoHora2, producaoEsperada, producaoEsperada2;
                int producaoReal, producaoReal2, i, somaProducao = 0, horasUsadas = 0, qtdProducao[7];

                system("cls");
                printf("\nNome do produto 1: ");
                getchar();
                fgets(nome1, sizeof(nome1), stdin);
                nome1[strcspn(nome1, "\n")] = '\0';

                printf("\nNome do produto 2: ");
                fgets(nome2, sizeof(nome2), stdin);
                nome2[strcspn(nome2, "\n")] = '\0';

                printf("Produção padrão por hora para o produto 1: ");
                scanf("%d", &producaoPadraoHora);

                printf("Produção padrão por hora para o produto 2: ");
                scanf("%d", &producaoPadraoHora2);

                printf("Produção total real no dia do produto 1: ");
                scanf("%d", &producaoReal);

                printf("Produção total real no dia do produto 2: ");
                scanf("%d", &producaoReal2);

                for(i = 0; i < 7 && somaProducao <= producaoReal; i++){
                    printf("Digite a quantidade produzida na hora %d (Produto 1): ", i + 1);
                    scanf("%d", &qtdProducao[i]);

                    somaProducao += qtdProducao[i];  
                    horasUsadas++; 
                }

                producaoEsperada = horasUsadas * producaoPadraoHora;
                producaoEsperada2 = producaoPadraoHora2 * (7 - horasUsadas);

                Produto produto1 = criarProduto(nome1, producaoPadraoHora, producaoEsperada);
                int diferencaProducao = calcularDiferencaProducao(producaoEsperada, producaoReal);
                int minutosPerda = calcularMinutosDePerda(produto1.producaoPadraoHora, diferencaProducao);

                Produto produto2 = criarProduto(nome2, producaoPadraoHora2, producaoEsperada2);
                int diferencaProducao2 = calcularDiferencaProducao(producaoEsperada2, producaoReal2);
                int minutosPerda2 = calcularMinutosDePerda(produto2.producaoPadraoHora, diferencaProducao2);

                printf("\n--- Resultados ---\n");
                printf("Produto 1: %s\n", produto1.nome);
                printf("Perda de produção: %d unidades\n", diferencaProducao);
                printf("Minutos de perda de produção: %d minutos\n", minutosPerda);

                printf("Produto 2: %s\n", produto2.nome);
                printf("Perda de produção: %d unidades\n", diferencaProducao2);
                printf("Minutos de perda de produção: %d minutos\n", minutosPerda2);

                printf("\nDeseja continuar com esse método? (s/n): ");
                scanf(" %c", &continuarMetodo);

            } while (continuarMetodo == 's' || continuarMetodo == 'S');
        }

    } while (metodoDeCalculo != 3);

    printf("Programa encerrado.\n");
    return 0;
}
