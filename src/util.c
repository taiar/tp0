#include "util.h"

void zeraVetor(unsigned int *v, int t)
{
  int i;
  for (i = 0; i < t; i += 1)
    v[i] = 0;
}

void Particao(unsigned int *v, unsigned int *u, int e, int d, int *i, int *j)
{
  int x, w, ww;
  *i = e;
  *j = d;
  x = v[(e + d) / 2];
  do
  {
    while (v[*i] < x)
      (*i)++;
    while (v[*j] > x)
      (*j)--;
    if (*i <= *j)
    {
      w = v[*i];
      ww = u[*i];
      v[*i] = v[*j];
      u[*i] = u[*j];
      v[*j] = w;
      u[*j] = ww;
      (*i)++;
      (*j)--;
    }
  } while (*i <= *j);
}

void Ordena(unsigned int *v, unsigned int *u, int e, int d)
{
  int i, j;
  Particao(v, u, e, d, &i, &j);
  if (e < j) Ordena(v, u, e, j);
  if (i < d) Ordena(v, u, i, d);
}

void Quicksort(unsigned int *v, unsigned int *u, int tam)
{
  Ordena(v, u, 0, tam - 1);
}
