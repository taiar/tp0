#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Esta constante define em qual poporção dos textos uma palavra deve aparecer no
 * máximo para que seja considerada pelo algoritmo de indexação.
 */
#define KEYWORDS_PROPORCAO_APARICAO .2

#include "io.h"
#include "vocabulario.h"
#include "util.h"

int main(int argc, char *argv[])
{
  // guarda o nome dos arquivos que serão indexados
  char **arquivosNomes;

  // estrutura de entrada e saída
  Entrada in;

  Dicionario vocabulario,       // vocabulario do conjunto de textos
             *textos_keywords;  // vocabulario individual de cada texto

  unsigned int textos_total = 0, termos_total = 0, keywords_limite_texto,
      *textos_termos_individual = NULL;

  printf("Lendo e inicializando a entrada...\n");
  if (!entradaLe(argc, argv, &in)) exit(EXIT_FAILURE);

  printf("Indexando arquivos e criando vocabulario...\n");
  dicionarioInicia(&vocabulario);

  // Constroi índice com o vocabulário dos textos
  indiceConstroi(&vocabulario, &in, &textos_total, &termos_total);

  // Número de vezes que uma palavra pode aparecer sem ser desconsiderada
  keywords_limite_texto = textos_total * KEYWORDS_PROPORCAO_APARICAO;

  if (!entradaReinicia(&in)) exit(EXIT_FAILURE);

  printf("Identificando palavras-chave...\n");

  textos_keywords = (Dicionario*) malloc(sizeof(Dicionario) * textos_total);
  textos_termos_individual = (unsigned int*) malloc(sizeof(int) * textos_total);

  arquivosNomes = (char**) malloc(sizeof(char*) * textos_total);
  for (termos_total = 0; termos_total < textos_total; termos_total += 1)
    arquivosNomes[termos_total] = (char*) malloc(sizeof(char) * 100);

  zeraVetor(textos_termos_individual, textos_total);

  indiceTextosConstroi(textos_keywords, &vocabulario, &in,
      keywords_limite_texto, textos_termos_individual, arquivosNomes);

  if (!saidaInicia(&in)) exit(EXIT_FAILURE);

  // Retorna as palavras chaves e textos mais similares
  indiceRetornaSaidas(&in, textos_keywords, &vocabulario,
      textos_termos_individual, textos_total, arquivosNomes);

  entradaFree(&in);
  saidaFree(&in);

  return (EXIT_SUCCESS);
}
