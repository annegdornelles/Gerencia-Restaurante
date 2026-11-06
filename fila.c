/*
FUNCOES QUE FICAM AQUI:
inicializaFila();
insereFila();
removeFila();
imprimirFila();
desistirFilaEspera();
*/

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void inicializaFila(Fila *fila){
    fila->inicio=NULL;
    fila->fim=NULL;
    fila->proxSenha = 1;
}

void insereFila(Fila *fila, int senha, int qtd){
    Grupo *p = (Grupo*)malloc(sizeof(Grupo));//aloca novo grupo
    if(p==NULL){
        printf("erro ao alocar\n");
        return;
    }
    p->senha = senha;
    p->quantPessoasGrupo = qtd;
    p->prox= NULL;
    
    if(fila->inicio == NULL){
        fila->inicio = p;
        fila->fim = p;
    }
    else{
        fila->fim->prox = p;
        fila->fim = p;
    }
}
void removeFila(Fila *fila){
    if(fila->inicio==NULL){
        return;
    }
    Grupo *aux = fila->inicio;
    fila->inicio = aux->prox;

    if(fila->inicio==NULL){
        fila->fim = NULL;
    }
    free(aux);
}

void imprimirFila(Fila *fila){
    Grupo *aux = fila->inicio;
    int grupos = 0;
    int pessoas = 0;
    if(aux == NULL){
        printf("Nao existem grupos esperando\n");
        return;
    }
    while(aux !=NULL){
        grupos++;
        pessoas = pessoas + aux->quantPessoasGrupo;
        printf("Grupo %d aguarda por %d lugares\n", aux->senha, aux->quantPessoasGrupo);
        aux = aux->prox;
    }
    printf("Total de grupos esperando: %d\n", grupos);
    printf("Total de pessoas esperando: %d\n", pessoas);

}
int desistirFilaEspera(Fila *fila, int senha){
    Grupo *aux = fila->inicio;
    Grupo *ant =NULL;
    while(aux !=NULL){
        if(aux->senha==senha){
            if(ant==NULL){
                fila->inicio = aux->prox;
            }
            else{
                ant->prox = aux->prox;
            }

            if(aux==fila->fim){
                fila->fim = ant;
            }
            free(aux);
            return 1;
        }
        ant = aux;
        aux = aux->prox;
    }
    return 0;
}

