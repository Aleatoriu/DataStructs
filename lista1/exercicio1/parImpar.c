
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 10

typedef struct numero_st{
    int numero;
}Numero;                //Estrutura que armazena o numero

typedef struct pilha{
    int top;
    Numero numero[MAX];    
}pilha;                //Estrutura que armazena a pilha


bool overflow(pilha *p){
    if(p->top == MAX){
        return true;
    }
    else{
        return false;
    }
}                    //Função que verifica se a pilha está cheia

void init(pilha *p){
    p->top = 0;
}                  //Função que inicializa a pilha

void push(pilha *p, Numero n){
    if(overflow(p)==1){
        printf("A pilha está cheia!");
        return;
    }
    p->numero[p->top] = n;
    p->top++;
}            //Função que empilha um numero

void pop(pilha *p){
    p->top--;
}           //Função que desempilha um numero

void show(pilha p){
    for(int i = 0;i > p.top; i++){
        printf("\n \n pilha [%d] = %d",i,p.numero[i].numero);
    }
}           //Função que mostra a pilha

void showArq(pilha *p, char *nomeArq){
    FILE *arq;
    arq = fopen(nomeArq,"w");
    for(int i = 0;i < p->top; i++){
        fprintf(arq, "%d ", p->numero[i].numero);
    }
    fclose(arq);
}               //Função que mostra a pilha em um arquivo

int main(int argc, char *argv[])
{
    pilha pilhaPar, pilhaImpar;
    Numero n;
    FILE *arq;
    init(&pilhaPar);
    init(&pilhaImpar);

    arq = fopen(argv[1],"r");
    if(arq == NULL){
        printf("Erro ao abrir o arquivo!");
        return 0;
    }
    for(int i = 0; i < MAX; i++){
        fscanf(arq,"%d",&n.numero);
        if(n.numero % 2 == 0){
            push(&pilhaPar,n);
        }
        else{
            push(&pilhaImpar,n);
        }
    }                
    fclose(arq);

    showArq(&pilhaPar,argv[2]);             //Mostra a pilha par em um arquivo
    showArq(&pilhaImpar,argv[3]);           //Mostra a pilha impar em um arquivo
    return 0;
}
