void inicializaPilha(Pilha *pilha);
void empilha(Pilha *pilha);
void desempilha(Pilha *pilha);
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
