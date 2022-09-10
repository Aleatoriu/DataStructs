#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int buscaBinaria(int vetor[], int valor, int tamanho, int inicio, int fim){
    int meio = (int) (inicio+fim)/2;
    if (inicio>fim)  return -1;
    if (vetor[meio] == valor);
    if(vetor[meio]<tamanho) return(buscaBinaria(valor,vetor, meio+1))
    else return(buscaBinaria(valor, vetor, meio-1));

}


int main(void){
    int inicio;
    int tamanho = 10;
    int valor = 20;
    int vetor = {10 , 30 , 41, 312 ,33, 4324 ,3424 ,5453,331,20};
    int fim = tamanho - 1;
    
    


    }