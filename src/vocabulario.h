#ifndef __vocabulario__
#define __vocabulario__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "util.h"

typedef struct
{
  char termo[50];
  unsigned int ocorrencias;
} Keyword;

typedef int (*cmp)(Keyword*, Keyword*);
int keywordCompare(Keyword*, Keyword*);

//estrutura das listas
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
int listaVazia(Lista*);
void listaInsere(Lista*, int);
void listaDestroi(Lista*);
void listaRetiraUltimo(Lista*);

typedef struct no *pNo;

typedef struct no
{
  char termo[50];
  Lista ocorrencias;
  pNo esq, dir;
} No;

typedef pNo Dicionario;
static unsigned int indiceParaVetorCounter;

void dicionarioInicia(pNo*);
void dicionarioInsere(pNo*, char*, int, unsigned int*, int*);
void dicionarioCaminhoCentral(pNo*, FILE*);
void dicionarioImprimeSaida(pNo*, FILE*);
pNo* dicionarioBuscaTermo(pNo*, char*);
void dicionarioImprime(pNo*, int);
int dicionarioBuscaOcorrenciasTermo(pNo*, char*);

void indiceConstroi(pNo*, Entrada*, unsigned int*, unsigned int*);
void indiceTextosConstroi(Dicionario*, Dicionario*, Entrada*, unsigned int,
    unsigned int*);
void indiceRetornaPalavrasChave(Entrada*, Dicionario*, Dicionario*,
    unsigned int*, unsigned int);
VecCelula* indiceVetorDeOcorrencias(Dicionario*, char*, int*);
void indiceParaVetor(Dicionario*, Keyword*);
void indiceParaVetorSetCounter();
void indiceTextosRefinaKeywords(Dicionario*, Dicionario*, unsigned int);
void indiceRemoveKeywordsIrrelevantes(Dicionario*, Dicionario*);
void indiceImprimePalavrasChaves(pNo*, int);

#endif
