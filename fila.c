/*
FUNCOES QUE FICAM AQUI:
inicializaFila();
insereFila();
removeFila();
imprimirFila();
desistirFilaEspera();
*/

<<<<<<< HEAD

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
=======
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

>>>>>>> cfebb15 (funcoes de fila.c implementadas)
