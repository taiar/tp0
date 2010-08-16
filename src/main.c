#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "vocabulario.h"

int main(int argc, char *argv[])
{
  entrada in;
  if (!entradaLe(argc, argv, &in))
    exit(EXIT_FAILURE);

  /**
   * Ideia para versao paralela:
   *  nesta versao, a entrada dos termos nos arquivos é feita de forma linear
   *  (um arquivo por vez, sequencialmente). Em uma versão paralela, fazer da
   *  seguinte forma:
   *    - alocar um vetor de ponteiros pra arquivos (quantos arquivos forem os
   *    da entrada);
   *    - utilizar uma thread para cada fluxo
   */

  FILE *listaTextos, *palavrasChave, *similares, *leitura;
  listaTextos = fopen(in.entradaListaDeTextos, "r");
  palavrasChave = fopen(in.saidaPalavrasChave, "w");
  similares = fopen(in.saidaMaisSimilares, "w");

  char linha[100];
  char termo[50];
  int rFlag = 0;

  while(fscanf(listaTextos, "%s\n", linha) != EOF)
  {
    printf("Lendo arquivo %s:\n", linha);
    leitura = fopen(linha, "r");
    getToken(leitura, termo, &rFlag);
    while(rFlag != 1)
    {
      printf("\"%s\"\n", termo);
      getToken(leitura, termo, &rFlag);
    }
    rFlag = 0;
    fclose(leitura);
  }

  fclose(listaTextos);
  fclose(palavrasChave);
  fclose(similares);

  return 1;
}
