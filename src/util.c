/*
 * util.c
 *
 *  Created on: 24/08/2010
 *      Author: taiar
 */

void zeraVetor(unsigned int *v, int t)
{
  int i;
  for (i = 0; i < t; i += 1)
    v[i] = 0;
}

void ssort(unsigned int *v, int tam)
{
  int i, j, value;
  int gap = 1;
  do
  {
    gap = 3 * gap + 1;
  }
  while (gap < tam);
  do
  {
    gap /= 3;
    for (i = gap; i < tam; i++)
    {
      value = v[i];
      j = i - gap;
      while (j >= 0 && value < v[j])
      {
        v[j + gap] = v[j];
        j -= gap;
      }
      v[j + gap] = value;
    }
  }
  while (gap > 1);
}

void particao(int v[], int e, int d, int *i, int *j)
{
  int x, w;
  *i = e;
  *j = d;
  x = v[(e + d) / 2];
  do
  {
    while (v[*i] < x) (*i)++;
    while (v[*j] > x) (*j)--;
    if (*i <= *j)
    {
      w = v[*i];
      v[*i] = v[*j];
      v[*j] = w;
      (*i)++;
      (*j)--;
    }
  }
  while (*i <= *j);
}

void Particao(unsigned int *v, unsigned int *u, int e, int d, int *i, int *j)
{
  int x, w, ww;
  *i = e;
  *j = d;
  x = v[(e + d) / 2];
  do
  {
    while (v[*i] < x) (*i)++;
    while (v[*j] > x) (*j)--;
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
  }
  while (*i <= *j);
}

void ordena(int v[], int e, int d)
{
  int i, j;
  particao(v, e, d, &i, &j);
  if (e < j) ordena(v, e, j);
  if (i < d) ordena(v, i, d);
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

void quicksort(int *v, int tam)
{
  ordena(v, 0, tam - 1);
}
