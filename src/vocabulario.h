#ifndef __vocabulario__
#define __vocabulario__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estrutura das listas
typedef struct listapal *apontalinha;

typedef struct
{
  apontalinha primeiro, ultimo;
} lista;

typedef struct listapal
{

  int linha;
  apontalinha prox;

} linha;

void iniciaL(lista*);
int vaziaL(lista);
void insereL(int, lista*);

// estrutuda das arvores
typedef struct registro
{

  lista linhas;

} registro;

typedef struct no *apontano;

typedef struct no
{
  char palavra[30];
  registro reg;
  apontano esq, dir;
} no;

typedef apontano dicionario;

void inicializaT(apontano*);
void insereT(apontano*, char*, int);
void caminhamento_centralT(apontano*, FILE*);
void imprimeNo(apontano*, FILE*);

#endif
