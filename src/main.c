#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "vocabulario.h"

int main(int argc, char *argv[])
{
  entrada in;
  Dicionario vocabulario;

  if (!entradaLe(argc, argv, &in))
    exit(EXIT_FAILURE);

  FILE *palavrasChave, *similares;
  palavrasChave = fopen(in.saidaPalavrasChave, "w");
  similares = fopen(in.saidaMaisSimilares, "w");

  dicionarioInicia(&vocabulario);
  indiceConstroi(&vocabulario, in.listaTextos);

  dicionarioCaminhoCentral(&vocabulario, palavrasChave);

  entradaFree(&in);
  fclose(palavrasChave);
  fclose(similares);

  return 1;
}
