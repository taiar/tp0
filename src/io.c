#include "io.h"

void entradaInit(Entrada *entrada)
{
  entrada->aFlag = 0;
  entrada->bFlag = 0;
  entrada->cFlag = 0;

  entrada->entradaListaDeTextos = NULL;
  entrada->saidaMaisSimilares = NULL;
  entrada->saidaPalavrasChave = NULL;
}

int entradaLe(int argc, char** argv, Entrada *entrada)
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

  entrada->listaTextos = fopen(entrada->entradaListaDeTextos, "r");
  if (!entrada->listaTextos)
  {
    printf(
        "O arquivo passado como parâmetro de lista de textos '%s' não existe.\n",
        entrada->entradaListaDeTextos);
    return 0;
  }
  return 1;
}

int entradaReinicia(Entrada *entrada)
{
  if (entrada->listaTextos) fclose(entrada->listaTextos);
  entrada->listaTextos = fopen(entrada->entradaListaDeTextos, "r");
  if (!entrada->listaTextos)
  {
    printf("Não foi possível reiniciar a leitura da lista de textos");
    return 0;
  }
  return 1;
}

void entradaFree(Entrada *entrada)
{
  fclose(entrada->listaTextos);
}

int saidaInicia(Entrada *entrada)
{
  entrada->palavrasChave = fopen(entrada->saidaPalavrasChave, "w");
  entrada->similares = fopen(entrada->saidaMaisSimilares, "w");
  if (!entrada->palavrasChave || !entrada->similares)
  {
    printf("Não foi possível escrever os arquivos de saída. '%s' e '%s'\n",
        entrada->saidaPalavrasChave, entrada->saidaMaisSimilares);
    return 0;
  }
  return 1;
}

void saidaFree(Entrada *entrada)
{
  fclose(entrada->palavrasChave);
  fclose(entrada->similares);
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
  if (c == 32) return 1;
  return 0;
}

int isLineBreak(char c)
{
  if (c == 10) return 1;
  return 0;
}

char lowerCase(char c)
{
  if (c >= 65 && c <= 99) return tolower(c);
  else return c;
}

char tiraAcento(char c)
{
  if ((c >= 192 && c <= 198) || (c >= 224 && c <= 230) || (c >= 192 - 256 && c
      <= 198 - 256) || (c >= 224 - 256 && c <= 230 - 256)) return 'a';
  else if ((c == 199) || (c == 231) || (c == 199 - 256) || (c == 231 - 256)) return 'c';
  else if ((c >= 200 && c <= 203) || (c >= 232 && c <= 235) || (c >= 200 - 256
      && c <= 203 - 256) || (c >= 232 - 256 && c <= 235 - 256)) return 'e';
  else if ((c >= 204 && c <= 207) || (c >= 236 && c <= 239) || (c >= 204 - 256
      && c <= 207 - 256) || (c >= 236 - 256 && c <= 239 - 256)) return 'i';
  else if ((c >= 210 && c <= 214) || (c >= 242 && c <= 246) || (c >= 210 - 256
      && c <= 214 - 256) || (c >= 242 - 256 && c <= 246 - 256)) return 'o';
  else if ((c >= 217 && c <= 220) || (c >= 249 && c <= 252) || (c >= 217 - 256
      && c <= 220 - 256) || (c >= 249 - 256 && c <= 252 - 256)) return 'u';
  else return c;
}

void getToken(FILE *handle, char* string, int *next)
{
  if (feof(handle)) *next = 1;
  int count = 0;
  char buff;
  char min;
  string[0] = '\0';
  buff = getc(handle);
  while (!isalpha(buff) && !feof(handle))
    buff = getc(handle);
  while (isalpha(buff) && !feof(handle))
  {
    min = tolower(buff);
    string[count] = min;
    string[count + 1] = '\0';
    count += 1;
    buff = getc(handle);
  }
  if (count < KEYWORD_MIN_CHAR && !feof(handle)) getToken(handle, string, next);
  else return;
}
