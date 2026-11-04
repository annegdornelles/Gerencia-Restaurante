#include<stdio.h>
#include<stdlib.h>

void inicializarPilha(Pilha *pilha);
void empilhar(Pilha *pilha);
void desempilhar(Pilha *pilha);
void imprimirPilha(Pilha *pilha);
#ifndef PILHA_H
#define PILHA_H

typedef struct Prato{
    struct Prato *prox;
} Prato;

typedef struct Pilha{
    Prato *topo;
    int quant;
}Pilha;

#endif
