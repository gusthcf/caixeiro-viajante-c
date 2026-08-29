#ifndef grafoPonderado_tad_h
#define grafoPonderado_tad_h
#include <stdio.h>

typedef struct grafoPon {
    int numCidades; //numero de cidades totais
    int **matrizAdjacencias; //matriz que armazena as distancias entre cada cidade
    int *cidadeVisitada; //vetor de 0 e 1 que nos diz se uma cidade foi visitada ou nao
    int *caminho; //vetor que armazena o melhor caminho pro dado grafo, uma vez que calculado
    int *caminhoTemp; //vetor que armazena os caminhos em tempo de teste
    int distancia; //inteiro que armazena a melhor distancia encontrada
} GrafoPon;


void alocarGrafo(GrafoPon*);

void desalocarGrafo(GrafoPon*);

void leGrafo(GrafoPon*);

void encontraCaminho(GrafoPon*, int, int, int);

void imprimeCaminho(GrafoPon*);

#endif /* grafoPonderado_tad_h */