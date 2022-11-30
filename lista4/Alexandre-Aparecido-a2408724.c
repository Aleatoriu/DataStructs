#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
    char *key; 
    int page;   
    int height; 
    struct node *left; 
    struct node *right;
} nodeAVL;               // Estrutura do nó da árvore AVL juntamente com seus dados


nodeAVL *initTree(){                 // Inicializa a arvore
    return NULL;
}

bool isEmpty(nodeAVL **tree){         // Verifica se a arvore esta vazia
    return (*tree) == NULL;
}

int height(nodeAVL *node){
    if(node == NULL)
        return 0;
    return node->height;
}

int refreshHeight(nodeAVL *node){      // Atualiza a altura do nó
    if(node == NULL)
        return 0;
    int heightLeft = height(node->left);         // Altura da subarvore esquerda
    int heightRight = height(node->right);         // Altura da subarvore direita
    if(heightLeft > heightRight)
        return heightLeft + 1;                  // Retorna a altura da subarvore com maior altura + 1
    else
        return heightRight + 1;            // Retorna a altura da subarvore com maior altura + 1
}

void rotateLeft(nodeAVL **node){               // Rotacao simples a esquerda
    nodeAVL *aux = (*node)->right;
    (*node)->right = aux->left;
    aux->left = (*node);
    (*node)->height = refreshHeight(*node);
    aux->height = refreshHeight(aux);
    (*node) = aux;
}

void rotateRight(nodeAVL **node){         // Rotacao simples a direita
    nodeAVL *aux = (*node)->left;
    (*node)->left = aux->right;
    aux->right = (*node);
    (*node)->height = refreshHeight(*node);
    aux->height = refreshHeight(aux);
    (*node) = aux;
}

void rotateLeftRight(nodeAVL **node){          // Rotacao dupla a esquerda
    rotateLeft(&(*node)->left);
    rotateRight(node);
}

void rotateRightLeft(nodeAVL **node){         // Rotacao dupla a direita
    rotateRight(&(*node)->right);
    rotateLeft(node);
}

int balanceFactor(nodeAVL *node){       // Calcula o fator de balanceamento
    if(node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}
 
void balance(nodeAVL **node){                // Balanceia a arvore
    if(balanceFactor(*node) == 2){              // Se o fator de balanceamento for 2
        if(balanceFactor((*node)->left) >= 0){          // Se o fator de balanceamento do filho esquerdo for maior ou igual a 0
            rotateRight(node);                            // Rotacao simples a direita
        }else{                                            // Se o fator de balanceamento do filho esquerdo for menor que 0
            rotateLeftRight(node);                         // Rotacao dupla a esquerda
        }
    }else if(balanceFactor(*node) == -2){             // Se o fator de balanceamento for -2
        if(balanceFactor((*node)->right) <= 0){         // Se o fator de balanceamento do filho direito for menor ou igual a 0
            rotateLeft(node);                               // Rotacao simples a esquerda
        }else{                                                 // Se o fator de balanceamento do filho direito for maior que 0
            rotateRightLeft(node);                                 // Rotacao dupla a direita
        }
    }
}

void insert(nodeAVL **tree, char *key, int page){                       // Insere um nó na arvore
    if((*tree) == NULL){                                                                
        (*tree) = (nodeAVL*) malloc(sizeof(nodeAVL));
        (*tree)->key = (char*) malloc((strlen(key) + 1) * sizeof(char));
        strcpy((*tree)->key, key);
        (*tree)->page = page;
        (*tree)->height = 1;
        (*tree)->left = NULL;
        (*tree)->right = NULL;
    }else{
        if(strcmp(key, (*tree)->key) < 0){                  // Se a chave for menor que a chave do nó atual
            insert(&(*tree)->left, key, page);                  // Insere na subarvore esquerda
        }else if(strcmp(key, (*tree)->key) > 0){                    // Se a chave for maior que a chave do nó atual
            insert(&(*tree)->right, key, page);                         // Insere na subarvore direita
        }else{                                                            
            printf("Chave ja existente na arvore AVL de livros de pagina %d e %d para %s e %s respectivamente (ignorando a nova insercao).\n ", (*tree)->page, page, (*tree)->key, key);
            return;
        }
    }
    (*tree)->height = refreshHeight(*tree);             // Atualiza a altura do nó
    balance(tree);                                      // Balanceia a arvore
}

void preOrder(nodeAVL *tree){               // Percorre a arvore em pre ordem
    if(tree != NULL){                   
        printf("%s %d " , tree->key, tree->page);
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

void inOrder(nodeAVL *tree){                            // Percorre a arvore em ordem
    if(tree != NULL){
        inOrder(tree->left);
        printf("%s \t %d \n" , tree->key, tree->page);
        inOrder(tree->right);
    }
}

void posOrder(nodeAVL *tree){                       // Percorre a arvore em pos ordem
    if(tree != NULL){
        posOrder(tree->left);
        posOrder(tree->right);
        printf("%s %d " , tree->key, tree->page);
    }
}

void search(nodeAVL *tree, char *key){                  // Busca um nó na arvore
    if(tree == NULL){
        printf("Chave nao encontrada " ) ;
        return;
    }
    if(strcmp(key, tree->key) < 0){ 
        search(tree->left, key);
    }else if(strcmp(key, tree->key) > 0){
        search(tree->right, key);
    }else{
        printf("Chave encontrada na pagina %d " , tree->page);
    }
}

void freeTree(nodeAVL *tree){               // Libera a memoria alocada para a arvore
    if(tree != NULL){                               
        freeTree(tree->left);
        freeTree(tree->right);
        free(tree->key);
        free(tree);
    }
}


void openFile(nodeAVL **tree, char *fileName){          // Abre o arquivo e insere os dados na arvore
    FILE *file;
    char key[100];
    int page;
    file = fopen(fileName, "r");
    if(file == NULL){
        printf("Erro ao abrir o arquivo " ) ;
        return;
    }
    while(!feof(file)){
        fscanf(file,"%s \t %d \n", key, &page);
        insert(tree, key, page);
    }
    fclose(file);
}

void systemMenu(nodeAVL **tree){                        // Menu do sistema
    int option; 
    char key[100];
    int page;
    do{
        printf("\n\n 1 - Inserir livro na arvore AVL \n" ) ;
        printf(" 2 - Buscar livro na arvore AVL \n" ) ;
        printf(" 3 - Imprimir arvore AVL em ordem\n" ) ;
        printf(" 4 - Sair\n" ) ;
        scanf("%d", &option);
        switch(option){
            case 1:
                printf("Digite a chave e a pagina a ser inserido: " ) ;
                scanf("%s %d", key, &page);
                insert(tree, key, page);
                break;
            case 2:
                printf("Digite a chave a ser buscado: " ) ;
                scanf("%s", key);
                search(*tree, key);
                break;
            case 3:
                inOrder(*tree);
                break; 
            case 4:
                freeTree(*tree);
                printf("Saindo do programa \n" ) ;
                break;
            default:
                printf("Opcao invalida \n" ) ;
                break;
        }
    }while(option != 4);
}


int main(int argc, char *argv[]){                       
    nodeAVL *tree = initTree();
    openFile(&tree, argv[1]);
    systemMenu(&tree);
    return EXIT_SUCCESS;
}

