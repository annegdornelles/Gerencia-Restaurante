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

inicializaFila(Fila *fila);
insereFila(Fila *fila, int senha, int qtd);
removeFila(Fila *fila);
imprimirFila(Fila *fila);
desistirFilaEspera(Fila *fila, int senha);
#endif