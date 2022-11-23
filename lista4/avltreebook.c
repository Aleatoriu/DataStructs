#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct avl{
    int chave;
    int altura;
    struct avl *esq;
    struct avl *dir;
}avl;

int max(int a, int b){
    return (a > b) ? a : b;
}

int altura(avl *a){
    if(a == NULL) return 0;
    return a->altura;
}

avl *criaNo(int chave){
    avl *novo = (avl*)malloc(sizeof(avl));
    novo->chave = chave;
    novo->altura = 1;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

avl *rotacaoEsq(avl *a){
    avl *b = a->dir;
    avl *t2 = b->esq;
    b->esq = a;
    a->dir = t2;
    a->altura = max(altura(a->esq), altura(a->dir)) + 1;
    b->altura = max(altura(b->esq), altura(b->dir)) + 1;
    return b;
}

avl *rotacaoDir(avl *a){
    avl *b = a->esq;
    avl *t2 = b->dir;
    b->dir = a;
    a->esq = t2;
    a->altura = max(altura(a->esq), altura(a->dir)) + 1;
    b->altura = max(altura(b->esq), altura(b->dir)) + 1;
    return b;
}


int fatorBalanceamento(avl *a){
    if(a == NULL) return 0;
    return altura(a->esq) - altura(a->dir);
}

avl *insere(avl *a, int chave){
    if(a == NULL) return criaNo(chave);
    if(chave < a->chave) a->esq = insere(a->esq, chave);
    else if(chave > a->chave) a->dir = insere(a->dir, chave); 
    else return a;
    a->altura = 1 + max(altura(a->esq), altura(a->dir));
    int fb = fatorBalanceamento(a);
    if(fb > 1 && chave < a->esq->chave) return rotacaoDir(a);
    if(fb < -1 && chave > a->dir->chave) return rotacaoEsq(a);
    if(fb > 1 && chave > a->esq->chave){
        a->esq = rotacaoEsq(a->esq);
        return rotacaoDir(a);
    }
    if(fb < -1 && chave < a->dir->chave){
        a->dir = rotacaoDir(a->dir);
        return rotacaoEsq(a);
    }
    return a;
}

void preOrdem(avl *a){
    if(a != NULL){
        printf("%d ", a->chave);
        preOrdem(a->esq);
        preOrdem(a->dir);
    }
}

void emOrdem(avl *a){
    if(a != NULL){
        emOrdem(a->esq);
        printf("%d ", a->chave);
        emOrdem(a->dir);
    }
}

void posOrdem(avl *a){
    if(a != NULL){
        posOrdem(a->esq);
        posOrdem(a->dir);
        printf("%d ", a->chave);
    }
}

int main(){
    avl *a = NULL;
    int n, chave;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &chave);
        a = insere(a, chave);
    }
    preOrdem(a);
    printf("
");
    emOrdem(a);
    printf("  ");
    

/*int main(void){
    FILE *arq;
    char temp1[23], temp2[23];
    arq = fopen("alou.xlsx", "r");
    while(!feof(arq)){
        fscanf(arq,"%s \t %s \n", temp1, temp2);
        printf("%s \t %s \n", temp1, temp2);
    }
}