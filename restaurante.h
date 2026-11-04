#include <stdbool.h>

typedef struct Mesa {
    int numero;
    bool ocupada;
    int quantPessoasMesa;
    int comanda;
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

int ocupaMesa(Restaurante *restaurante, int quantidade, int comanda);

void liberaMesa(Restaurante *restaurante);

void chamarGrupo(Restaurante *restaurante);

void desistirFilaEspera(Restaurante *restaurante);

void atualizarFila(Restaurante *restaurante);
