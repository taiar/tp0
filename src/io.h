#include <stdlib.h>
#include <stdio.h>

#ifndef __io__
#define __io__

/**
 * Verifica se o caractere passado é valido segundo criterios arbitrarios para leitura do arquivo.
 */
int is_char(char);

/**
 * Verifica se o caractere passado como parâmetro é um espaço.
 */
int is_space(char);

/**
 * Verifica se o caractere passado como parâmetro é uma quebra de linha.
 */
int is_line_break(char);

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
void get_token(FILE*, char*, int*);

#endif
