#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct grafoM{
    int **matriz;
    int vertices;
    int arestas;
    bool dirigido;
}grafoMatriz;

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

void buscaProfundidade(grafoMatriz *g, int v, bool *visitados){
    visitados[v-1] = true;
    printf("%d ", v);
    for(int i = 0; i < g->vertices; i++){
        if(g->matriz[v-1][i] == 1 && !visitados[i]){
            buscaProfundidade(g, i+1, visitados);
        }
    }
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
    insertAresta(&grafo, 1, 3);
    insertAresta(&grafo, 2, 3);
    insertAresta(&grafo, 2, 5);
    insertAresta(&grafo, 3, 4);
    insertAresta(&grafo, 4, 5);
    printMatrizG(&grafo);
    showArestas(&grafo);
    printf(" \n ");
    buscaProfundidade(&grafo, 1, (bool*)calloc(grafo.vertices, sizeof(bool)));
    hasAresta(&grafo, 1, 2) ? printf(" \n Tem aresta ") : printf(" \n Nao tem aresta ");
    freeG(&grafo);


}