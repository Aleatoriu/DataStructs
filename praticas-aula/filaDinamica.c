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

void init(){
    FilaDinamica_t *fila = (FilaDinamica_t *) malloc(sizeof(FilaDinamica_t));
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->qtd = 0;
}

void isEmpty(FilaDinamica_t *fila){
    if(fila->qtd == 0){
        return true;
    }else{
        return false;
    }
}

void push(){
    int valor;
    printf("Digite o valor a ser inserido: ");
    scanf("%d", &valor);
    No *novo = (No *) malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;
    if(isEmpty(&fila)){
        fila->inicio = novo;
        fila->fim = novo;
    }else{
        fila->fim->prox = novo;
        fila->fim = novo;
    }
    fila->qtd++;
}

void pop(){
    if(isEmpty(&fila)){
        printf("Fila vazia!");
    }else{
        No *aux = fila->inicio;
        fila->inicio = fila->inicio->prox;
        free(aux);
        fila->qtd--;
    }
}





int main(){

    

}