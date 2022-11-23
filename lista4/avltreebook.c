#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>





FILE openArq(char *nomeArq) {
    FILE *arq = fopen(nomeArq, "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s no modo %s \n", nomeArq);
        exit(1);
    }
    return arq;
}

int main(void){
    FILE *arq;
    char temp1[23], temp2[23];
    arq = fopen("alou.xlsx", "r");
    while(!feof(arq)){
        fscanf(arq,"%s \t %s \n", temp1, temp2);
        printf("%s \t %s \n", temp1, temp2);
    }
}