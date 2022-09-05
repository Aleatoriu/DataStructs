#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define N 2

typedef struct aluno_st{
    int RA;
    char nome[50];
}aluno_t;


typedef struct pilha_st{
    aluno_t alunos[N];
    int top;
}pilha_t;

void inicializaPilha(pilha_t *p){
    p->top = 0;
}

bool estaCheia(pilha_t *p){
    if(p->top == N){
        return true;
    }
    else{
        return false;
    }
}

void empilhar(pilha_t *p, aluno_t a){
    if(estaCheia(p)==1){
        printf("A pilha está cheia!");
        return;
    }
    p->alunos[p->top]= a;
    p->top++;
}

void imprimirPilha(pilha_t p){
    for(int i = 0;i < p.top; i++){
        printf("\n \n pilha [%d] = %d / %s",i,p.alunos[i].RA, p.alunos[i].nome);
    }
}

void removerPilha(pilha_t *p){;
    p->top--;
}

void topo(pilha_t *p){
    printf("\n \n ra do topo %d\n", p->alunos[p->top].RA);
}


int main(){
    pilha_t pilha;
    aluno_t a = {157, "alexandre"};

    inicializaPilha(&pilha);
    empilhar(&pilha, a);

    a.RA = 321;
    strcpy(a.nome, "roberto");
    empilhar(&pilha, a);

    topo(&pilha);

    removerPilha(&pilha);

    imprimirPilha(pilha);





    printf("\n\n topo=%d \n\n",pilha.top);

}   