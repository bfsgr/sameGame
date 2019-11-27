#include <stdio.h>
#include <stdlib.h>

typedef struct dado{
    int info;
    struct dado *prox;
} dado;

typedef struct Pilha{
    dado *topo;
} Pilha;

void inicializaPilha(Pilha *p){
    p->topo = NULL;
}

int pilhaVazia(Pilha *p){
    return p->topo == NULL;
}

void empilha(Pilha *p, int x){
    dado *q;
    q = malloc(sizeof(dado));
    q->info = x;
    q->prox = p->topo;
    p->topo = q;
}

void desempilha(Pilha *p, int *x){
    if(!pilhaVazia(p)){
        dado *q = p->topo;
        *x = q->info;
        p->topo = p->topo->prox;
        free(q);
    }
}

int elementoDoTopo(Pilha *p){
    if(!pilhaVazia(p)){
        return p->topo->info;
    }
}