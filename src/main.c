#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEYWORDS_PROPORCAO_APARICAO .4

#include "io.h"
#include "vocabulario.h"

int main(int argc, char *argv[])
{
  Entrada in;
  Dicionario vocabulario, *textos_keywords;
  unsigned int textos_total = 0, termos_total = 0, keywords_limite_texto;

  printf("Lendo e inicializando a entrada...\n");
  if (!entradaLe(argc, argv, &in))
    exit(EXIT_FAILURE);

  printf("Indexando arquivos e criando vocabulario...\n");
  dicionarioInicia(&vocabulario);
  indiceConstroi(&vocabulario, &in, &textos_total, &termos_total);

  keywords_limite_texto = textos_total * KEYWORDS_PROPORCAO_APARICAO;
  printf("Maximo de aparicoes: %d\n", keywords_limite_texto);
  if (!entradaReinicia(&in))
    exit(EXIT_FAILURE);

  printf("Identificando palavras-chave...\n");
  textos_keywords = (Dicionario*) malloc(sizeof(Dicionario) * textos_total);
  indiceTextosConstroi(textos_keywords, &vocabulario, &in,
      keywords_limite_texto);

  int i, *vec;
  for(i = 0; i < textos_total; i += 1)
  {
    vec = (int*) malloc(sizeof(int)*(textos_keywords[i]->ocorrencias.tamanho));
  }

  if (!saidaInicia(&in))
    exit(EXIT_FAILURE);

  entradaFree(&in);
  saidaFree(&in);

  return (EXIT_SUCCESS);
}
