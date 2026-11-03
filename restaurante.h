#include <stdbool.h>

typedef struct Mesa {
    int numero;
    bool ocupada;
    int quantPessoasMesa;
    int comanda;
} Mesa;

typedef struct Grupo {
    int senha;
    int quantPessoasGrupo;
    struct Grupo *prox;
} Grupo;

typedef struct Fila {
    Grupo *inicio;
    Grupo *fim;
    int proxSenha;
} Fila;

typedef struct Prato {
    struct Prato *prox;
} Prato;

typedef struct Pilha {
    Prato *topo;
    int quant;
} Pilha;

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
