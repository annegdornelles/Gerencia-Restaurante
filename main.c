#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

int main(){
    menu();
}

int menu(){
    //FUNCOES:
    inserirMesas();//o usuario informa linha e coluna
    inserirGrupo();//designa senha e caso necessario coloca na fila de espera. mas primeiro insere a quant de pessoas no grupo
    //MEXE COM A FILA DE ESPERA:
    ocupaMesa();//chamarGrupo() - ve se ele é separado ou nao. () e chama a mesa de acordo com a quantidade de pessoas do grupo
    liberaMesa();//a mesa é liberada e o grupo que estava na fila de espera é chamado para ocupar a mesa. tem que ter uma funcao para ATUALIZAR isso tbm
    desistirFilaEspera();
    //MEXE COM A PILHA DE PRATOS:
    retirarPratos();
    inserirPratos();//mexe com pratos excedentes tambem e ajusta de acordo com a quantidade de pessoas
    //IMPRESSAO:
    imprimirPilha();
    imprimirFila();//imprimir grupos na fila de espera
    imprimirMesas();//imprimir mesas ocupadas e livres

    //VER A QUESTAO DOS NÓS

}