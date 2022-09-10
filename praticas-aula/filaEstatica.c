#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct fila {
    int inicio;
    int fim;
    int qtd;
    int dados[MAX];
} Fila;

void inicializar(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
}

bool estaCheia(Fila *f) {
    return f->qtd == MAX;
}

bool estaVazia(Fila *f) {
    return f->qtd == 0;
}

bool inserir(Fila *f, int valor) {
    if (estaCheia(f)) {
        return false;
    }
    f->dados[f->fim] = valor;
    f->fim = (f->fim + 1) % MAX;
    f->qtd++;
    return true;
}

bool remover(Fila *f, int *valor) {
    if (estaVazia(f)) {
        return false;
    }
    *valor = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->qtd--;
    return true;
}

void imprimir(Fila *f) {
    int i;
    for (i = 0; i < f->qtd; i++) {
        printf("%d ", f->dados[(f->inicio + i) % MAX]);
    }
}

int main() {
    Fila f;
    inicializar(&f);
    int valor;
    int opcao;
    do {
        printf("\n\n1 - Inserir\n2 - Remover\n3 - Imprimir \n0 - Sair");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                if (inserir(&f, valor)) {
                    printf("Valor inserido com sucesso!");
                } else {
                    printf("Fila cheia!");
                }
                break;
            case 2:
                if (remover(&f, &valor)) {
                    printf("Valor removido: %d", valor);
                } else {
                    printf("Fila vazia!");
                }
                break;
            case 3:
                imprimir(&f);
                break;
        }
    } while (opcao != 0);
    return 0;
}


