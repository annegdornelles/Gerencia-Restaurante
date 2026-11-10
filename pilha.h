#ifndef PILHA_H
#define PILHA_H

typedef struct Prato
{
    struct Prato *prox;
} Prato;

typedef struct Pilha
{
    Prato *topo;
    int quant;
} Pilha;

void inicializarPilha(Pilha *pilha);
int empilhar(Pilha *pilha);
void desempilhar(Pilha *pilha);
void imprimirPilha(Pilha *pilha);
void inserirPratos(Pilha *pilha);
void esvaziarPilha(Pilha *pilha);

#endif