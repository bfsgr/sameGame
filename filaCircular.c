#include <stdio.h>
#include <stdlib.h>

#define tamMax 194

typedef struct ixj{
	int i;
	int j;
} ixj;

typedef struct Fila {
    ixj elem[tamMax];
    int inicio;
    int fim;
} Fila;

void inicializaFila(Fila *q){
    q->inicio = 0;
    q->fim = 0;
}

int filaVazia(Fila *q){
    return q->inicio == q->fim;
}

int filaCheia(Fila *q){
    return ( (q->fim + 1) % tamMax) == q->inicio;
}

void insereFila(Fila *q, ixj x){
    if(!filaCheia(q)){
        q->fim = (q->fim + 1) % tamMax;
        q->elem[q->fim] = x;
    }
}

void removefila(Fila *q, ixj *x){
    if(!filaVazia(q)){
        q->inicio = (q->inicio + 1) % tamMax;
        *x = q->elem[q->inicio];
    }
}

ixj primeiroDaFila(Fila *q){
    if(!filaVazia(q)){
        return q->elem[((q->inicio + 1) % tamMax)];
    }
}
