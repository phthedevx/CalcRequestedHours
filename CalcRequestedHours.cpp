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
    
    char nome[100];
    int producaoPadraoHora, producaoEsperada, producaoReal;
    char continuar;
    
    do {
        system(CLEAR_SCREEN);
        printf("\nNome do produto: ");
        getchar(); // Limpa buffer
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
        
        printf("\nDeseja adicionar outro produto? (s/n): ");
        scanf(" %c", &continuar);
        
    } while (continuar == 's' || continuar == 'S');
    
    return 0;
}
