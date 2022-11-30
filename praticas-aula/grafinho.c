#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct grafoM{
    int **matriz;
    int vertices;
    int arestas;
    bool dirigido;
}grafoMatriz;

typedef struct no {
    int valor;
    struct no *prox;
} No;

typedef struct filaDinamica_st {
    No *inicio;
    No *fim;
    int qtd;
} FilaDinamica_t;

void init(FilaDinamica_t *fila){
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->qtd = 0;
}

bool isEmpty(FilaDinamica_t *fila){
    if(fila->qtd == 0){
        return true;
    }else{
        return false;
    }
}

void push(FilaDinamica_t *fila, int valor){
    No *novo = (No *) malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;
    if(isEmpty(fila)){
        fila->inicio = novo;
        fila->fim = novo;
    }else{
        fila->fim->prox = novo;
        fila->fim = novo;
    }
    fila->qtd++;
}

void pop(FilaDinamica_t *fila){
    if(isEmpty(fila)){
        printf("Fila vazia!");
    }else{
        No *aux = fila->inicio;
        fila->inicio = fila->inicio->prox;
        free(aux);
        fila->qtd--;
    }
}

void freeFila(FilaDinamica_t *fila){
    while(!isEmpty(fila)){
        pop(fila);
    }
}

void startG(grafoMatriz *g, int vertices, bool dirigido){
    g->arestas = 0;
    g->dirigido = dirigido;
    g->vertices = vertices;
    g->matriz = (int**)malloc(vertices*sizeof(int*));
    for(int i = 0; i < vertices; i++){
        g->matriz[i] = (int*)malloc(vertices*sizeof(int));
        for(int j = 0; j < vertices; j++){
            g->matriz[i][j] = 0;
        }
    }
}

void insertAresta(grafoMatriz *g, int v1, int v2){
    g->matriz[v1-1][v2-1] = 1;
        if(!g->dirigido){
        g->matriz[v2-1][v1-1] = 1;
    }
    g->arestas++;
}

void printMatrizG(grafoMatriz *g){
    for(int i = 0; i < g->vertices; i++){
        for(int j = 0; j < g->vertices; j++){
            printf("%d ", g->matriz[i][j]);
        }
        printf("\n");
    }
}

bool hasAresta(grafoMatriz *g, int v1, int v2){
    return(g->matriz[v1-1][v2-1] == 1);
}

void showArestas(grafoMatriz *g){
    for(int i = 0; i < g->vertices; i++){
        for(int j = 0; j < g->vertices; j++){
            if(g->matriz[i][j] == 1){
                if(!g->dirigido) printf(" \n < %d , %d > ", i+1, j+1);
                else printf(" \n ( %d , %d ) ", i+1, j+1);
            }
        }
    }
}

void removeAresta(grafoMatriz *g, int v1, int v2){
    g->matriz[v1-1][v2-1] = 0;
    if(!g->dirigido){
        g->matriz[v2-1][v1-1] = 0;
    }
    g->arestas--;
}


void visitaDFS(grafoMatriz *g, int visitado[], int i, int status){
    visitado[i] = status;
    printf("[%d] \t ", i+1);
    for(int j = 0; j < g->vertices; j++){
        if(g->matriz[i][j] == 1 && visitado[j] == 0){
            visitaDFS(g, visitado, j, 1);
        }
    }
    visitado[i] = 2;
}


void dfs(grafoMatriz *g, int ini){
    int visitado[g->vertices]; 
    ini--;  
    for(int i = 0; i < g->vertices; i++) visitado[i] = 0;
    visitado[ini] = 1;
    printf("\n [%d] \t ", ini+1);
    for(int i = 0; i < g->vertices; i++){
        if(g->matriz[ini][i] == 1 && visitado[i] == 0){
            visitaDFS(g, visitado, i, 1);
        }
    }
    for(int i = 0; i < g->vertices; i++){
        if(visitado[i] == 0){
            visitaDFS(g, visitado, i, 1);
        }
    }
}

void bfs(grafoMatriz *g, int ini){
    int visitado[g->vertices];
    FilaDinamica_t fila;
    init(&fila);
    ini--;
    bool visitados[g->vertices];
    for(int i = 0; i < g->vertices; i++) visitados[i] = false;
    visitados[ini] = true;
    push(&fila, ini);
    printf("\n [%d] \t ", ini+1);
    do{
        while(!isEmpty(&fila)){
            for(int i = 0; i < g->vertices; i++){
                if(g->matriz[fila.inicio->valor][i] == 1 && visitados[i] == false){
                    visitados[i] = true;
                    push(&fila, i);
                    printf("[%d] \t ", i+1);
                }
            }
            pop(&fila);
        }
        for(int i = 0; i < g->vertices; i++){
            if(visitados[i] == false){
                visitados[i] = true;
                push(&fila, i);
                printf("[%d] \t ", i+1);
                break;
            }
        }
    }while(!isEmpty(&fila));
    freeFila(&fila);
}


void freeG(grafoMatriz *g){
    for(int i = 0; i < g->vertices; i++){
        free(g->matriz[i]);
    }
    free(g->matriz);
}

int main(){
    grafoMatriz grafo;

    startG(&grafo, 5, true);
    insertAresta(&grafo, 1, 2);
    insertAresta(&grafo, 2, 5);
    insertAresta(&grafo, 3, 1);
    insertAresta(&grafo, 3, 2);
    insertAresta(&grafo, 3, 4);
    insertAresta(&grafo, 4, 5);
    printMatrizG(&grafo);
    showArestas(&grafo);
    printf(" \n ");
    //dfs(&grafo, 1);
    bfs(&grafo, 1);
    hasAresta(&grafo, 1, 2) ? printf(" \n Tem aresta ") : printf(" \n Nao tem aresta ");
    freeG(&grafo);


}