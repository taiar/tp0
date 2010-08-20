#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEYWORDS_PROPORCAO_APARICAO 1.

#include "io.h"
#include "vocabulario.h"

int main(int argc, char *argv[])
{
  Entrada in;
  Dicionario vocabulario, *textos_keywords;
  unsigned int textos_total = 0, termos_total = 0, keywords_limite_texto;

  if (!entradaLe(argc, argv, &in))
    exit(EXIT_FAILURE);

  dicionarioInicia(&vocabulario);
  indiceConstroi(&vocabulario, &in, &textos_total, &termos_total);

  keywords_limite_texto = textos_total * KEYWORDS_PROPORCAO_APARICAO;

  if (!entradaReinicia(&in))
    exit(EXIT_FAILURE);

  textos_keywords = (Dicionario*) malloc(sizeof(Dicionario) * textos_total);
  indiceTextosConstroi(textos_keywords, &vocabulario, &in,
      keywords_limite_texto);

  char opa[18];
  strcpy(opa, "horizonte");

  printf("%d - \"%s\"\n\n\n", dicionarioBuscaOcorrenciasTermo(&vocabulario, opa), opa);

  if (!saidaInicia(&in))
    exit(EXIT_FAILURE);

  entradaFree(&in);
  saidaFree(&in);

  return (EXIT_SUCCESS);
}
