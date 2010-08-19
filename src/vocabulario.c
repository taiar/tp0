#include "vocabulario.h"

void listaInicia(Lista *l)
{
  l->tamanho = 0;
  l->primeiro = (pLista) malloc(sizeof(listaCelula));
  l->ultimo = l->primeiro;
  l->primeiro->prox = NULL;
}

int listaVazia(Lista *l)
{
  return (l->tamanho == 0);
  //return (l.primeiro == l.ultimo);
}

void listaInsere(Lista *l, int texto)
{
  l->ultimo->prox = (pLista) malloc(sizeof(listaCelula));
  l->ultimo = l->ultimo->prox;
  l->ultimo->texto = texto;
  l->ultimo->quantidade = 1;
  l->tamanho += 1;
  l->ultimo->prox = NULL;
}

void listaDestroi(Lista *l)
{
  while (!listaVazia(l))
    listaRetiraUltimo(l);
}

void listaRetiraUltimo(Lista *l)
{
  pLista aux, aux2;
  aux = l->primeiro->prox;
  if (aux->prox == NULL)
  {
    l->ultimo = l->primeiro;
    l->primeiro->prox = NULL;
    free(aux);
    l->tamanho = 0;
    return;
  }
  while (aux->prox->prox != NULL)
    aux = aux->prox;
  aux2 = aux->prox;
  l->ultimo = aux;
  aux->prox = NULL;
  free(aux2->prox);
  l->tamanho -= 1;
}

void dicionarioInicia(pNo *d)
{
  (*d) = NULL;
}

void dicionarioInsere(pNo *p, char *palavra, int texto, unsigned int *n_termos)
{
  if ((*p) == NULL)
  {
    *p = (pNo) malloc(sizeof(No));

    strcpy((*p)->termo, palavra);
    listaInicia(&(*p)->ocorrencias);
    listaInsere(&(*p)->ocorrencias, texto);

    (*p)->esq = NULL;
    (*p)->dir = NULL;
    *n_termos += 1;
  }
  else if (strcmp(palavra, (*p)->termo) > 0)
    dicionarioInsere(&(*p)->dir, palavra, texto, n_termos);
  else if (strcmp(palavra, (*p)->termo) < 0)
    dicionarioInsere(&(*p)->esq, palavra, texto, n_termos);
  else
  {
    pLista aux;
    aux = (*p)->ocorrencias.primeiro;
    while (aux != NULL && aux->texto != texto)
      aux = aux->prox;
    if (aux == NULL)
      listaInsere(&(*p)->ocorrencias, texto);
    else
      aux->quantidade += 1;
  }
}

void dicionarioCaminhoCentral(pNo *p, FILE *handle)
{
  if ((*p) == NULL)
    return;
  dicionarioCaminhoCentral(&(*p)->esq, handle);
  dicionarioImprimeSaida(&(*p), handle);
  dicionarioCaminhoCentral(&(*p)->dir, handle);

}

void dicionarioImprimeSaida(pNo *p, FILE *handle)
{
  fprintf(handle, "%s ", (*p)->termo);

  pLista aux;
  int i;

  aux = (*p)->ocorrencias.primeiro->prox;
  for (i = 0;; i++)
  {
    fprintf(handle, ",%d (%d)", aux->texto, aux->quantidade);
    aux = aux->prox;
    if (!aux)
      break;
  }

  listaDestroi(&(*p)->ocorrencias);
  fprintf(handle, "\n");
}

void dicionarioImprime(pNo *p, int limite)
{
  if ((*p)->ocorrencias.tamanho > limite && limite != 0)
    return;

  printf("%s ", (*p)->termo);

  pLista aux;
  int i;
  aux = (*p)->ocorrencias.primeiro->prox;
  for (i = 0;; i++)
  {
    printf(",%d (%d)", aux->texto, aux->quantidade);
    aux = aux->prox;
    if (!aux)
      break;
  }
  printf("\n");
}

int dicionarioBuscaOcorrenciasTermo(pNo *p, char *termo)
{
  if ((*p) != NULL)
  {
    printf("OEE!\n");
    if (strcmp(termo, (*p)->termo) > 0)
      dicionarioBuscaOcorrenciasTermo(&(*p)->dir, termo);
    else if (strcmp(termo, (*p)->termo) < 0)
      dicionarioBuscaOcorrenciasTermo(&(*p)->esq, termo);
    else
    {
      printf("ACHEI!\n");
      return (*p)->ocorrencias.tamanho;
    }
  }
}

void indiceConstroi(pNo *v, Entrada *e, unsigned int *textos,
    unsigned int *termos)
{
  char linha[100];
  char termo[50];
  int rFlag = 0;
  int n_texto = 0;
  FILE *leitura;

  while (fscanf(e->listaTextos, "%s\n", linha) != EOF)
  {
    leitura = fopen(linha, "r");
    getToken(leitura, termo, &rFlag);
    while (rFlag != 1)
    {
      dicionarioInsere(v, termo, n_texto, termos);
      getToken(leitura, termo, &rFlag);
    }
    rFlag = 0;
    n_texto += 1;
    fclose(leitura);
  }
  *textos = n_texto;
}

void indiceTextosConstroi(Dicionario *vec_textos, Dicionario *vocabulario,
    Entrada *e, unsigned int key_lim)
{
  char linha[100];
  char termo[50];
  int rFlag = 0;
  int n_texto = 0;
  unsigned int termos = 0;
  FILE *leitura;

  while (fscanf(e->listaTextos, "%s\n", linha) != EOF)
  {
    leitura = fopen(linha, "r");
    dicionarioInicia(&vec_textos[n_texto]);
    getToken(leitura, termo, &rFlag);
    while (rFlag != 1)
    {
      dicionarioInsere(&vec_textos[n_texto], termo, n_texto, &termos);
      getToken(leitura, termo, &rFlag);
    }
    rFlag = 0;
    n_texto += 1;
    fclose(leitura);
  }
}

void indiceImprimePalavrasChaves(pNo *p, int limite)
{
  if ((*p) == NULL)
    return;
  indiceImprimePalavrasChaves(&(*p)->esq, limite);
  dicionarioImprime(&(*p), limite);
  indiceImprimePalavrasChaves(&(*p)->dir, limite);
}
