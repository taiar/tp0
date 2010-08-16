#include "io.h"

void entradaInit(entrada *entrada)
{
  entrada->aFlag = 0;
  entrada->bFlag = 0;
  entrada->cFlag = 0;

  entrada->entradaListaDeTextos = NULL;
  entrada->saidaMaisSimilares = NULL;
  entrada->saidaPalavrasChave = NULL;
}

int entradaLe(int argc, char** argv, entrada *entrada)
{
  entradaInit(entrada);
  int c;
  while ((c = getopt(argc, argv, "a:b:c:")) != -1)
  {
    switch (c)
    {
      case 'a':
        entrada->aFlag = 1;
        entrada->entradaListaDeTextos = optarg;
        break;
      case 'b':
        entrada->bFlag = 1;
        entrada->saidaPalavrasChave = optarg;
        break;
      case 'c':
        entrada->cFlag = 1;
        entrada->saidaMaisSimilares = optarg;
        break;
    }
  }
  if (entrada->aFlag != 1 || entrada->bFlag != 1 || entrada->cFlag != 1)
  {
    printf(
        "Os parâmetros não foram passados corretamente na linha de comando:\n\t");
    printf(
        "%s -a <lista de textos> -b <saida das palavras chave> -c <saida textos mais similares>\n",
        argv[0]);
    return 0;
  }
  return 1;
}

void entradaFree(entrada *entrada)
{
}

int isChar(char c)
{
  if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c == 45) || (c == 95)
      || (c >= 48 && c <= 57)) /* [0-9a-zA-Z-] */
    return 1;
  return 0;
}

int isSpace(char c)
{
  if (c == 32)
    return 1;
  return 0;
}

int isLineBreak(char c)
{
  if (c == 10)
    return 1;
  return 0;
}

char lowerCase(char c)
{
  if (c >= 65 && c <= 99)
    return tolower(c);
  else
    return c;
}

void getToken(FILE *handle, char* string, int *next)
{
  if (feof(handle))
    *next = 1;
  int count = 0;
  char buff;
  string[0] = '\0';
  buff = getc(handle);
  while (!isChar(buff) && !feof(handle))
    buff = getc(handle);
  while (isChar(buff) && !feof(handle))
  {
    string[count] = buff;
    string[count + 1] = '\0';
    count += 1;
    buff = getc(handle);
  }
  if (count < 3 && !feof(handle))
    getToken(handle, string, next);
  else
    return;
}
