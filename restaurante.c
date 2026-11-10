#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "restaurante.h"
#include "fila.h"
#include "pilha.h"

/*FUNCOES QUE FICAM AQUI:
inserirMesas();
inserirGrupo();
ocupaMesa();
liberaMesa();
chamarGrupo();
desistirFilaEspera();
atualizarFila();
*/

void inserirMesas(Restaurante *restaurante){
    int i,j;

    printf("Insira o numero de linhas:");
    scanf("%d", &restaurante->linhas);
    printf("Insira o numero de colunas:");
    scanf("%d", &restaurante->colunas);

    if (restaurante->linhas <= 0 || restaurante->colunas <= 0) {
        printf("Numero de linhas e colunas deve ser maior que zero.\n");
        return;
    }

    restaurante->mesas=(Mesa**)malloc(restaurante->linhas * sizeof(Mesa*));

    if (restaurante->mesas == NULL) {
        printf("Erro ao alocar memoria para as mesas.\n");
        return;
    }

    for (i=0;i<restaurante->linhas;i++){
        restaurante->mesas[i]=(Mesa*)malloc(restaurante->colunas * sizeof(Mesa));

        if (restaurante->mesas[i] == NULL) {
            printf("Erro ao alocar memoria para as mesas.\n");

            for (int k = 0; k < i; k++) {
                free(restaurante->mesas[k]);
            }
            free(restaurante->mesas);
            restaurante->mesas = NULL;
            return;
        }

        for (j=0;j<restaurante->colunas;j++){
            restaurante->mesas[i][j].numero = i * restaurante->colunas + j + 1;
            restaurante->mesas[i][j].ocupada = false;
            restaurante->mesas[i][j].quantPessoasMesa = 0;
            restaurante->mesas[i][j].comanda = 0;
            restaurante->mesas[i][j].quantPratos = 4;
             restaurante->mesas[i][j].quantPratosDisp = 4;
        }
    }

    inicializarFila(&restaurante->fila);
    inicializarPilha(&restaurante->pilha);

    printf("Seja bem vindo ao restaurante! Estamos abertos!\n");
}

void inserirGrupo(Restaurante *restaurante){
    int quantidade;
    int senha;
    int restantes;

    printf("Insira a quantidade de pessoas do grupo: ");
    scanf("%d", &quantidade);

    if (quantidade <= 0) {
        printf("Quantidade de pessoas deve ser maior que zero.\n");
        return;
    }

    senha = restaurante->fila.proxSenha;
    restaurante->fila.proxSenha++;

    printf("\n Senha do grupo:%d\n", senha);

    if(restaurante->fila.inicio!=NULL){
        inserirFila(&restaurante->fila,senha,quantidade);
        printf("\n Grupo esta na fila de espera");
    }
    else {
        restantes = ocuparMesa(restaurante, quantidade, senha);
        if (restantes > 0) {
            inserirFila(&restaurante->fila, senha, restantes);
            printf("\n %d pessoas do grupo estao na fila de espera", restantes);
        }
        else {
            printf("\n Grupo foi acomodado no restaurante");
        }
    }
}

int ocuparMesa(Restaurante *restaurante, int quantidade, int comanda){
    int i,j;
    int restantes = quantidade;

    for (i=0;i<restaurante->linhas;i++){
        for (j=0;j<restaurante->colunas;j++){
            if(restaurante->mesas[i][j].ocupada == false && restaurante->mesas[i][j].quantPratosDisp==4){ //adicionei essa verif 
                restaurante->mesas[i][j].ocupada = true;
                if(restantes>=4){
                    restaurante->mesas[i][j].quantPessoasMesa = 4;
                    restantes = restantes - 4;
                }
                else {
                    restaurante->mesas[i][j].quantPessoasMesa = restantes;
                    restantes = 0;
                }

                restaurante->mesas[i][j].comanda = comanda;
                int pratosExcedentes = 4 - restaurante->mesas[i][j].quantPessoasMesa;

                for(int k = 0; k < pratosExcedentes; k++){
                    if(empilhar(&restaurante->pilha)){
                        restaurante->mesas[i][j].quantPratos--;
                    }
                }

                printf("Mesa %d ocupada com %d pessoas e comanda %d.\n", restaurante->mesas[i][j].numero, restaurante->mesas[i][j].quantPessoasMesa, restaurante->mesas[i][j].comanda);

                if (restantes == 0) {
                    return 0; // Todas as pessoas foram acomodadas
                }
            }
        }
    }
    return restantes;
}

void atualizarFila(Restaurante *restaurante){
    int restantes;

    while(restaurante->fila.inicio!=NULL){
        Grupo *grupo = restaurante->fila.inicio;
        restantes = ocuparMesa(restaurante, grupo->quantPessoasGrupo, grupo->senha);

        if (restantes == 0){
            printf("\n Grupo com senha %d foi acomodado no restaurante", grupo->senha);
            removerFila(&restaurante->fila);
        }
        else {
            grupo->quantPessoasGrupo = restantes;
            printf("\n %d pessoas do grupo com senha %d estao na fila de espera", restantes, grupo->senha);
            break;
        }

    }
}

void chamarGrupo(Restaurante *restaurante) {

    if (restaurante->fila.inicio == NULL) {
        printf("Nao existem grupos esperando.\n");
        return;
    }

    atualizarFila(restaurante);
}

void liberarMesa(Restaurante *restaurante){
    int numero;
    int i, j;
    int encontrou = 0;

    printf("Numero da mesa que sera liberada: ");
    scanf("%d", &numero);

    for (i = 0; i < restaurante->linhas; i++) {

        for (j = 0; j < restaurante->colunas; j++) {

            if (restaurante->mesas[i][j].numero == numero) {

                encontrou = 1;

                if (restaurante->mesas[i][j].ocupada == false) {
                    printf("Essa mesa ja esta livre.\n");
                    return;
                }

                restaurante->mesas[i][j].ocupada = false;
                restaurante->mesas[i][j].quantPessoasMesa = 0;
                restaurante->mesas[i][j].comanda = 0;
                if(restaurante->pilha.quant >= 4){
                    for(int k = 0; k < 4; k++){
                        desempilhar(&restaurante->pilha);
                    }
                    restaurante->mesas[i][j].quantPratos = 4;
                    printf("Mesa arrumada\n");
                }
                else{
                    restaurante->mesas[i][j].quantPratos = 0;
                    printf("Nao ha pratos suficientes\n");
                }

                printf("Mesa %d liberada\n", numero);

                chamarGrupo(restaurante);

                return;
            }
        }
    }

    if (encontrou == 0) {
        printf("Mesa nao encontrada\n");
    }
}

void desistirFilaEspera(Restaurante *restaurante) {

    int senha;

    printf("Senha do grupo que deseja desistir: ");
    scanf("%d", &senha);

    if (removerGrupo(&restaurante->fila, senha)) {
        printf("Grupo removido da fila\n");
        atualizarFila(restaurante);
    } 
    else {
        printf("Grupo nao encontrado na fila\n");
    }
}