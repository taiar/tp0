#ifndef UTIL_H_
#define UTIL_H_

/**
 * Coloca todos os valores do vetor de inteiros como 0 (zero)
 */
void zeraVetor(unsigned int*, int);

/**
 * Funções do método de ordenação Quicksort (versão recursiva)
 */
void Particao(unsigned int*, unsigned int*, int, int, int*, int*);
void Ordena(unsigned int*, unsigned int*, int, int);
void Quicksort(unsigned int*, unsigned int*, int);

#endif /* UTIL_H_ */
