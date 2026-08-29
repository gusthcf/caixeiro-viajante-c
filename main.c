#include <stdio.h>
#include "grafoPonderado_tad.h"

int main() {

    GrafoPon grafo;

    // a funcao alocaGrafo e chamada automaticamente dentro da funcao leGrafo
    leGrafo(&grafo);

    // o primeiro parametro int informa a posicaoo atual, o segundo um contador e o terceiro a distancia atual
    encontraCaminho(&grafo, 0, 1, 0);

    //imprime o melhor caminho encontrado e a distancia total
    imprimeCaminho(&grafo);

    desalocarGrafo(&grafo);
    
    return 0;
}