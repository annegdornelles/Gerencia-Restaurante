

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

void inicializarPilha(Pilha *pilha)
{
    pilha->topo = NULL;
    pilha->quant = 0;
}

/* retorna 1 se empilhou e 0 se nao conseguiu alocar */
int empilhar(Pilha *pilha)
{
    Prato *novoPrato = (Prato*)malloc(sizeof(Prato));

    if (novoPrato == NULL)
    {
        printf("Erro ao alocar memoria para o novo prato.\n");
        return 0;
    }

    novoPrato->prox = pilha->topo;
    pilha->topo = novoPrato;
    pilha->quant++;
    return 1;
}

void desempilhar(Pilha *pilha)
{
    if (pilha->topo == NULL)
    {
        printf("\nNao ha pratos na pilha\n");
        return;
    }

    Prato *aux = pilha->topo;
    pilha->topo = aux->prox;
    free(aux);
    pilha->quant--;
}

void imprimirPilha(Pilha *pilha)
{
    Prato *aux = pilha->topo;

    if (aux == NULL)
    {
        printf("\nNao ha pratos na pilha\n");
        return;
    }

    printf("\nPratos na pilha:\n");

    while (aux != NULL)
    {
        printf("Prato\n");
        aux = aux->prox;
    }

    printf("Quantidade de pratos na pilha: %d\n", pilha->quant);
}

void inserirPratos(Pilha *pilha)
{
    int qtd;

    printf("Quantos pratos quer adicionar?\n");

    if (scanf("%d", &qtd) != 1 || qtd <= 0)
    {
        printf("Quantidade invalida\n");
        while (getchar() != '\n')
        {
        }
        return;
    }

    for (int i = 0; i < qtd; i++)
    {
        empilhar(pilha);
    }
    printf("%d pratos adicionados na pilha\n", qtd);
}

void esvaziarPilha(Pilha *pilha)
{
    while (pilha->topo != NULL)
    {
        desempilhar(pilha);
    }
}