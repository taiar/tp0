#ifndef __io__
#define __io__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Armazena dados lidos da entrada.
 */
typedef struct
{
  int aFlag, bFlag, cFlag;
  char *entradaListaDeTextos, *saidaPalavrasChave, *saidaMaisSimilares;
  //TODO: apagar se desnecessário
  FILE *listaTextos, *palavrasChave, *similares;
} entrada;

/**
 * Seta os valores iniciais da estrutura de entrada.
 */
void entradaInit(entrada*);

/**
 * Libera dados utilizados na leitura da entrada.
 */
void entradaFree(entrada*);

/**
 * Faz leitura dos dados de entrada e armazena.
 */
int entradaLe(int, char**, entrada*);

/**
 * Verifica se o caractere passado é valido segundo criterios arbitrarios para leitura do arquivo.
 */
int isChar(char);

/**
 * Verifica se o caractere passado como parâmetro é um espaço.
 */
int isSpace(char);

/**
 * Verifica se o caractere passado como parâmetro é uma quebra de linha.
 */
int isLineBreak(char);

/**
 * Transforma caracteres de letras maiúsculas em minúsculas para fins de simplificação.
 */
char lowerCase(char);

/**
 * Lê e armazena em uma variável uma string retirada do arquivo de passado como
 * parâmetro. A string é definida arbitráriamente segundo especificação.
 * Sinaliza um flag inteiro interpretando o valor char da próxima leitura para
 * facilitar o trabalho na leitura dos arquivos.
 */
void getToken(FILE*, char*, int*);

#endif
