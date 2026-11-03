#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Mesa {
    int numero;
    bool ocupada;
    int quantPessoasMesa;
    int comanda;
} Mesa;

typedef struct Grupo {
    int senha;
    int quantPessoasGrupo;
    struct Grupo *prox;
} Grupo;

typedef struct Fila {
    Grupo *inicio;
    Grupo *fim;
    int proxSenha;
} Fila;

typedef struct Prato {
    struct Prato *prox;
} Prato;

typedef struct Pilha {
    Prato *topo;
    int quant;
} Pilha;

typedef struct Restaurante {
    int linhas;
    int colunas;
    Mesa **mesas;
    Fila fila;
    Pilha pilha;
} Restaurante;

/*FUNCOES QUE FICAM AQUI:
inserirMesas();
inserirGrupo();
ocupaMesa();
liberaMesa();
chamarGrupo();
desistirFilaEspera();
atualizarFila();
*/