#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct no_st{
    int no;
    struct no_st* prox;
}no;                          //cria a estrutura do nó

typedef struct pilhaDinamica_st{
    no *topo;
    int qntd;
}pilhaDinamica;                     //cria a estrutura da pilha

void init(pilhaDinamica *p){
    p->topo = NULL;
    p->qntd = 0;                        //inicializa a pilha
}

int size(pilhaDinamica p){
    return (p.qntd);
}

bool stackEmpty(pilhaDinamica p){
    if(p.qntd == 0) {                 //verifica se a pilha está vazia
    return(true);
    }
}

void push(pilhaDinamica *p, int ch){ //empilha um elemento
    no* aux=NULL;
    aux = (no*)malloc(sizeof(no));
    aux->no=ch;
    aux->prox=p->topo;                  
    p->topo=aux;
    p->qntd++;
}

void pop(pilhaDinamica *p){         //desempilha um elemento
    no *aux;
    aux = p->topo;
    p->topo = p->topo->prox;
    free(aux);
    p->qntd--;
}

void destroy(pilhaDinamica *p){ //destroi a pilha
    while (p->qntd != 0){
        pop(p);
    }
}

void show(pilhaDinamica p){     //mostra a pilha
    no *aux;
    aux = p.topo;
    while(aux != NULL){
        printf("%d ", aux->no);
        aux = aux->prox;
    }
}

int main(void){                  
    pilhaDinamica p;
    init(&p);
    int n;
    printf("Digite um numero: ");
    scanf("%d", &n);
    if(n <= 0){                     //verifica se o numero é positivo
        printf("Numero invalido");
    }
    else{ 
        while(n != 0){               //converte o numero para binario
            push(&p, n%2);           //e empilha os numeros
            n = n/2;                //na pilha
        }
    }
    show(p);                      //mostra a pilha
    return 0;
}