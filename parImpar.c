
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 10

typedef struct numero_st{
    int numero;
}Numero;

typedef struct pilha{
    int top;
    Numero numero[MAX];    
}pilha;


bool overflow(pilha *p){
    if(p->top == MAX){
        return true;
    }
    else{
        return false;
    }
}

void init(pilha *p){
    p->top = 0;
}

void push(pilha *p, Numero n){
    if(overflow(p)==1){
        printf("A pilha está cheia!");
        return;
    }
    p->numero[p->top] = n;
    p->top++;
}

void pop(pilha *p){
    p->top--;
}

void show(pilha p){
    for(int i = 0;i < p.top; i++){
        printf("\n \n pilha [%d] = %d",i,p.numero[i].numero);
    }
}

int main(int argc, char const *argv[])
{
    pilha p;
    Numero n[10] = {10, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    init(&p);
    push(&p,n[0]);
    push(&p,n[1]);
    push(&p,n[2]);
    push(&p,n[3]);
    push(&p,n[4]);
    push(&p,n[5]);
    show(p);
    return 0;
}
