#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define BUFFER_SIZE 100

typedef struct data_st {
    int dia;
    int mes;
    int ano;
} data_t;

typedef struct pacientes_st{
    char nome[50];
    char sexo;
    data_t dayNas;
    data_t lastVisit;
}pacientes_t;

typedef struct node_st  {
    pacientes_t value;
    struct node_st *prox;
    struct node_st *ant;
} node_t;

typedef struct lista_st {
    int size;
    node_t *head;
    node_t *tail;
} lista_t;

void initList(lista_t *lista){
    lista->size = 0;
    lista->head = NULL;
    lista->tail = NULL;
}

bool isEmpty(lista_t *lista){
    return lista->size == 0;
}

void insertNode(lista_t *lista, pacientes_t pacientes){                //insere no na lista de forma ordenada
    node_t *novo = (node_t *) malloc(sizeof(node_t));
    novo->value = pacientes;
    novo->prox = NULL;
    novo->ant = NULL;
    if(isEmpty(lista)){
        lista->head = novo;
        lista->tail = novo;
    } else if (strcmp(pacientes.nome, lista->head->value.nome) < 0){
        novo->prox = lista -> head;
        lista->head->ant = novo;
        lista->head = novo;
    }else {
        node_t *aux = lista->head;
        while (aux -> prox != NULL && strcmp(pacientes.nome, aux->prox->value.nome) > 0){
            aux = aux->prox;
        }
        if(aux->prox != NULL){
            aux -> prox -> ant = novo;
        }
        novo->prox = aux->prox;
        novo->ant = aux;
        if(aux->prox == NULL){
            lista->tail = novo;
        }
        aux->prox = novo;
    }
    lista->size++;
}                                                            

char *lerString(FILE *f, char parada, bool* eof) {         // Lê uma string até encontrar um caractere parada
    char *linha = NULL, tmp; //variavel temporaria
    int cont = 0; //contador

    do {
        tmp = getc(f);
        if (tmp == '\r') {
            tmp = getc(f);
        }
        if (!isalnum(tmp) && tmp != '<' && tmp != '>' && tmp != '/' && tmp != ',' && tmp != ' '  ){
            int a = tmp;
           // printf("Caractere invalido: %d\n", a);
        }
        if (cont % BUFFER_SIZE == 0) { // Aloca em blocos de BUFFER_SIZE BUFFER_SIZE
            linha = realloc(linha, sizeof(char) * (cont + BUFFER_SIZE));
        }
        if (tmp == parada) {
            break;  
        }
        if(tmp == EOF){
            *eof = true;
            break;
        }
        if ((tmp != '\n') && (tmp != EOF)) {
            linha[cont++] = tmp;
        }
    } while ((tmp != '\n') && (tmp != EOF));
    linha[cont] = '\0';
    return linha;
}

pacientes_t splitLine(char *line, FILE *f, lista_t *lista){ // Separa a linha em tokens
    pacientes_t p;
    char aux[100]; //Variavel de leitura auxiliar
    while (fgets(aux, 100, f) != NULL) { // acaba o loop ao final do arquivo
        sscanf(aux, "<%[^,], %[^,], %d/%d/%d, %d/%d/%d>\n", p.nome, &p.sexo, &p.dayNas.dia, &p.dayNas.mes, &p.dayNas.ano, &p.lastVisit.dia, &p.lastVisit.mes, &p.lastVisit.ano);
        insertNode(lista, p);
    }
    return p;
}

void insertIntoList(lista_t *lista, char *line, FILE *f){         // Insere na lista
    pacientes_t p = splitLine(line, f, lista);
}

void getFileInputAndInsert(FILE *f, lista_t *lista) {                // Lê o arquivo e insere na lista
    bool eof = false;
    while (!eof) {
        char *input = lerString(f, '\n', &eof);
        insertIntoList(lista, input, f);
    }
}

FILE* openFile(char *fileName, char *mode){                        // Abre o arquivo
    FILE *f = fopen(fileName, mode);
    if(f == NULL){
        printf("Erro ao abrir o arquivo %s ", fileName);
        exit(1);
    }
    return f;
}


void destroyList(lista_t *lista){                             // Libera a lista
    node_t *aux = lista->head;
    while(aux != NULL){
        node_t *aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
}

bool sexDefined(char sexo){                                  // Verifica se o sexo foi definido
    return sexo == 'M' || sexo == 'F';
}

int dateLastVisit(pacientes_t p){                          // faz o calculo de verificação da data da ultima visita com a data atual do pc e retorna o valor
    struct tm *data;
    time_t t;
    time(&t);
    data = localtime(&t);
    int diaMeses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int ano = ((data->tm_year + 1900) - p.lastVisit.ano) * 365;    
    int mes = 0;
    int dia = (data->tm_mday - p.lastVisit.dia);
    int subMes = ((data->tm_mon + 1) - p.lastVisit.mes); 
    int lastVisit = 0;
    if(subMes > 0){
        int mesAux = p.lastVisit.mes;
        while(mesAux != (data->tm_mon + 1)){
            mes = mes + diaMeses[mesAux];
            mesAux++;
        }
    }else{
        int mesAux = data->tm_mon + 1;
        while(mesAux != (p.lastVisit.mes)){
            mes = mes - diaMeses[mesAux];
            mesAux++;
        }
    }
    lastVisit = ano + mes + dia;
    return lastVisit;
}

int dayNas(pacientes_t p){                                  // faz o calculo de verificação da data de nascimento com a data atual do pc e retorna o valor
    struct tm *data;
    time_t t;
    time(&t);
    data = localtime(&t);
    int idade = 0;
    idade = (data->tm_year + 1900) - p.dayNas.ano;
    return idade = (data->tm_year + 1900) - p.dayNas.ano;
}

void locatePacientesName(lista_t *lista, char *name){       // Localiza o paciente pelo nome
    node_t *aux = lista->head;
    while(aux != NULL){
        if(strcmp(aux->value.nome, name) == 0){
            printf("Nome: %s\n", aux->value.nome);
            printf("Sexo: %c\n", aux->value.sexo);
            printf("Data de nascimento: %d/%d/%d\n", aux->value.dayNas.dia, aux->value.dayNas.mes, aux->value.dayNas.ano);
            printf("Ultima consulta: %d/%d/%d\n", aux->value.lastVisit.dia, aux->value.lastVisit.mes, aux->value.lastVisit.ano);
            printf("Idade: %d\n", dayNas(aux->value));
            printf("Tempo percorrido pela ultima consulta: %d dias \n", dateLastVisit(aux->value));
        }
        aux = aux->prox;

    }
}

void insertManualNode(lista_t *lista){                     // Insere manualmente um paciente na lista
    pacientes_t manual;
    setbuf(stdin, NULL);
    printf("Digite o nome do paciente: ");
    fgets(manual.nome, 50, stdin);
    manual.nome[strcspn(manual.nome, "\n")] = '\0';
    setbuf(stdin, NULL);
    printf("Digite o sexo do paciente: ");
    scanf("%c", &manual.sexo);
    manual.sexo = toupper(manual.sexo);
    setbuf(stdin, NULL);
    printf("Digite a data de nascimento do paciente: ");
    scanf("%d/%d/%d", &manual.dayNas.dia, &manual.dayNas.mes, &manual.dayNas.ano);
    printf("Digite a data da ultima consulta do paciente: ");
    scanf("%d/%d/%d", &manual.lastVisit.dia, &manual.lastVisit.mes, &manual.lastVisit.ano);
    insertNode(lista, manual);
}

FILE *saveArqs(FILE *outputMasc, FILE *outputFem, lista_t *lista){                // Salva os arquivos
    node_t *aux = lista->tail;
    node_t *aux2 = lista->head;
    while(aux != NULL){
        if(aux->value.sexo == 'M'){                               // Salva o arquivo masculino a partir da calda da lista
            fprintf(outputMasc, "<%s, ", aux->value.nome);
            fprintf(outputMasc, "%c, ", aux->value.sexo);
            fprintf(outputMasc, "%d/%d/%d, ", aux->value.dayNas.dia, aux->value.dayNas.mes, aux->value.dayNas.ano);
            fprintf(outputMasc, "%d/%d/%d>\n", aux->value.lastVisit.dia, aux->value.lastVisit.mes, aux->value.lastVisit.ano);
        }
        if(aux2 -> value.sexo == 'F'){                           // Salva o arquivo feminino a partir da cabeça da lista
            fprintf(outputFem, "<%s, ", aux2->value.nome);
            fprintf(outputFem, "%c, ", aux2->value.sexo);
            fprintf(outputFem, "%d/%d/%d, ", aux2->value.dayNas.dia, aux2->value.dayNas.mes, aux2->value.dayNas.ano);
            fprintf(outputFem, "%d/%d/%d>\n", aux2->value.lastVisit.dia, aux2->value.lastVisit.mes, aux2->value.lastVisit.ano);
        }
        aux = aux->ant;
        aux2 = aux2->prox;
    }
    return outputMasc;
    return outputFem;
}

int main(int argc, char *argv[]){                             
    lista_t lista;
    initList(&lista);
    FILE *input = openFile(argv[1], "r");
    FILE *outputMasc = openFile(argv[2], "w");
    FILE *outputFem = openFile(argv[3], "w");
    getFileInputAndInsert(input, &lista);
    int op = 0;
    while(1){
        printf("Sistema de cadastro de pacientes\n");  
        printf("OPÇÕES:\n");
        printf("1 - Inserir paciente\n");
        printf("2 - Buscar paciente\n");;
        printf("3 - Salvar \n");
        printf("4 - Sair\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &op);
        switch(op){
            case 1:
                insertManualNode(&lista);
                break;
            case 2:
                printf("Digite o nome do paciente: ");
                char name[100];
                setbuf(stdin, NULL);
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0';
                locatePacientesName(&lista, name);
                break;
            case 3:
                saveArqs(outputMasc, outputFem, &lista);
                break;
            case 4:
                printf("Saindo...\n");
                destroyList(&lista);
                fclose(input);
                fclose(outputMasc);
                fclose(outputFem);
                return EXIT_SUCCESS;
                break;
            default:
                printf("Opção inválida\n");
                break;
        }
    }
}
    









