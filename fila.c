/*
FUNCOES QUE FICAM AQUI:
inicializaFila();
insereFila();
removeFila();
imprimirFila();
desistirFilaEspera();
*/


#include<stdio.h>
#include<stdlib.h>
#include "fila.h";

void inicializaFila(Fila *fila){
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->proxSenha = 0;
}

void inserirFila(Fila *fila, int senha, int quantidade){
    Grupo *novo = (Grupo*)malloc(sizeof(Grupo));

    if(novo == NULL){
        printf("Erro ao alocar memoria para o novo grupo.\n");
        return;
    }

    novo->senha = senha;
    novo->quantPessoasGrupo = quantidade;
    novo->prox = NULL;

    if (fila->inicio==NULL){
        fila->inicio =  novo;
        fila->fim = novo;
    }
    else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }

}

void removerFila(Fila *fila){
    if (fila->inicio == NULL){
        printf("\n A fila esta vazia");
        return;
    }

    Grupo *aux = fila->inicio;
    fila->inicio = aux->prox;

    if(fila->inicio == NULL){
        fila->fim = NULL;
    }

    free(aux);
}

int removerGrupo(Fila *fila, int senha){
    Grupo *atual = fila->inicio;
    Grupo *ant = NULL;

    while(atual!=NULL){
        if(atual->senha == senha){
            if(ant == NULL){
                fila->inicio =  atual->prox;
            }
            else{
                ant->prox = atual->prox;        
            }

            if (atual == fila->fim){
                fila->fim = ant;
            }
            free(atual);
            return 1;
        }
        ant = atual;
        atual = atual->prox;
    }
    return 0;
}