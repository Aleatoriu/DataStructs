#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 10
#define NAME "arquivos/visita.txt"
#define SAIDA "arquivos/saida.txt"

typedef struct ListaVisita
{
    int id;
    char proprietario[51];
    char endereco[25];
    int nCasa;
} Visita;

////////////////////////////////////////////////////////////////////
// FUNCOES FILA ESTATICA
//
typedef struct {
    int inicio;
    int fim;
    Visita vetor[TAM];
    int quantidade;
} FilaEstatica;

/**
 * @brief Funcao que inicializa a fila
 *
 * @param fila
 */
void iniciaFilaEstatica(FilaEstatica *fila) {
    fila->quantidade = 0;
    fila->inicio = 0;
    fila->fim = -1;
}

/**
 * @brief Funcao que retorna 1 se a fila estiver vazia e 0 se nao estiver
 *
 * @param fila
 * @return int
 */
int estaVaziaEstatica(FilaEstatica *fila) {
    return (fila->quantidade == 0);
}

/**
 * @brief Funcao que retorna 1 se a quantidade de elementos da fila for igual ao maximo de elementos predeterminado
 *
 * @param fila
 * @return int
 */
int estaCheiaEstatica(FilaEstatica *fila) {
    return (fila->quantidade == TAM);
}

/**
 * @brief Funcao que retorna a quantidade de elementos da fila
 *
 * @param fila
 * @return int
 */
int tamanhoFilaEstatica(FilaEstatica *fila) {
    return fila->quantidade;
}

/**
 * @brief Funcao para remocao do primeiro elemento da fila
 *
 * @param fila
 * @return int
 */
int removerFilaEstatica(FilaEstatica *fila) {
    if (estaVaziaEstatica(fila)) {
        printf("Fila esta vazia\n");
        return 0;
    }
    fila->inicio = (fila->inicio + 1) % TAM; //Atualizacao do inicio
    fila->quantidade--;

    return 1;
}

/**
 * @brief Funcao para insercao de elementos no final da fila utilizando metodo circular
 *
 * @param fila
 * @param n
 */
void inserirFilaEstatica(FilaEstatica *fila, Visita n) {
    if(estaVaziaEstatica(fila)) { //Primeira insercao
        fila->quantidade++;
        fila->fim = fila->inicio = 0;
        fila->vetor[0] = n;
        return;
    }
    if (estaCheiaEstatica(fila)) {
        printf("Fila esta cheia\n");
        return;
    }
    fila->fim = (fila->fim + 1) % TAM; //Atualizacao do final da fila
    fila->vetor[fila->fim] = n; //Insercao no final da fila
    fila->quantidade++;
}

////////////////////////////////////////////////////////////////////
// FUNCOES FILA DINAMICA
//
typedef struct NoFila *PtrNoFila;

typedef struct NoFila
{
    Visita conteudo;
    PtrNoFila proximo;
} NoFila;

typedef struct
{
    PtrNoFila inicio;
    PtrNoFila final;
    int quantidade;
} FilaDinamica;

/**
 * @brief Funcao que inicializa os valores da fila
 *
 * @param fila
 */
void iniciaFilaDinamica(FilaDinamica *fila) {
    fila->final = NULL;
    fila->inicio = NULL;
    fila->quantidade = 0;
}

/**
 * @brief Funcao que retorna 1 se a fila estiver vazia
 *
 * @param fila
 * @return int
 */
int vaziaFilaDinamica(FilaDinamica *fila) {
    return (fila->inicio == NULL);
}

/**
 * @brief Funcao que retorna o tamanho da fila
 *
 * @param fila
 * @return int
 */
int tamanhoFilaDinamica(FilaDinamica *fila) {
    return fila->quantidade;
}

/**
 * @brief Funcao para insercao de elementos na fila
 *
 * @param fila
 * @param n
 */
void inserirFilaDinamica(FilaDinamica *fila, Visita n) {
    //Criar aux de NoFila, alocar mem, copiar informacao pra ele
    PtrNoFila aux;
    aux = (PtrNoFila) malloc(sizeof(NoFila));
    aux->conteudo = n;
    if (vaziaFilaDinamica(fila)) { //Primeira insercao
        fila->inicio = fila->final = aux; //inicio e final da fila apontam pro novo no
        aux->proximo = NULL;
    } else { // Demais insercoes
        aux->proximo = fila->final->proximo; //Proximo do aux aponta para quem é o prox do fim (NULL)
        fila->final->proximo = aux; //Proximo do fim aponta para o novo elemento
        fila->final = fila->final->proximo; //Fim recebe o proximo do fim
    }
    fila->quantidade++;
}

/**
 * @brief Funcao para remocao do primeiro elemento da fila
 *
 * @param fila
 */
void removerFilaDinamica(FilaDinamica *fila) {
    if (!vaziaFilaDinamica(fila)) {
        //ptr auxiliar
        PtrNoFila aux;
        //copiar a info pro user
        aux = fila->inicio;
        //att o inicio do prox dele
        fila->inicio = fila->inicio->proximo;
        free(aux);
        //decrementa qtd
        fila->quantidade--;
    } else {
        printf("Fila esta vazia\n");
    }
}

/**
 * @brief Funcao para destruicao da fila, e feita a chamada da funcao remover ate que a quantidade de elementos na fila seja 0
 *
 * @param fila
 */
void destruirFila(FilaDinamica *fila) {
    while (fila->quantidade != 0) {
        removerFilaDinamica(fila);
    }
}

////////////////////////////////////////////////////////////////////
// FUNCOES MANIPULACAO DE ARQUIVOS
//

/**
 * @brief Open file - funcao para abrir arquivo com nome passado por parametro em formato de leitura (read)
 *
 * @param name
 * @return FILE*
 */
FILE *op_file(char *name) {
    FILE *file = fopen(name, "r");
    if (file == NULL) {
        printf("error: fail to open file\n");
        return EXIT_FAILURE;
    }
    return file;
}

/**
 * @brief Create file - funcao para criar arquivos com o nome que foi passado por parametro
 *
 * @param name
 * @return FILE*
 */
FILE *cr_file(char *name) {
    FILE *file = fopen(name, "w+");
    if (file == NULL) {
        printf("error: fail to create file\n");
        return EXIT_FAILURE;
    }
    return file;
}

/**
 * @brief Save file - funcao para salvar as informacoes da variavel no arquivo
 *
 * @param file
 * @param pilha
 * @return FILE
 */
FILE sv_file(FILE *file, FilaDinamica *fila) {
    for (PtrNoFila i = fila->inicio; i != NULL; i = i->proximo) {
        fprintf(file, "{ %d; %s; %s; %d }\n", i->conteudo.id, i->conteudo.proprietario, i->conteudo.endereco, i->conteudo.nCasa);
    }
}

/**
 * @brief Read file - funcao para ler arquivo e armazenar seus dados em uma variavel
 *
 * @param file
 * @param pPar
 * @param pImpar
 * @return int
 */
void rd_file(FILE *file, FilaEstatica *fila) {
    Visita n; //Objeto auxiliar
    char aux[100]; //Variavel de leitura auxiliar
    if (fgets(aux, 100, file) == NULL) { // acaba o loop ao final do arquivo
        return;
    } else {
        sscanf(aux, "{ %d; %[^;]; %[^;]; %d }\n", &n.id, &n.proprietario, &n.endereco, &n.nCasa); //Formatacao dos dados armazenados na variavel auxiliar, eles sao armazenados em uma variavel auxiliar do tipo do objeto que é usada para inserir na fila
        inserirFilaEstatica(fila, n);
    }
}

////////////////////////////////////////////////////////////////////
// FUNCOES MENU + MAIN
//

/**
 * @brief MENU com opcoes e chamadas das funcoes necessarias para o programa
 *
 * @param filaVisita
 * @param filaConcretizadas
 * @param filaNConcretizadas
 * @param entrada
 * @param saida
 * @return int
 */
int menu(FilaEstatica *filaVisita, FilaDinamica *filaConcretizadas, FilaDinamica *filaNConcretizadas, FILE *entrada, FILE *saida) {
    int i = 0; //indice
    while(1) { //Loop infinito
        int n = 0; //Var para opcao
        printf("\nCasa atual = { %d; %s; %s; %d }\n", filaVisita->vetor[(filaVisita->inicio + i) % TAM].id, filaVisita->vetor[(i + filaVisita->inicio) % TAM].proprietario, filaVisita->vetor[(filaVisita->inicio + i) % TAM].endereco, filaVisita->vetor[(i + filaVisita->inicio) % TAM].nCasa);
        printf("[1] Visita concretiza\n[2] Visita nao concretizada\n");
        while(n != 2 && n != 1) { //Loop para que apenas os numeros 1 e 2 sejam inseridos
            setbuf(stdin, NULL);
            scanf("%d", &n);
        }
        if (n == 1) { //Visita concretizaa
            inserirFilaDinamica(filaConcretizadas, filaVisita->vetor[(filaVisita->inicio + i) % TAM]);
            removerFilaEstatica(filaVisita);
            if (tamanhoFilaDinamica(filaConcretizadas) == TAM) {
                return 0;
            } else if (estaVaziaEstatica(filaVisita)) {
                return 1;
            }
        } else { //Visita nao concretizada
            inserirFilaDinamica(filaNConcretizadas, filaVisita->vetor[(filaVisita->inicio + i) % TAM]);
            removerFilaEstatica(filaVisita);
            rd_file(entrada, filaVisita);
            if (estaVaziaEstatica(filaVisita)) {
                return 1;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    //Arquivos
    FILE *entrada = op_file(argv[1]);
    FILE *saida = cr_file(argv[2]);
    char aux[100];
    //Var filas
    FilaEstatica filaVisita;
    FilaDinamica filaConcretizadas;
    FilaDinamica filaNConcretizadas;
    //Inicializando filas
    iniciaFilaEstatica(&filaVisita);
    iniciaFilaDinamica(&filaConcretizadas);
    iniciaFilaDinamica(&filaNConcretizadas);
    //
    for (int i = 0; i < TAM; i++) { //Carregando os dados do arquivo
        rd_file(entrada, &filaVisita);
    }
    if (menu(&filaVisita, &filaConcretizadas, &filaNConcretizadas, entrada, saida)) { //menu == 1 -> acabou o arquivo
        //Imprimindo informacoes no arquivo de saida:
        printf("Atencao: todas as casas foram visitadas!\n");
        fprintf(saida, "Visitas concretizadas:\n");
        sv_file(saida, &filaConcretizadas);
        fprintf(saida, "Visitas nao concretizadas:\n");
        sv_file(saida, &filaNConcretizadas);
        fprintf(saida, "Meta de 10 visitas nao foi efetuada\n");
        //Destruicao das filas dinamicas com memoria alocada
        destruirFila(&filaConcretizadas);
        destruirFila(&filaNConcretizadas);
        //Fechando arquivos
        fclose(entrada);
        fclose(saida);
    } else { //10 visitas concretizadas
        //Imprimindo informacoes no arquivo de saida
        printf("Atencao: 10 visitas foram concretizadas!\n");
        fprintf(saida, "Visitas concretizadas:\n");
        sv_file(saida, &filaConcretizadas);
        fprintf(saida, "Visitas nao concretizadas:\n");
        sv_file(saida, &filaNConcretizadas);
        fprintf(saida, "Meta 10 visitas efetuada\n");
        //Destruicao das filas dinamicas com memoria alocada
        destruirFila(&filaConcretizadas);
        destruirFila(&filaNConcretizadas);
        //Fechando arquivos
        fclose(entrada);
        fclose(saida);
    }
    return EXIT_SUCCESS;
}