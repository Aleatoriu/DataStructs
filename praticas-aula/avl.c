#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


typedef struct  noArvore
{
    int chave;
    struct  noArvore* dir;    
    struct  noArvore* esq;  
    int alt;
}NoArvore;


NoArvore* inicializaArvore(){
    return NULL;
}

bool estaVazia(NoArvore** no){
    return((*no)==NULL);
}

int maxAltFilho(NoArvore **no){
    if((*no)->esq == NULL && (*no)->dir == NULL) return (-1);
    else if((*no)->esq == NULL) return ((*no)->dir->alt);
    else if((*no)->dir == NULL) return ((*no)->esq->alt);
    return((*no)->dir->alt > (*no)->esq->alt ? (*no)->dir->alt : (*no)->esq->alt);
}

void rotacaoEsq(NoArvore **no){
    NoArvore *aux=NULL;
    aux = (*no)->dir;
    (*no)->dir = aux->esq;
    aux->esq = (*no);
    (*no)=aux;
    (*no)->esq->alt = maxAltFilho(&(*no)->esq) + 1;
   // (*no)->dir->alt = maxAltFilho(&(*no)->dir) + 1;
    (*no)->alt = maxAltFilho(no) + 1;
}

void rotacaoDir(NoArvore **no){
    NoArvore *aux = (*no)->esq;
    (*no)->esq=aux->dir;
    aux->dir=(*no);
    (*no)=aux;
   // (*no)->esq->alt = maxAltFilho(&(*no)->esq) + 1;
    (*no)->dir->alt = maxAltFilho(&(*no)->dir) + 1;
    (*no)->alt = maxAltFilho(no) + 1;
}

int altura(NoArvore **no){
    if((*no)==NULL) return -1;
    return ((*no)->alt);
}

void insereArvore(NoArvore **no, int chave){
   if((*no)==NULL){
        (*no)=(NoArvore*) malloc(sizeof(NoArvore));
        (*no)->chave=chave;
        (*no)->dir=(*no)->esq=NULL;
        (*no)->alt=0;
        return;
    }
   if((*no)->chave == chave){
        printf("\nElemento repetido");
        return;
    }
    (*no)->chave > chave ? insereArvore(&((*no)->esq),chave): insereArvore(&((*no)->dir), chave);
    (*no)->alt= maxAltFilho(no) + 1;
    
    if(altura(&(*no)->dir) - altura(&(*no)->esq) == 2){
        if(altura(&(*no)->dir->dir) - altura(&(*no)->dir->esq) < 0)  rotacaoDir(&(*no)->dir);
        rotacaoEsq(no);
    }
    else if(altura(&(*no)->dir) - altura(&(*no)->esq) == -2){
         if(altura(&(*no)->esq->dir) - altura(&(*no)->esq->esq) > 0)  rotacaoEsq(&(*no)->esq);
        rotacaoDir(no);
    }
}

void imprimeEmOrdem(NoArvore **no){
    if(*no==NULL) return;
    imprimeEmOrdem(&((*no)->esq));
    printf("\n--> %d [h=%d]", (*no)->chave, (*no)->alt);
    imprimeEmOrdem(&((*no)->dir));
}

void imprimePreOrdem(NoArvore **no){
    if(*no==NULL) return;
    printf("\n--> %d [h=%d]", (*no)->chave, (*no)->alt);
    imprimePreOrdem(&((*no)->esq));    
    imprimePreOrdem(&((*no)->dir));
}

void destroiArvore(NoArvore **no){
    if((*no)==NULL) return;
    destroiArvore(&((*no)->esq)); 
    destroiArvore(&((*no)->dir));
    free(*no);
    (*no)=NULL;
}

void excluiElem(NoArvore **no, int chave){
    if(*no==NULL){
        printf("\n\n------------\n\n\t Chave nao encontrada \n\n----------------\n");
        return;
    }
    if((*no)->chave==chave){
        if((*no)->esq==NULL && (*no)->dir==NULL){
            free(*no);
            *no=NULL;
        }
        else if((*no)->esq==NULL){
            NoArvore *aux=*no;
            *no=(*no)->dir;
            free(aux);
        }
        else if((*no)->dir==NULL){
            NoArvore *aux=*no;
            *no=(*no)->esq;
            free(aux);
        }
        else{ //arrumar
           NoArvore *aux=(*no);
           NoArvore *anterior=(*no);
           *no=(*no)->esq;
           while((*no)->dir!=NULL){
                anterior=(*no); 
                *no=(*no)->dir;                
           }
           (*no)->dir=aux->dir;
           anterior->dir=(*no)->esq;
           if(aux!=anterior) (*no)->esq=aux->esq;
           free(aux);           
        }
        return;
    }
    if((*no)->chave > chave) excluiElem(&(*no)->esq, chave);
    else excluiElem(&(*no)->dir, chave);
    (*no)->alt = maxAltFilho(no) + 1;
     if(altura(&(*no)->dir) - altura(&(*no)->esq) == 2){
        if(altura(&(*no)->dir->dir) - altura(&(*no)->dir->esq) < 0)  rotacaoDir(&(*no)->dir);
        rotacaoEsq(no);
    }
    else if(altura(&(*no)->dir) - altura(&(*no)->esq) == -2){
         if(altura(&(*no)->esq->dir) - altura(&(*no)->esq->esq) > 0)  rotacaoEsq(&(*no)->esq);
        rotacaoDir(no);
    }
}

int main(void){

    NoArvore *raiz = inicializaArvore();

    insereArvore(&raiz, 10);  
    insereArvore(&raiz, 15);
    insereArvore(&raiz, 13);
    insereArvore(&raiz, 17);
    insereArvore(&raiz, 16);
    insereArvore(&raiz, 12);
    insereArvore(&raiz, 14); 
    insereArvore(&raiz, 5);
    
    printf("\n\n-----------------INICIO------------------\n\n");
    imprimePreOrdem(&raiz);
    printf("\n\n-----------------FIM------------------\n\n");


    
  //  insereArvore(&raiz, 3);
 //   insereArvore(&raiz, 7);
  //  insereArvore(&raiz, 6);
 //   insereArvore(&raiz, 2);
  //  insereArvore(&raiz, 4);

  //  insereArvore(&raiz, 19);
  //  insereArvore(&raiz, 20);
/*
    printf("\n\n-----------------***INICIO***------------------\n\n");
    imprimeEmOrdem(&raiz);
    printf("\n\n-----------------FIM------------------\n\n");
*/
    excluiElem(&raiz, 17);

    printf("\n\n-----------------Inicio------------------\n\n");
    imprimePreOrdem(&raiz);
    printf("\n\n-----------------Fim------------------\n\n");
    
    destroiArvore(&raiz);
}