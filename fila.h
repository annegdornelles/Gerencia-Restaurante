#ifndef FILA_H
#define FILA_H

typedef struct Grupo {
    int senha;
    int quantPessoasGrupo;
    struct Grupo *prox;
} Grupo;

typedef struct Fila{
    Grupo *inicio;
    Grupo *fim;
    int proxSenha;
}Fila;

#endif