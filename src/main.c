#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "vocabulario.h"

int main(int argc, char *argv[])
{
  Entrada in;
  Dicionario vocabulario;
  unsigned int total_textos = 0, total_termos = 0;

  if (!entradaLe(argc, argv, &in))
    exit(EXIT_FAILURE);

  dicionarioInicia(&vocabulario);
  indiceConstroi(&vocabulario, in.listaTextos, &total_textos, &total_termos);

  if (!saidaInicia(&in))
    exit(EXIT_FAILURE);

  entradaFree(&in);
  saidaFree(&in);

  return 1;
}
