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

void inicializaFila(Fila *fila);
void insereFila(Fila *fila, int senha, int qtd);
void removeFila(Fila *fila);
void imprimirFila(Fila *fila);
int desistirFilaEspera(Fila *fila, int senha);
#endif