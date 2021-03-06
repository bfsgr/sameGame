#include <stdio.h>
#include <stdlib.h>

typedef struct ixj{
	int i;
	int j;
} ixj;

typedef struct caixinha{
    ixj info;
    struct caixinha *prox;
} caixinha;

typedef struct Fila{
    caixinha *inicio;
    caixinha *fim;
} Fila;


void inicializaFila(Fila *q){
    q->inicio = NULL;
    q->fim = NULL;
}

int filaVazia(Fila *q){
    return q->inicio == NULL;
}

void insereFila(Fila *q, ixj x){
    caixinha *r;
    r = malloc(sizeof(caixinha));
    r->info = x;
    r->prox = NULL;
    if(filaVazia(q)){
        q->inicio = r;
    } else {
        q->fim->prox = r;
    }
    q->fim = r;
}

void removeFila(Fila *q, ixj *x){
    if(!filaVazia(q)){
        caixinha *r = q->inicio;
        *x = r->info;
        q->inicio = q->inicio->prox;
        free(r);
        if(filaVazia(q)){
            q->fim = NULL;
        }
    }
}

ixj primeiroDaFila(Fila *q){
    if(!filaVazia(q)){
        return q->inicio->info;
    }
}