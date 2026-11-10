/*
FUNCOES Q FICAM AQ:
inicializarPilha();
empilha();
desempilha();
inserirPratos();
imprimirPilha();
*/

#include<stdio.h>
#include<stdlib.h>
#include "pilha.h";

void inicializarPilha(Pilha *pilha){
    pilha->topo = NULL;
    pilha->quant = 0;
}

bool empilhar(Pilha *pilha){
    Prato *novoPrato = (Prato*)malloc(sizeof(Prato));
    if(novoPrato == NULL){
        printf("Erro ao alocar memoria para o novo prato.\n");
        return false;
    }

    novoPrato->prox = pilha->topo;
    pilha->topo = novoPrato;
    pilha->quant++;
    return true;
}

void desempilhar(Pilha *pilha){
    if(pilha->topo == NULL){
        printf("\n Nao ha pratos na pilha\n");
        return;
    }

    Prato *aux = pilha->topo;
    pilha->topo = aux->prox;
    free(aux);
    pilha->quant--;
}

void imprimirPilha(Pilha *pilha){
    Prato *aux = pilha->topo;

    if(aux == NULL){
        printf("\n Nao ha pratos na pilha\n");
        return;
    }

    printf("\n Pratos na pilha:\n");

    while(aux != NULL){
        printf("Prato\n");
        aux = aux->prox;
    }

    printf("Quantidade de pratos na pilha: %d\n", pilha->quant);
}

void inserirPratos(Pilha *pilha){
    int qtd;
    printf("Quantos pratos quer adicionar?\n");
    scanf(" %d", &qtd);
    
    for(int i=0; i<qtd; i++){
        empilhar(pilha);
    }
    printf("%d pratos adicionados na pilha\n", qtd);
}