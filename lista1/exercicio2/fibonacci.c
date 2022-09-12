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
}pilhaDinamica;                    //cria a estrutura da pilha

void init(pilhaDinamica *p){
    p->topo = NULL;                      //inicializa a pilha
    p->qntd = 0;
}

int size(pilhaDinamica p){               //retorna o tamanho da pilha
    return (p.qntd);
}

bool stackEmpty(pilhaDinamica p){       //verifica se a pilha está vazia
    if(p.qntd == 0) {
    return(true);
    }
}

void push(pilhaDinamica *p, int ch){
    no* aux=NULL;
    aux = (no*)malloc(sizeof(no));           //empilha um elemento
    aux->no=ch;
    aux->prox=p->topo;
    p->topo=aux;
    p->qntd++;
}

void pop(pilhaDinamica *p){                 //desempilha um elemento
    no *aux;
    aux = p->topo;
    p->topo = p->topo->prox;
    free(aux);
    p->qntd--;
}

void destroy(pilhaDinamica *p){          //destroi a pilha
    while (p->qntd != 0){
        pop(p);
    }
}

void show(pilhaDinamica p){
    no *aux;
    aux = p.topo;
    while(aux != NULL){
        printf("%d ", aux->no);
        aux = aux->prox;
    }                             //mostra os elementos da pilha
}

int fibonacci(int n){               //função que calcula o fibonacci
    if(n== 1){
        return 0;
    }
    if(n==2){
        return 1;
    }
    return fibonacci(n-1) + fibonacci(n-2);
}

int main(void){
    pilhaDinamica stack;
    init(&stack);
    int n;

    printf("Digite um valor para a sequencia de fibonacci ente 5 e 20:");
    scanf("%d", &n);
    if (n < 5 || n > 20){                   //verifica se o valor está entre 5 e 20
        printf("Valor invalido");
        return 0;
    }
    for(int i = 1; i <= n; i++){                //empilha os valores da sequencia
        push(&stack, fibonacci(i));
    }
    printf("A quantidade será %d\n", size(stack));
    show(stack);               //mostra os valores da pilha
    printf("\n");
    return 0;
}