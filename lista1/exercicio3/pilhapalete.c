#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX 4
#define STACKS 5

typedef struct stack {
    int top;
    int qtt;
    int vet[MAX];
} stack;

stack *createStack() {
    stack *s = malloc(sizeof(stack));
    s->top = 0;
    s->qtt = 0;
    return s;
}//cria uma pilha vazia e retorna o endereço dela na memória.

// \/ Abaixo esta o cabecalho das funcoes criadas embaixo da main. \/

stack *createStack();
bool isFull(stack *s);
bool isEmpty(stack *s);
void push(stack *s, int data);
int pop(stack *s);
void destroyStack(stack *s);
void printStack(stack *s);
int getShortestStack(stack **s);
int getLongestStack(stack **s);
void showAllStack(stack **s);



int main() {
    stack **s = malloc(sizeof(stack*) * STACKS); // array de pilhas
    for (int i = 0; i < STACKS; i++) { // para cada pilha no array, crie uma pilha
        s[i] = createStack();
    }

    int cmd;

    do {
        printf("---------- CMD ----------\n");
        printf("- (1) Adicionar novo palete\n");
        printf("- (2) Remover palete\n");
        printf("- (3) Sair\n");
        printf("-------------------------\n");
        printf("\n\nDigite o comando: ");
        scanf(" %d", &cmd);

        switch (cmd) {
            case 1:
                printf("Digite o numero do palete: ");
                int num;
                scanf("%d", &num);
                push(s[getShortestStack(s)], num);
                showAllStack(s);
                break;
            case 2:
                printf("Palete removido: %d\n", pop(s[getLongestStack(s)]));
                showAllStack(s);
                break;
            case 3:
                break;
            default:
                printf("Comando inválido!\n");
                break;
        }
    } while (cmd != 3);

    for (int i = 0; i < STACKS; i++) {
        destroyStack(s[i]);
    }
    free(s);
    
    return EXIT_SUCCESS;
} // end main


void showAllStack(stack **s) {
    for (int i = 0; i < STACKS; i++) {
        printf("Stack %d: ", i);
        printStack(s[i]);
    }
    printf("\n\n");
}// a funcao showAllStack() foi criada para mostrar todas as pilhas de acordo com oq for perdido ou adicionado.

int getShortestStack(stack **s) {
    int shortest = 0;
    for (int i = 1; i < STACKS; i++) {
        if (s[i]->qtt < s[shortest]->qtt) {
            shortest = i;
        }
    }
    return shortest;
}// a funcao getShortestStack retorna o indice da pilha mais curta. (Funcao de retorno)

int getLongestStack(stack **s) {
    int longest = 0;
    for (int i = 1; i < STACKS; i++) {
        if (s[i]->qtt > s[longest]->qtt) {
            longest = i;
        }
    }
    return longest;
}// A função getShortestStack retorna o índice do vetor de pilhas que possui a menor quantidade de elementos. (Funcao de retorno)

bool isFull(stack *s) {
    return s->qtt == MAX;
}// A funcao isFull retorna true se a pilha estiver cheia. (Funcao de verificacao)

bool isEmpty(stack *s) {
    return s->qtt == 0;
}// A funcao isEmpty retorna true se a pilha estiver vazia e false caso contrario. (Funcao de verificacao.)

void push(stack *s, int data) {
    if (isFull(s)) return;

    s->vet[s->top] = data;
    s->top++;
    s->qtt++;
}// A função push() recebe uma pilha e um dado, e empilha o dado na pilha de forma organizada.

int pop(stack *s) {
    if (isEmpty(s)) return -1;

    s->top--;
    s->qtt--;
    return s->vet[s->top];
}// a função pop retorna o valor do topo da pilha e decrementa o topo e a quantidade de elementos da pilha.

void destroyStack(stack *s) {
    free(s);
}// Destroi a pilha da memoria.

void printStack(stack *s) {
    for (int i = 0; i < s->qtt; i++) {
        printf("%d ", s->vet[i]);
    }
    printf("\n");
}// Imprime a pilha.

// fim do arquivo.