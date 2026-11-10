#ifndef FILA_H
#define FILA_H

typedef struct Grupo
{
    int senha;
    int quantPessoasGrupo;
    struct Grupo *prox;
} Grupo;

typedef struct Fila
{
    Grupo *inicio;
    Grupo *fim;
    int proxSenha;
} Fila;

void inicializarFila(Fila *fila);
void inserirFila(Fila *fila, int senha, int qtd);
void removerFila(Fila *fila);
void imprimirFila(Fila *fila);
int removerGrupo(Fila *fila, int senha);
void esvaziarFila(Fila *fila);

#endif