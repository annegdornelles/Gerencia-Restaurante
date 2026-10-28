#include<stdio.h>
#include<stdbool.h>

typedef struct Mesa{
    int numero;
    bool ocupada;
    int quantPessoasMesa;  
    int comanda;  
} Mesa;

typedef struct Fila{
    Grupo *inicio;
    Grupo *fim;
    int proxSenha;
}Fila;

typedef struct Grupo {
    int senha;
    int quantPessoasGrupo;
    struct Grupo *prox;
} Grupo;

typedef struct Prato{
    struct Prato *prox;
} Prato;

typedef struct Pilha{
    Prato *topo;
    int quant;
}Pilha;

struct Restaurante{
    int linhas;
    int colunas;
    Mesa **mesas;
    Fila fila;
    Pilha pilha;
}Restaurante;