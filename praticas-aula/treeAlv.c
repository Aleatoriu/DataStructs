#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node_st  {
    int value;
    int height;
    struct node_st *left;
    struct node_st *right;
} node_t;

node_t *initTree(){
    return NULL;
}

void insertNode(node_t **root, int value){
    if(*root == NULL){
        *root = (node_t *) malloc(sizeof(node_t));
        (*root)->value = value;
        (*root)->left = NULL;
        (*root)->right = NULL;
    } else {
        if(value == (*root)->value){
            printf("Valor já existe na árvore %d == %d ", value, (*root)->value);
        } else if(value < (*root)->value){
            insertNode(&(*root)->left, value);
        } else {
            insertNode(&(*root)->right, value);
        }
    }
}

bool isEmpty(node_t *root){
    return root == NULL;
}

void preOrder(node_t *root){
    if(!isEmpty(root)){
        printf("%d ", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void posOrder(node_t *root){
    if(!isEmpty(root)){
        posOrder(root->left);
        posOrder(root->right);
        printf("%d ", root->value);
    }
}

void inOrder(node_t *root){
    if(!isEmpty(root)){
        inOrder(root->left);
        printf("%d ", root->value);
        inOrder(root->right);
    }
}

void fireTree(node_t **root){
    if(!isEmpty(*root)){
        fireTree(&(*root)->left);
        fireTree(&(*root)->right);
        free(*root);
        *root = NULL;
    }
}

node_t *searchNode(node_t **root, int value){
    if(isEmpty(*root)){
        return NULL;
    } else {
        if(value == (*root)->value){
            return (*root);
        } else if(value < (*root)->value){
            return searchNode(&(*root)->left, value);
        } else {
            return searchNode(&(*root)->right, value);
        }
    }
}

node_t *searchFather(node_t **root, int value){
    if(isEmpty(*root)){
        return NULL;
    } else {
        if(value == (*root)->value){
            return NULL;
        } else if(value < (*root)->value){
            if((*root)->left->value == value){
                return (*root);
            } else {
                return searchFather(&(*root)->left, value);
            }
        } else {
            if((*root)->right->value == value){
                return (*root);
            } else {
                return searchFather(&(*root)->right, value);
            }
        }
    }
}

node_t* searchMax(node_t **root){  // retorna o nó com o maior valor da subárvore da esquerda
    if(((*root) -> right) == NULL){
        node_t *aux = (*root);
        if((*root)-> left != NULL){
            (*root) = (*root)->left;
            return aux;
        }else{
            (*root) = NULL;
            return aux;
        }
    } else {
        return searchMax(&(*root)->right);
    }
}

node_t *searchMin(node_t **root){  //menor numero da direita
    if(((*root) -> left) == NULL){
        node_t *aux = (*root);
        if((*root)-> right != NULL){
            (*root) = (*root)->right;
            return aux;
        }else{
            (*root) = NULL;
            return aux;
        }
    } else {
        return searchMin(&(*root)->left);
    }
}



bool removeNode(node_t **root, int value){
    if(isEmpty(*root)== true) return false;
    else {
        if(value < (*root)->value){
            return removeNode(&(*root)->left, value);
        } else if(value > (*root)->value){
            return removeNode(&(*root)->right, value);
        } else {
            if((*root)->left == NULL && (*root)->right == NULL){ //caso 1
                free(*root);
                *root = NULL;
                return true;
            } if((*root)->left == NULL){               //caso 2
                node_t *aux = *root;
                *root = (*root)->right;
                free(aux);
                return true;
            } if((*root)->right == NULL){              //caso 2
                node_t *aux = *root;
                *root = (*root)->left;
                free(aux);
                return true;
            } 
            node_t *element =searchMax(&(*root)->right);
            element->left = (*root)->left;
            element->right = (*root)->right;
            node_t *aux = *root;
            *root = element;
            free(aux);
            return true;        
        }
        if((*root)-> value > value){
            return removeNode(&(*root)->left, value);
        } else {
            return removeNode(&(*root)->right, value);
        }
    }
}

void maxValue(node_t *root){
    if(root->right == NULL){
        printf("Maior valor: %d ", root->value);
    } else {
        maxValue(root->right);
    }
}

void minValue(node_t *root){
    if(root->left == NULL){
        printf("Menor valor: %d ", root->value);
    } else {
        minValue(root->left);
    }
}

void rotateLeft(node_t **root){
    node_t *aux = (*root)->right;
    (*root)->right = aux->left;
    aux->left = (*root);
    (*root) = aux;
}

void rotateRight(node_t **root){
    node_t *aux = (*root)->left;
    (*root)->left = aux->right;
    aux->right = (*root);
    (*root) = aux;
}

void dualLeft(node_t **root){
    rotateRight(&(*root)->right);
    rotateLeft(&(*root));
}

void dualRight(node_t **root){
    rotateLeft(&(*root)->left);
    rotateRight(&(*root));
}

void balanceTree(node_t **root){
    if((*root)->left != NULL){
        balanceTree(&(*root)->left);
    }
    if((*root)->right != NULL){
        balanceTree(&(*root)->right);
    }
    if((*root)->left != NULL && (*root)->right != NULL){
        if((*root)->left->height - (*root)->right->height > 1){
            if((*root)->left->left->height - (*root)->right->height > 0){
                rotateRight(&(*root));
            } else {
                dualRight(&(*root));
            }
        } else if((*root)->right->height - (*root)->left->height > 1){
            if((*root)->right->right->height - (*root)->left->height > 0){
                rotateLeft(&(*root));
            } else {
                dualLeft(&(*root));
            }
        }
    }
}

int treeHeight(node_t *root){
    if(root == NULL){
        return -1;
    } else {
        int left = treeHeight(root->left);
        int right = treeHeight(root->right);
        if(left > right){
            return left + 1;
        } else {
            return right + 1;
        }
    }
}

int main(){
    node_t *root = initTree();
    insertNode(&root, 12);
    insertNode(&root, 16);   
    insertNode(&root, 8);
    insertNode(&root, 2);
    insertNode(&root, 6);
    printf("\nPreOrder: ");
    preOrder(root);
    printf("\nPosOrder: ");
    posOrder(root);
    printf("\nInOrder: ");
    inOrder(root);
    printf("\n");
    removeNode(&root, 5);

    
    balanceTree(&root);

    printf("\nPreOrder: ");
    preOrder(root);
    printf("\nPosOrder: ");
    posOrder(root);
    printf("\nInOrder: ");
    inOrder(root);
    printf("\n");
    printf("Altura: %d", treeHeight(root));

    if(searchNode(&root, 5) != NULL){
        printf("Valor encontrado");  rotateLeft(&root);
        printf("\nValor: %d", searchNode(&root, 5)->value);
    } else {
        printf("\nValor não encontrado\n");
    }
    fireTree(&root);
    isEmpty(root) ? printf("\nÁrvore vazia ") : printf("\nÁrvore não vazia ");
    

    return EXIT_SUCCESS;
}