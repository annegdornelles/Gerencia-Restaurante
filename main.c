#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

int main(){
    menu();
}

int menu() {
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
                inserirMesas();
                break;

            case 2:
                inserirGrupo();
                break;

            case 3:
                liberaMesa();
                break;

            case 4:
                desistirFilaEspera();
                break;

            case 5:
                inserirPratos();
                break;

            case 6:
                imprimirPilha();
                break;

            case 7:
                imprimirFila();
                break;

            case 8:
                imprimirMesas();
                break;
        }

    } while (opcao != 0);

    return 0;
}