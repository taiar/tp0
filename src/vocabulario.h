#ifndef __vocabulario__
#define __vocabulario__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estrutura das listas
typedef struct listapal *pLista;

typedef struct
{
  pLista primeiro, ultimo;
} Lista;

typedef struct listapal
{

  int val;
  pLista prox;

} listaCelula;

void listaInicia(Lista*);
int listaVazia(Lista);
void listaInsere(int, Lista*);
void listaDestroi(Lista*);

// estrutuda das arvores
typedef struct registro
{
  Lista documentos;
} Registro;

typedef struct no *pNo;

typedef struct no
{
  char palavra[50];
  Registro reg;
  pNo esq, dir;
} No;

typedef pNo Dicionario;

void dicionarioInicia(pNo*);
void dicionarioInsere(pNo*, char*, int);
void dicionarioCaminhoCentral(pNo*, FILE*);
void dicionarioImprime(pNo*, FILE*);

#endif
