#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include "restaurante.h"
#include "fila.h"
#include "pilha.h"

int main(){
    Restaurante restaurante = {0};
    menu(&restaurante);
}

int menu(Restaurante *restaurante) {
    int opcao;

    do {
        printf("\n===== RESTAURANTE =====\n");
        printf("1 - Abrir restaurante\n");
        printf("2 - Chegada de grupo\n");
        printf("3 - Liberar mesa\n");
        printf("4 - Desistir da fila de espera\n");
        printf("5 - Repor pratos\n");
        printf("6 - Imprimir pilha de pratos\n");
        printf("7 - Imprimir fila de espera\n");
        printf("8 - Imprimir mesas\n");
        printf("0 - Sair\n");

        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirMesas(restaurante);
                break;

            case 2:
                inserirGrupo(restaurante);
                break;

            case 3:
                liberaMesa(restaurante);
                break;

            case 4:
                desistirFilaEspera(restaurante);
                break;

            case 5:
                inserirPratos(&restaurante->pilha);
                break;

            case 6:
                imprimirPilha(&restaurante->pilha);
                break;

            case 7:
                imprimirFila(&restaurante->fila);
                break;

            case 8:
                imprimirMesas(restaurante);
                break;

            case 0:
                printf("Encerrando programa...\n");
                break;

            default:
                printf("Opcao invalida\n");
        }

    } while (opcao != 0);

    return 0;
}