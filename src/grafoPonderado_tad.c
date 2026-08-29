#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "grafoPonderado_tad.h"

// funcao que aloca memoria para os atributos do grafo que necessitam de alocacao
void alocarGrafo(GrafoPon *grafo)
{
    // aloca espaco para os vetores de caminho e caminhoTemp
    grafo->caminho = malloc(sizeof(int) * (grafo->numCidades + 1));
    grafo->caminhoTemp = malloc(sizeof(int) * (grafo->numCidades + 1));

    // aloca espaco pro vetor que armazena quais cidades foram visitadas
    grafo->cidadeVisitada = malloc(sizeof(int) * grafo->numCidades);

    // inicializa o vetor de cidades visitadas com 0, pois nenhuma cidade foi visitada ainda
    // inicializa o vetor de caminhos com -1, que serao substituidos posteriormente pelos numeros das cidades
    for (int i = 0; i < grafo->numCidades; i++)
    {
        grafo->cidadeVisitada[i] = 0;
        grafo->caminho[i] = -1;
        grafo->caminhoTemp[i] = -1;
    }

    // a primeira cidade (0) e marcada como visitada, pois começamos por ela, assim como o indice 0 do caminho sempre sera a cidade 0
    grafo->cidadeVisitada[0] = 1;
    grafo->caminhoTemp[0] = 0;
    // considera a distancia como maxima
    grafo->distancia = INT_MAX;

    /*
    alocacao da matriz n*n para armazenar as distancias entre as cidades, sendo armazenados no seguinte padrao:
    considere a matriz[i][j].
    i: cidade de origem
    j: cidade de destino
    matriz[i][j]: distancia entre essas 2 cidades
    */
    grafo->matrizAdjacencias = malloc(grafo->numCidades * sizeof(int *));
    for (int i = 0; i < grafo->numCidades; i++)
        grafo->matrizAdjacencias[i] = malloc(grafo->numCidades * sizeof(int));
}

// funcao que desaloca tudo o que estiver sendo alocado dinamicamente
void desalocarGrafo(GrafoPon *grafo)
{
    // libera matriz de distancias
    for (int i = 0; i < grafo->numCidades; i++)
    {
        free(grafo->matrizAdjacencias[i]);
    }
    free(grafo->matrizAdjacencias);

    // libera vetores de caminho e vetor que armazena as cidades visitadas
    free(grafo->caminho);
    free(grafo->caminhoTemp);
    free(grafo->cidadeVisitada);
}

// funcao que chama a funcapo alocarGrafo e armazena as distancias entre as cidades
void leGrafo(GrafoPon *grafo)
{
    // variaveis locais para preenchimento dos atributos do grafo
    int cidadeOrigem, cidadeDestino, distancia;

    // le e armazena o numero de cidades
    scanf("%d", &(grafo->numCidades));

    // chama a funcao que aloca espaço para todos os atributos que necessitam alocação dinamica
    alocarGrafo(grafo);

    // le e armazena a distancia entre cada cidade, preenchendo a matriz "matrizAdjacencias" conforme o padrao descrito nos comentarios da funcao "alocaGrafo"
    for (int i = 0; i < grafo->numCidades; i++)
        for (int j = 0; j < grafo->numCidades; j++)
        {
            scanf("%d%d%d", &cidadeOrigem, &cidadeDestino, &distancia);
            grafo->matrizAdjacencias[cidadeOrigem][cidadeDestino] = distancia;
        }
}

// funcao recursiva que encontra o menor caminho possivel entre as cidades
// posicao informa a cidade atual que estamos visitando, começa em 0 pois partimos dela
// contador ira contar o numero de cidades visitadas, começa em 1 pois javisitamos a cidade 0
// distanciaTemp armazena a distancia do caminho atual, que começa em 0 pois ainda nao andamos ate a cidade seguinte
void encontraCaminho(GrafoPon *grafo, int posicao, int contador, int distanciaTemp)
{
    // aqui a funcao confere se todas as cidades ja foram visitadas e se a distancia entre a cidade atual e a próxima é diferente de 0
    if ((contador == grafo->numCidades) && (grafo->matrizAdjacencias[posicao][0]))
    {
        // caso sim, a distancia total do ciclo e calculada
        distanciaTemp += grafo->matrizAdjacencias[posicao][0];
        // caso a distancia desse ciclo seja menor que a menor distancia encontrada ate agora, a melhor distancia e atualizada
        // o vetor que armazena o melhor caminho tambem e atualizado para receber o vetor que armazena o caminho temporario
        if (distanciaTemp < grafo->distancia)
        {
            grafo->distancia = distanciaTemp;
            for (int k = 0; k < grafo->numCidades; k++)
                grafo->caminho[k] = grafo->caminhoTemp[k];
        }
        return;
    }
    // o laço for ira iterar sobre todas as cidades
    for (int i = 0; i < grafo->numCidades; i++)
    {
        /*
        caso a cidade da iteracao nao tenha sido visitada e haja uma distancia diferente de 0 entre ela e a cidade atual,
        a cidade da iteracao e visitada e seu número e inserido no vetor que armazena o caminho temporario
        a funcao e chamada novamente para que a proxima cidade seja visitada, com novos parametros:
        - posicap recebe o numero da iteracao, que representa a proxima cidade a ser visitada
        - o contador e incrementado, pois acabamos de visitar uma cidade
        - a distanciaTemp e somada com a distância entre a cidade atual e a cidade da iteracao
        */
        if (grafo->cidadeVisitada[i] == 0 && grafo->matrizAdjacencias[posicao][i])
        {
            grafo->cidadeVisitada[i] = 1;
            grafo->caminhoTemp[contador] = i;
            encontraCaminho(grafo, i, contador + 1, distanciaTemp + grafo->matrizAdjacencias[posicao][i]);
            // apos a chamada recursiva a cidade deve ser marcada como nao visitada novamente, para que as proximas iteracoes possam ser feitas
            grafo->cidadeVisitada[i] = 0;
        }
    }
}

// funcao que imprime a ordem do menor caminho e a menor distancia
void imprimeCaminho(GrafoPon *grafo)
{
    // imprime numa primeira linha o menor caminho a ser percorrido
    for (int i = 0; i < grafo->numCidades; i++)
    {
        printf("%d ", grafo->caminho[i]);
    }
    printf("0");
    // imprime numa segunda linha a distancia percorrida por esse menor caminho
    printf("\n%d\n", grafo->distancia);
}
