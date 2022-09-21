#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node_st  {
    int value;
    struct node_st *left;
    struct node_st *right;
} node_t;

node_t *initTree() {
    return NULL;
}

bool isEmpty(node_t *root){
    if(root == NULL){
        return true;
    }
    return false;
}


void insert(node_t **root, int value){
    if(isEmpty(*root)){
        (*root) = (node_t *) malloc(sizeof(node_t));
        (*root)->value = value;
        (*root)->left = NULL;
        (*root)->right = NULL;
    } else {
        if(value < (*root)->value){
            insert((*root)->left, value);
        } else {
            insert((*root)->right, value);
        }
    }
}


void printTree(node_t *root){
    if(root != NULL){
        printTree(root->left);
        printf("%d ", root->value);
        printTree(root->right);
    }
}



int main(){
    node_t *root;
    root = initTree();
    insert(&root, 10);
    printTree(&root);
    return 0;
}