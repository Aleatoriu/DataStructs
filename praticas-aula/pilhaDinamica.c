#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct no_st{
    int no;
    struct no_st* prox;
}no;

typedef struct pilhaDinamica_st{
    no *topo;
    int qntd;
}pilhaDinamica;


void iniciarPilha (pilhaDinamica *p){
    p->topo == NULL;
    p->qntd = 0;
}

int tamanhoPilha(pilhaDinamica p){
    return (p.qntd);
}

bool estaVazia (pilhaDinamica p){
    if(p.qntd == 0) return(true);
}

void inserirPilha(pilhaDinamica *p, int ch){
    no* aux=NULL;
    aux = (no*)malloc(sizeof(no));
    aux->no=ch;
    aux->prox=p->topo;
    p->topo=aux;
    p->qntd++;
}

void removerPilha(pilhaDinamica *p){
    no *aux;
    aux = p->topo;
    p->topo = p->topo->prox;
    free(aux);
    p->qntd--;
}

void destruir(pilhaDinamica *p){
    while (p->qntd != 0){
        removerPilha(p);
    }
}



int main(void){
    pilhaDinamica stack;

    iniciarPilha(&stack);    
    

    inserirPilha(&stack, 5);
    inserirPilha(&stack, 2);
    printf("A quantidade será %d\n", tamanhoPilha(stack));
    removerPilha(&stack);
    destruir(&stack);
    if(estaVazia(stack)== false) printf("está vazia");
    else printf("não é vazia\n");
    
    return EXIT_SUCCESS;
}