#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "restaurante.h"
#include "fila.h"
#include "pilha.h"

bool restauranteFechado(Restaurante *restaurante)
{
    if (restaurante->mesas == NULL)
    {
        printf("O restaurante esta fechado. Abra o restaurante primeiro (opcao 1).\n");
        return true;
    }
    return false;
}

int arrumarMesa(Restaurante *restaurante, Mesa *mesa)
{
    if (restaurante->pilha.quant >= 4)
    {
        for (int k = 0; k < 4; k++)
        {
            desempilhar(&restaurante->pilha);
        }
        mesa->quantPratos = 4;
        mesa->quantPratosDisp = 4;
        return 1;
    }

    mesa->quantPratos = 0;
    mesa->quantPratosDisp = 0;
    return 0;
}

void inserirMesas(Restaurante *restaurante)
{
    int i;
    int j;
    int linhas;
    int colunas;

    if (restaurante->mesas != NULL)
    {
        printf("O restaurante ja esta aberto.\n");
        return;
    }

    printf("Insira o numero de linhas: ");
    scanf("%d", &linhas);
    printf("Insira o numero de colunas: ");
    scanf("%d", &colunas);

    if (linhas <= 0 || colunas <= 0)
    {
        printf("Numero de linhas e colunas deve ser maior que zero.\n");
        return;
    }

    restaurante->mesas = (Mesa**)malloc(linhas * sizeof(Mesa*));

    if (restaurante->mesas == NULL)
    {
        printf("Erro ao alocar memoria para as mesas.\n");
        return;
    }

    for (i = 0; i < linhas; i++)
    {
        restaurante->mesas[i] = (Mesa*)malloc(colunas * sizeof(Mesa));

        if (restaurante->mesas[i] == NULL)
        {
            printf("Erro ao alocar memoria para as mesas.\n");

            for (int k = 0; k < i; k++)
            {
                free(restaurante->mesas[k]);
            }
            free(restaurante->mesas);
            restaurante->mesas = NULL;
            return;
        }

        for (j = 0; j < colunas; j++)
        {
            restaurante->mesas[i][j].numero = i * colunas + j + 1;
            restaurante->mesas[i][j].ocupada = false;
            restaurante->mesas[i][j].quantPessoasMesa = 0;
            restaurante->mesas[i][j].comanda = 0;
            restaurante->mesas[i][j].quantPratos = 4;
            restaurante->mesas[i][j].quantPratosDisp = 4;
        }
    }

    restaurante->linhas = linhas;
    restaurante->colunas = colunas;

    inicializarFila(&restaurante->fila);
    inicializarPilha(&restaurante->pilha);

    printf("Seja bem vindo ao restaurante! Estamos abertos!\n");
}

void inserirGrupo(Restaurante *restaurante)
{
    int quantidade;
    int senha;
    int restantes;

    if (restauranteFechado(restaurante))
    {
        return;
    }

    printf("Insira a quantidade de pessoas do grupo: ");
    scanf("%d", &quantidade);

    if (quantidade <= 0)
    {
        printf("Quantidade de pessoas deve ser maior que zero.\n");
        return;
    }

    senha = restaurante->fila.proxSenha;
    restaurante->fila.proxSenha++;

    printf("\nSenha do grupo: %d\n", senha);

    if (restaurante->fila.inicio != NULL)
    {
        inserirFila(&restaurante->fila, senha, quantidade);
        printf("Grupo esta na fila de espera\n");
    }
    else
    {
        restantes = ocuparMesa(restaurante, quantidade, senha);

        if (restantes > 0)
        {
            inserirFila(&restaurante->fila, senha, restantes);
            printf("%d pessoas do grupo estao na fila de espera\n", restantes);
        }
        else
        {
            printf("Grupo foi acomodado no restaurante\n");
        }
    }
}

int ocuparMesa(Restaurante *restaurante, int quantidade, int comanda)
{
    int i;
    int j;
    int restantes = quantidade;

    for (i = 0; i < restaurante->linhas; i++)
    {
        for (j = 0; j < restaurante->colunas; j++)
        {
            Mesa *mesa = &restaurante->mesas[i][j];

            if (mesa->ocupada == false && mesa->quantPratosDisp == 4)
            {
                mesa->ocupada = true;

                if (restantes >= 4)
                {
                    mesa->quantPessoasMesa = 4;
                    restantes = restantes - 4;
                }
                else
                {
                    mesa->quantPessoasMesa = restantes;
                    restantes = 0;
                }

                mesa->comanda = comanda;

                /* pratos que nao serao usados voltam para a pilha */
                int pratosExcedentes = 4 - mesa->quantPessoasMesa;

                for (int k = 0; k < pratosExcedentes; k++)
                {
                    if (empilhar(&restaurante->pilha))
                    {
                        mesa->quantPratos--;
                    }
                }

                printf("Mesa %d ocupada com %d pessoas e comanda %d.\n",
                       mesa->numero, mesa->quantPessoasMesa, mesa->comanda);

                if (restantes == 0)
                {
                    return 0;
                }
            }
        }
    }
    return restantes;
}

void atualizarFila(Restaurante *restaurante)
{
    int restantes;

    while (restaurante->fila.inicio != NULL)
    {
        Grupo *grupo = restaurante->fila.inicio;
        restantes = ocuparMesa(restaurante, grupo->quantPessoasGrupo, grupo->senha);

        if (restantes == 0)
        {
            printf("Grupo com senha %d foi acomodado no restaurante\n", grupo->senha);
            removerFila(&restaurante->fila);
        }
        else
        {
            grupo->quantPessoasGrupo = restantes;
            printf("%d pessoas do grupo com senha %d continuam na fila de espera\n",
                   restantes, grupo->senha);
            break;
        }
    }
}

void chamarGrupo(Restaurante *restaurante)
{
    if (restaurante->fila.inicio == NULL)
    {
        printf("Nao existem grupos esperando.\n");
        return;
    }

    atualizarFila(restaurante);
}

void liberarMesa(Restaurante *restaurante)
{
    int numero;
    int i;
    int j;

    if (restauranteFechado(restaurante))
    {
        return;
    }

    printf("Numero da mesa que sera liberada: ");
    scanf("%d", &numero);

    for (i = 0; i < restaurante->linhas; i++)
    {
        for (j = 0; j < restaurante->colunas; j++)
        {
            Mesa *mesa = &restaurante->mesas[i][j];

            if (mesa->numero == numero)
            {
                if (mesa->ocupada == false)
                {
                    printf("Essa mesa ja esta livre.\n");
                    return;
                }

                mesa->ocupada = false;
                mesa->quantPessoasMesa = 0;
                mesa->comanda = 0;

                if (arrumarMesa(restaurante, mesa))
                {
                    printf("Mesa arrumada\n");
                }
                else
                {
                    printf("Nao ha pratos suficientes para arrumar a mesa\n");
                }

                printf("Mesa %d liberada\n", numero);

                chamarGrupo(restaurante);
                return;
            }
        }
    }

    printf("Mesa nao encontrada\n");
}

void desistirFilaEspera(Restaurante *restaurante)
{
    int senha;

    if (restauranteFechado(restaurante))
    {
        return;
    }

    printf("Senha do grupo que deseja desistir: ");
    scanf("%d", &senha);

    if (removerGrupo(&restaurante->fila, senha))
    {
        printf("Grupo removido da fila\n");
        atualizarFila(restaurante);
    }
    else
    {
        printf("Grupo nao encontrado na fila\n");
    }
}

/* repoe pratos, arruma as mesas livres que estavam sem pratos e chama a fila */
void reporPratos(Restaurante *restaurante)
{
    int i;
    int j;

    if (restauranteFechado(restaurante))
    {
        return;
    }

    inserirPratos(&restaurante->pilha);

    for (i = 0; i < restaurante->linhas; i++)
    {
        for (j = 0; j < restaurante->colunas; j++)
        {
            Mesa *mesa = &restaurante->mesas[i][j];

            if (mesa->ocupada == false && mesa->quantPratosDisp != 4)
            {
                if (arrumarMesa(restaurante, mesa))
                {
                    printf("Mesa %d arrumada\n", mesa->numero);
                }
            }
        }
    }

    if (restaurante->fila.inicio != NULL)
    {
        atualizarFila(restaurante);
    }
}

void imprimirMesas(Restaurante *restaurante)
{
    int i;
    int j;

    if (restauranteFechado(restaurante))
    {
        return;
    }

    for (i = 0; i < restaurante->linhas; i++)
    {
        for (j = 0; j < restaurante->colunas; j++)
        {
            Mesa *mesa = &restaurante->mesas[i][j];

            printf("Mesa %d: ", mesa->numero);

            if (mesa->ocupada)
            {
                printf("ocupada | %d pessoas | comanda %d", mesa->quantPessoasMesa, mesa->comanda);
            }
            else if (mesa->quantPratosDisp == 4)
            {
                printf("livre e arrumada");
            }
            else
            {
                printf("livre e sem pratos");
            }

            printf(" | pratos na mesa: %d\n", mesa->quantPratos);
        }
    }
}

void fecharRestaurante(Restaurante *restaurante)
{
    if (restaurante->mesas != NULL)
    {
        for (int i = 0; i < restaurante->linhas; i++)
        {
            free(restaurante->mesas[i]);
        }
        free(restaurante->mesas);
        restaurante->mesas = NULL;
        esvaziarFila(&restaurante->fila);
        esvaziarPilha(&restaurante->pilha);
    }
}