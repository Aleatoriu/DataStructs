#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node_st  {
    int value;
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




int main(){
    node_t *root = initTree();
    insertNode(&root, 5);
    insertNode(&root, 3);   
    insertNode(&root, 7);
    insertNode(&root, 2);
    insertNode(&root, 4);
    insertNode(&root, 6);
    insertNode(&root, 8);
    insertNode(&root, 1);
    insertNode(&root, 1);
    insertNode(&root, 9);
    insertNode(&root, 10);
    printf("\nPreOrder: ");
    posOrder(root);
    printf("\nPosOrder: ");
    preOrder(root);
    printf("\nInOrder: ");
    inOrder(root);
    printf("\n");
    fireTree(&root);
    posOrder(root);
    isEmpty(root) ? printf(" Árvore vazia ") : printf(" Árvore não vazia ");
    return EXIT_SUCCESS;
}