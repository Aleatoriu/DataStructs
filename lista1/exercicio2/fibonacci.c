#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct no_st{
    int no;
    struct no_st* prox;
}no;

typedef struct pilhaDinamica_st{
    no *topo;
    int qntd;
}pilhaDinamica;

void init(pilhaDinamica *p){
    p->topo = NULL;
    p->qntd = 0;
}

int size(pilhaDinamica p){
    return (p.qntd);
}

bool stackEmpty(pilhaDinamica p){
    if(p.qntd == 0) {
    return(true);
    }
}

void push(pilhaDinamica *p, int ch){
    no* aux=NULL;
    aux = (no*)malloc(sizeof(no));
    aux->no=ch;
    aux->prox=p->topo;
    p->topo=aux;
    p->qntd++;
}

void pop(pilhaDinamica *p){
    no *aux;
    aux = p->topo;
    p->topo = p->topo->prox;
    free(aux);
    p->qntd--;
}

void destroy(pilhaDinamica *p){
    while (p->qntd != 0){
        pop(p);
    }
}

int fibonacci(int n){
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
    if (n < 5 || n > 20){
        printf("Valor invalido");
        return 0;
    }
    for(int i = 1; i <= n; i++){
        push(&stack, fibonacci(i));
    }
    printf("A quantidade será %d\n", size(stack));
    for(int i = 1; i <= n; i++){
        printf("%d ", stack.topo->no);
        pop(&stack);
    }
    printf("\n");
    return 0;
}