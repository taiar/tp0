#ifndef __vocabulario__
#define __vocabulario__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "util.h"

/**
 * Estrutura criada para criação de um vetor de Keywords para fins de ordenação.
 */
typedef struct
{
  char termo[50];
  unsigned int ocorrencias;
} Keyword;

/**
 * Funções utilizadas pelo método qsort
 */
//typedef int (*cmp)(Keyword*, Keyword*);
int keywordCompare(const void*, const void*);

//=============================================================================
// LISTA
//=============================================================================
typedef struct listapal *pLista;

typedef struct
{
  int tamanho;
  pLista primeiro, ultimo;
} Lista;

typedef struct listapal
{
  int texto;
  int quantidade;
  pLista prox;
} listaCelula;

typedef struct
{
  int texto;
  int quantidade;
} VecCelula;

void listaInicia(Lista*);
int  listaVazia(Lista*);
void listaInsere(Lista*, int);
void listaDestroi(Lista*);
void listaRetiraUltimo(Lista*);

//=============================================================================
// ÁRVORE BINÁRIA
//=============================================================================

typedef struct no *pNo;

/**
 * Estrutura de cada nó da árvore binária.
 */
typedef struct no
{
  char termo[50];     // termo a ser armazenado em cada nó
  Lista ocorrencias;  // lista de ocorrências do termo
  pNo esq, dir;       // nós filhos
} No;

typedef pNo Dicionario;

/**
 * Esta variável estática é utilizada no método indiceParaVetor e foi necessária
 * para que eu pudesse acessar corretamente o índice do vetor de Keywords a ser
 * preenchido nesse método.
 */
static unsigned int indiceParaVetorCounter;

void dicionarioInicia(pNo*);
void dicionarioInsere(pNo*, char*, int, unsigned int*, int*);
void dicionarioCaminhoCentral(pNo*, FILE*);
void dicionarioImprimeSaida(pNo*, FILE*);
pNo* dicionarioBuscaTermo(pNo*, char*);
void dicionarioImprime(pNo*, int);
int dicionarioBuscaOcorrenciasTermo(pNo*, char*);

/**
 * Utiliza a estrutura da árvore binária para construir um índice geral de todos
 * os textos que estão sendo analisados pelo programa.
 */
void indiceConstroi(pNo*, Entrada*, unsigned int*, unsigned int*);

/**
 * Constrói um vetor de árvores binárias e dentro de cada uma das posições
 * armazena o índice de cada texto individualmente.
 */
void indiceTextosConstroi(Dicionario*, Dicionario*, Entrada*, unsigned int,
    unsigned int*, char**);

/**
 * Utiliza todas os cálculos feitos ao longo do programa e retorna a saída
 * especificada.
 */
void indiceRetornaSaidas(Entrada*, Dicionario*, Dicionario*,
    unsigned int*, unsigned int, char**);

/**
 * Retorna um vetor de ocorrência baseado em uma lista de ocorrência.
 */
VecCelula* indiceVetorDeOcorrencias(Dicionario*, char*, int*);

/**
 * Retorna um vetor do índice (árvore binária) baseado no índice do arquivo.
 */
void indiceParaVetor(Dicionario*, Keyword*);

/**
 * Zera o valor da variável estática.
 */
void indiceParaVetorSetCounter();

/**
 * Utilizado apenas para testes.
 */
void indiceImprimePalavrasChaves(pNo*, int);

#endif
