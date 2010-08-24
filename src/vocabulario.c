#include "vocabulario.h"

int keywordCompare(Keyword *a, Keyword *b)
{
  if (a->ocorrencias > b->ocorrencias) return -1;
  else if (a->ocorrencias < b->ocorrencias) return 1;
  else return 0;
}

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

void dicionarioInsere(pNo *p, char *palavra, int texto, unsigned int *n_termos,
    int *flagNew)
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
    *flagNew = 1;
  }
  else if (strcmp(palavra, (*p)->termo) > 0) dicionarioInsere(&(*p)->dir,
      palavra, texto, n_termos, flagNew);
  else if (strcmp(palavra, (*p)->termo) < 0) dicionarioInsere(&(*p)->esq,
      palavra, texto, n_termos, flagNew);
  else
  {
    pLista aux;
    aux = (*p)->ocorrencias.primeiro;
    while (aux != NULL && aux->texto != texto)
      aux = aux->prox;
    if (aux == NULL) listaInsere(&(*p)->ocorrencias, texto);
    else aux->quantidade += 1;
    *flagNew = 0;
  }
}

void dicionarioCaminhoCentral(pNo *p, FILE *handle)
{
  if ((*p) == NULL) return;
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
    if (!aux) break;
  }

  listaDestroi(&(*p)->ocorrencias);
  fprintf(handle, "\n");
}

pNo* dicionarioBuscaTermo(pNo *p, char *termo)
{
  if ((*p) == NULL) return NULL;
  else if (strcmp(termo, (*p)->termo) > 0) dicionarioBuscaTermo(&(*p)->dir,
      termo);
  else if (strcmp(termo, (*p)->termo) > 0) dicionarioBuscaTermo(&(*p)->esq,
      termo);
  else return p;
}

void dicionarioImprime(pNo *p, int limite)
{
  if ((*p)->ocorrencias.tamanho > limite && limite != 0) return;

  printf("%s ", (*p)->termo);

  pLista aux;
  int i;
  aux = (*p)->ocorrencias.primeiro->prox;
  for (i = 0;; i++)
  {
    printf(",%d (%d)", aux->texto, aux->quantidade);
    aux = aux->prox;
    if (!aux) break;
  }
  printf("\n");
}

int dicionarioBuscaOcorrenciasTermo(pNo *p, char *termo)
{
  if ((*p) != NULL)
  {
    if (strcmp(termo, (*p)->termo) > 0) dicionarioBuscaOcorrenciasTermo(
        &(*p)->dir, termo);
    else if (strcmp(termo, (*p)->termo) < 0) dicionarioBuscaOcorrenciasTermo(
        &(*p)->esq, termo);
    else return (*p)->ocorrencias.tamanho;
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
  int fNew;

  while (fscanf(e->listaTextos, "%s\n", linha) != EOF)
  {
    leitura = fopen(linha, "r");
    getToken(leitura, termo, &rFlag);
    while (rFlag != 1)
    {
      dicionarioInsere(v, termo, n_texto, termos, &fNew);
      getToken(leitura, termo, &rFlag);
    }
    rFlag = 0;
    n_texto += 1;
    fclose(leitura);
  }
  *textos = n_texto;
}

void indiceTextosConstroi(Dicionario *vec_textos, Dicionario *vocabulario,
    Entrada *e, unsigned int key_lim, unsigned int *n_termos)
{
  char linha[100];
  char termo[50];
  int rFlag = 0;
  int n_texto = 0;
  unsigned int termos = 0;
  FILE *leitura;
  int ocorrencias_gerais;
  int fNew = 0;

  while (fscanf(e->listaTextos, "%s\n", linha) != EOF)
  {
    leitura = fopen(linha, "r");
    dicionarioInicia(&vec_textos[n_texto]);
    getToken(leitura, termo, &rFlag);

    while (rFlag != 1)
    {
      ocorrencias_gerais = dicionarioBuscaOcorrenciasTermo(vocabulario, termo);
      if (ocorrencias_gerais <= key_lim)
      {
        dicionarioInsere(&vec_textos[n_texto], termo, n_texto, &termos, &fNew);
        if (fNew) n_termos[n_texto] += 1;
      }
      getToken(leitura, termo, &rFlag);
    }
    rFlag = 0;
    n_texto += 1;
    fclose(leitura);
  }
}

void indiceRetornaPalavrasChave(Entrada *entrada, Dicionario *textos_keywords,
    Dicionario *indice, unsigned int *textos_termos_individual,
    unsigned int textos_total)
{
  int i, j, vecSize;
  Keyword *texto_keywords_individual;
  char linha[100];
  VecCelula *ocorrencias;
  unsigned int *potencialIgualdade = (unsigned int*) malloc(
      sizeof(unsigned int) * textos_total);
  zeraVetor(potencialIgualdade, textos_total);

  if (!entradaReinicia(entrada)) exit(EXIT_FAILURE);

  for (i = 0; i < textos_total; i += 1)
  {
    // conta quantos termos relevantes cada texto tem
    texto_keywords_individual = (Keyword*) malloc(sizeof(Keyword)
        * textos_termos_individual[i]);

    // transforma indice em vetor com o numero de ocorrencias de termos no texto
    indiceParaVetorSetCounter();
    indiceParaVetor(&textos_keywords[i], texto_keywords_individual);

    // ordena por termos que mais apareceram
    qsort(texto_keywords_individual, textos_termos_individual[i],
        sizeof(Keyword), (cmp) keywordCompare);

    // imprime no arquivo de saida o nome dos textos com suas keywords
    fscanf(entrada->listaTextos, "%s\n", linha);
    fprintf(entrada->palavrasChave, "%s;", linha);
    for (j = 0; j < textos_termos_individual[i]; j += 1)
    {
      fprintf(entrada->palavrasChave, "%s;", texto_keywords_individual[j].termo);

      //vetor de ocorrencias da palavra chave
      ocorrencias = indiceVetorDeOcorrencias(indice,
          texto_keywords_individual[j].termo, &vecSize);
      //alimenta vetor de potencial
      //TODO: pareis aquis!!!
      free(ocorrencias);
    }
    fprintf(entrada->palavrasChave, "\n");
  }
}

VecCelula* indiceVetorDeOcorrencias(Dicionario *indice, char *termo, int *size)
{
  int i = 0;
  pLista aux;
  pNo *n = dicionarioBuscaTermo(indice, termo);
  *size = (*n)->ocorrencias.tamanho;
  VecCelula *v = (VecCelula*) malloc(sizeof(VecCelula) * (*size));
  aux = (*n)->ocorrencias.primeiro->prox;
  while(aux->prox != NULL)
  {
    v[i].quantidade = aux->quantidade;
    v[i].texto = aux->texto;
    i += 1;
    aux = aux->prox;
  }
  return v;
}

void indiceParaVetorSetCounter()
{
  indiceParaVetorCounter = 0;
}

void indiceParaVetor(Dicionario *p, Keyword *k)
{
  if ((*p) == NULL) return;
  indiceParaVetor(&(*p)->esq, k);
  k[indiceParaVetorCounter].ocorrencias
      = (*p)->ocorrencias.primeiro->prox->quantidade;
  strcpy(k[indiceParaVetorCounter].termo, (*p)->termo);
  indiceParaVetorCounter += 1;
  indiceParaVetor(&(*p)->dir, k);
}

void indiceImprimePalavrasChaves(pNo *p, int limite)
{
  if ((*p) == NULL) return;
  indiceImprimePalavrasChaves(&(*p)->esq, limite);
  dicionarioImprime(&(*p), limite);
  indiceImprimePalavrasChaves(&(*p)->dir, limite);
}
