#ifndef __vocabulario__
#define __vocabulario__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"

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

void dicionarioInicia(pNo*);
void dicionarioInsere(pNo*, char*, int, unsigned int*);
void dicionarioCaminhoCentral(pNo*, FILE*);
void dicionarioImprimeSaida(pNo*, FILE*);
void dicionarioImprime(pNo*);

void indiceConstroi(pNo*, FILE*, unsigned int*, unsigned int*);
void indiceImprimePalavrasChaves(pNo*);

#endif
