#ifndef RESTAURANTE_H
#define RESTAURANTE_H
#include <stdbool.h>
#include "fila.h"
#include "pilha.h"

typedef struct Mesa {
    int numero;
    bool ocupada;
    int quantPessoasMesa;
    int comanda;
    int quantPratosDisp;
    int quantPratos;
} Mesa;

typedef struct Restaurante {
    int linhas;
    int colunas;
    Mesa **mesas;
    Fila fila;
    Pilha pilha;
} Restaurante;


void inserirMesas(Restaurante *restaurante);

void inserirGrupo(Restaurante *restaurante);

int ocuparMesa(Restaurante *restaurante, int quantidade, int comanda);

void liberarMesa(Restaurante *restaurante);

void chamarGrupo(Restaurante *restaurante);

void desistirFilaEspera(Restaurante *restaurante);

void atualizarFila(Restaurante *restaurante);
#endif