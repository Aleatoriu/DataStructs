#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct no {
    int valor;
    struct no *prox;
} No;

typedef struct filaDinamica_st {
    No *inicio;
    No *fim;
    int qtd;
} FilaDinamica_t;

void init(FilaDinamica_t *fila){
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->qtd = 0;
}

bool isEmpty(FilaDinamica_t *fila){
    if(fila->qtd == 0){
        return true;
    }else{
        return false;
    }
}

void push(FilaDinamica_t *fila, int valor){
    No *novo = (No *) malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;
    if(isEmpty(fila)){
        fila->inicio = novo;
        fila->fim = novo;
    }else{
        fila->fim->prox = novo;
        fila->fim = novo;
    }
    fila->qtd++;
}

void pop(FilaDinamica_t *fila){
    if(isEmpty(fila)){
        printf("Fila vazia!");
    }else{
        No *aux = fila->inicio;
        fila->inicio = fila->inicio->prox;
        free(aux);
        fila->qtd--;
    }
}

void show(FilaDinamica_t *fila){
    No *aux = fila->inicio;
    while(aux != NULL){
        printf("%d ", aux->valor);
        aux = aux->prox;
    }
}


int main(void){

    FilaDinamica_t filazinha;
    init(&filazinha);
    while(1){
        
        push(&filazinha, 0);
        push(&filazinha, 1);
        push(&filazinha, 1);
        push(&filazinha, 0);
        push(&filazinha, 0);
        

        show(&filazinha);
    }

    return 0;

}