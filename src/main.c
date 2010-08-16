#include <stdio.h>
#include <stdlib.h>

#include "io.h"

int main(int argc, char *argv[])
{
  entrada in;
  if (!entradaLe(argc, argv, &in))
    exit(EXIT_FAILURE);

  FILE *listaTextos, *palavrasChave, *similares;
  listaTextos = fopen(in->entradaListaDeTextos, "r");
  palavrasChave = fopen(in->saidaPalavrasChave, "w");
  similares = fopen(in->saidaMaisSimilares, "w");



  return 1;
}
