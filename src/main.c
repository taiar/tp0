#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEYWORDS_PROPORCAO_APARICAO .2

#include "io.h"
#include "vocabulario.h"
#include "util.h"

int main(int argc, char *argv[])
{
  char **arquivosNomes;
  Entrada in;
  Dicionario vocabulario, *textos_keywords;
  unsigned int textos_total = 0, termos_total = 0, keywords_limite_texto,
      *textos_termos_individual = NULL;

  printf("Lendo e inicializando a entrada...\n");
  if (!entradaLe(argc, argv, &in)) exit(EXIT_FAILURE);

  printf("Indexando arquivos e criando vocabulario...\n");
  dicionarioInicia(&vocabulario);
  indiceConstroi(&vocabulario, &in, &textos_total, &termos_total);

  keywords_limite_texto = textos_total * KEYWORDS_PROPORCAO_APARICAO;
  if (!entradaReinicia(&in)) exit(EXIT_FAILURE);

  printf("Identificando palavras-chave...\n");
  textos_keywords = (Dicionario*) malloc(sizeof(Dicionario) * textos_total);
  textos_termos_individual = (unsigned int*) malloc(sizeof(int) * textos_total);
  zeraVetor(textos_termos_individual, textos_total);

  indiceTextosConstroi(textos_keywords, &vocabulario, &in,
      keywords_limite_texto, textos_termos_individual);

  if (!saidaInicia(&in)) exit(EXIT_FAILURE);
  indiceRetornaPalavrasChave(&in, textos_keywords, &vocabulario,
      textos_termos_individual, textos_total);

  entradaFree(&in);
  saidaFree(&in);

  return (EXIT_SUCCESS);
}
