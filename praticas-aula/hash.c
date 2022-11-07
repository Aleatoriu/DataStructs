#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAM 13

typedef struct noHash{
    int chave;
    struct noHash* prox;
}NoHash;

typedef struct hash{
    NoHash* tabela[TAM];
}Hash;

NoHash* inicializaNoHash(int chave){
    NoHash* no = (NoHash*) malloc(sizeof(NoHash));
    no->chave = chave;
    no->prox = NULL;
    return no;
}

Hash* inicializaHash(){
    Hash* hash = (Hash*) malloc(sizeof(Hash));
    for(int i=0; i<TAM; i++){
        hash->tabela[i] = NULL;
    }
    return hash;
}

int funcaoHash(int chave){
    return chave%TAM;
}

void insereHash(Hash* hash, int chave){
    int pos = funcaoHash(chave);
    NoHash* no = inicializaNoHash(chave);
    if(hash->tabela[pos] == NULL){
        hash->tabela[pos] = no;
    }else{
        NoHash* aux = hash->tabela[pos];
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
}

void imprimeHash(Hash* hash){
    for(int i=0; i<TAM; i++){
        printf("Posicao %d: ", i);
        NoHash* aux = hash->tabela[i];
        while(aux != NULL){
            printf("%d ", aux->chave);
            aux = aux->prox;
        }
        printf("\n");
    }
}

void removeHash(Hash* hash, int chave){
    int pos = funcaoHash(chave);
    NoHash* aux = hash->tabela[pos];
    NoHash* ant = NULL;
    while(aux != NULL && aux->chave != chave){
        ant = aux;
        aux = aux->prox;
    }
    if(aux == NULL){
        printf("Chave nao encontrada!\n");
    }else{
        if(ant == NULL){
            hash->tabela[pos] = aux->prox;
        }else{
            ant->prox = aux->prox;
        }
        free(aux);
    }
}

void buscaHash(Hash* hash, int chave){
    int pos = funcaoHash(chave);
    NoHash* aux = hash->tabela[pos];
    while(aux != NULL && aux->chave != chave){
        aux = aux->prox;
    }
    if(aux == NULL){
        printf("Chave nao encontrada!\n");
    }else{
        printf("Chave encontrada!\n");
    }
}

int main(){
    Hash* hash = inicializaHash();
    insereHash(hash, 100);
    insereHash(hash, 40);
    insereHash(hash, 6);
    insereHash(hash, 0);
    insereHash(hash, 17);
    insereHash(hash, 15);
    insereHash(hash, 4);
    insereHash(hash, 25);
    insereHash(hash, 63);
    insereHash(hash, 48);
    insereHash(hash, 96);
    insereHash(hash, 2);

    imprimeHash(hash);

    printf("Removendo 15...\n\n\n\n");
    removeHash(hash, 15);
    buscaHash(hash, 15);

    imprimeHash(hash);
    return 0;
    

}