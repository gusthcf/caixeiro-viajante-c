# TP1 — Problema do Caixeiro Viajante

> **Trabalho acadêmico desenvolvido durante o 2º período da graduação em Ciência da Computação (UFOP), no semestre 2023/2.**

Implementação em C de uma solução **exata e recursiva** (backtracking) para o **Problema do Caixeiro Viajante** (*Travelling Salesman Problem* — TSP), construída sobre um Tipo Abstrato de Dados (TAD) de grafo ponderado representado por matriz de adjacências.

---

## Contexto acadêmico

| | |
|---|---|
| **Disciplina** | BCC202 — Estruturas de Dados I |
| **Período** | **2º período** da graduação — semestre 2023/2 |
| **Instituição** | Departamento de Computação (DECOM) — Universidade Federal de Ouro Preto (UFOP) |
| **Professor** | Pedro Silva |
| **Trabalho** | Trabalho Prático I (TP1) |
| **Autores** | Gustavo Ferreira e Marcelo Vieira |

> Este repositório é um **arquivo histórico** do trabalho entregue na época. O código-fonte foi preservado exatamente como submetido, sem refatorações posteriores.

---

## O problema

Dado um conjunto de `n` cidades e as distâncias entre todas as duplas possíveis, o caixeiro viajante precisa percorrer **todas as cidades exatamente uma vez** e **retornar à cidade de origem** (sempre a cidade `0`), de forma que a **distância total percorrida seja a menor possível**.

Como exigido pelo enunciado, a busca é feita por meio de uma **função recursiva**, sem uso de bibliotecas externas — apenas a biblioteca padrão da GNU.

---

## Estrutura do repositório

```
.
├── main.c                  # Ponto de entrada: apenas orquestra as chamadas ao TAD
├── grafoPonderado_tad.h    # Interface do TAD GrafoPonderado
├── grafoPonderado_tad.c    # Implementação do TAD e do algoritmo de busca
├── Makefile                # Automação da compilação
├── casos-de-teste/         # Caso de teste de exemplo (entrada e saída esperada)
├── main.tex                # Fonte LaTeX do relatório
├── Relatório_TP1.pdf       # Relatório final entregue
└── TP.pdf                  # Enunciado original do trabalho
```

---

## O TAD `GrafoPon`

```c
typedef struct grafoPon {
    int numCidades;          // numero de cidades totais
    int **matrizAdjacencias; // matriz que armazena as distancias entre cada cidade
    int *cidadeVisitada;     // vetor de 0 e 1 que nos diz se uma cidade foi visitada ou nao
    int *caminho;            // vetor que armazena o melhor caminho pro dado grafo
    int *caminhoTemp;        // vetor que armazena os caminhos em tempo de teste
    int distancia;           // inteiro que armazena a melhor distancia encontrada
} GrafoPon;
```

Operações implementadas (exigidas pelo enunciado):

| Função | Responsabilidade |
|---|---|
| `alocarGrafo` | Aloca dinamicamente a matriz de adjacências e os vetores auxiliares |
| `desalocarGrafo` | Libera toda a memória alocada |
| `leGrafo` | Inicializa o TAD a partir dos dados lidos do terminal |
| `encontraCaminho` | Função **recursiva** que encontra o menor caminho no grafo |
| `imprimeCaminho` | Imprime o menor caminho e a distância total percorrida |

Na matriz de adjacências, `matrizAdjacencias[i][j]` guarda a distância da cidade de origem `i` até a cidade de destino `j`. O valor `0` indica que **não existe** ligação entre as duas cidades.

---

## Compilação e execução

### Usando o Makefile

```bash
make          # compila e gera o executável ./exe
make run      # executa o programa
```

### Compilando manualmente

Diretivas equivalentes às usadas na correção da disciplina:

```bash
gcc -c grafoPonderado_tad.c -Wall
gcc -c main.c -Wall
gcc grafoPonderado_tad.o main.o -o exe -lm
```

### Executando com um arquivo de entrada

```bash
./exe < casos-de-teste/caso1.in
```

---

## Formato de entrada

1. A primeira linha contém `n`, o número de cidades.
2. Em seguida, `n × n` linhas no formato `origem destino distancia`.

## Formato de saída

1. Primeira linha: a sequência de cidades do menor caminho, começando e terminando na cidade `0` (com um espaço após cada número de cidade).
2. Segunda linha: a distância total percorrida.

### Exemplo

<table>
<tr><th>Entrada</th><th>Saída</th></tr>
<tr><td>

```
4
0 0 0
0 1 30
0 2 0
0 3 10
1 0 30
1 1 0
1 2 15
1 3 35
2 0 0
2 1 15
2 2 0
2 3 25
3 0 10
3 1 35
3 2 25
3 3 0
```

</td><td>

```
0 1 2 3 0
80
```

</td></tr>
</table>

O caminho `0 → 1 → 2 → 3 → 0` custa `30 + 15 + 25 + 10 = 80`, sendo o menor ciclo válido para essa entrada.

---

## Testes e validação

- O programa foi testado com as 5 entradas fornecidas pela disciplina (com 4, 6, 4, 5 e 5 cidades), incluindo casos em que **não há ligação** entre determinadas cidades.
- A ausência de vazamentos de memória foi verificada com **Valgrind**:

```bash
gcc -g -o exe main.c grafoPonderado_tad.c -Wall
valgrind --leak-check=full -s ./exe < casos-de-teste/caso1.in
```

---

## Sobre a complexidade

A solução é uma busca exaustiva com backtracking: ela explora todas as permutações possíveis de cidades a partir da cidade `0`, o que resulta em complexidade de tempo **O(n!)**. Isso é adequado para as entradas pequenas propostas pelo trabalho, mas cresce rapidamente com o número de cidades — característica esperada de uma solução exata para o TSP.

---

## Aprendizados

O trabalho consolidou, ainda no segundo período do curso, conceitos fundamentais de Estruturas de Dados:

- Alocação dinâmica de memória (vetores e matrizes) e sua liberação correta;
- Modularização com separação entre interface (`.h`) e implementação (`.c`);
- Construção e uso de Tipos Abstratos de Dados;
- Recursão com backtracking;
- Depuração e análise dinâmica de código com Valgrind.

---

## Licença

Distribuído sob a licença MIT. Veja [LICENSE](LICENSE) para mais detalhes.
