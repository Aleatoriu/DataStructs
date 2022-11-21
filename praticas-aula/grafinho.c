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

void freeG(grafoMatriz *g){
    for(int i = 0; i < g->vertices; i++){
        free(g->matriz[i]);
    }
    free(g->matriz);
}

int main(){
    grafoMatriz grafo;

    startG(&grafo, 5, false);
    freeG(&grafo);


}