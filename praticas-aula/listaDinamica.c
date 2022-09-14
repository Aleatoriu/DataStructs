#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct no_st{
    int no;
    struct no_st* prox;
}no;

typedef struct listaDinamica_st{
    no *inicio;
    int qntd;
}listaDinamica;

void init(listaDinamica *l){
    l->inicio == NULL;
    l->qntd = 0;
}

bool isEmpty(listaDinamica *l){
    if(l->qntd == 0){
        return(true);
    }else{
        return(false);
    }
}

int size(listaDinamica l){
    return (l.qntd);
}

void push(listaDinamica *l, int ch){
    no* novo = NULL;
    novo = (no*)malloc(sizeof(no));
    novo->no=ch;
    novo->prox=NULL;
    if(isEmpty(l) == true){
        l->inicio = novo;
    }else if (ch < l->inicio->no){
        novo->prox = l->inicio;
        l->inicio = novo;
    }else{
        no* aux = l->inicio;
        while (aux->prox != NULL && aux->prox->no < ch){
            aux = aux->prox;
        }
        novo->prox = aux->prox;
        aux->prox = novo;
    }
    l->qntd++;
}

void showList(listaDinamica *l){
    no* aux = l->inicio;
    int pos = 0;
    while (aux != NULL){
        printf("\n Pos %d -------> %d ",++pos,aux->no);
        aux = aux->prox;
    }
    printf("\n----------------------fim lista---------------- ");
}


void destroy(listaDinamica *l){
    while (l->qntd != 0){
        no *aux;
        aux = l->inicio;
        l->inicio = l->inicio->prox;
        free(aux);
        l->qntd--;
    }
}

bool pesquisar(listaDinamica l, int ch){
    no* aux = l.inicio;
    while (aux != NULL){
        if(aux->no == ch){
            return true;
        }
        aux = aux->prox;
    }
    return false;
}



int main(){
    listaDinamica lista;
    init(&lista);
    push(&lista, 7);
    push(&lista, 0);
    push(&lista, -1);
    push(&lista, 3);
    showList(&lista);
    if(pesquisar(lista, -2) == true){
        printf("\n encontrado");
    }else{
        printf("\n nao encontrado");
    }
    
    return EXIT_SUCCESS;
}