#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int keywords_upper_limit;
float keywords_appearence_proportion = .5;

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

  keywords_upper_limit = total_textos * keywords_appearence_proportion;

  indiceImprimePalavrasChaves(&vocabulario);

  if (!saidaInicia(&in))
    exit(EXIT_FAILURE);

  entradaFree(&in);
  saidaFree(&in);

  return 1;
}
