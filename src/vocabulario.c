#include "vocabulario.h"

//lista
void listaInicia(Lista *l)
{
  l->primeiro = (pLista) malloc(sizeof(linha));
  l->ultimo = l->primeiro;
  l->primeiro->prox = NULL;
}

int listaVazia(Lista l)
{
  return (l.primeiro == l.ultimo);
}

void listaInsere(int linha, Lista *l)
{
  l->ultimo->prox = (pLista) malloc(sizeof(linha));
  l->ultimo = l->ultimo->prox;
  l->ultimo->val = linha;
  l->ultimo->prox = NULL;
}

//arvore
void inicializaT(pNo *d)
{
  (*d) = NULL;
}

void insereT(pNo *p, char *palavra, int linha)
{
  if ((*p) == NULL)
  {
    *p = (pNo) malloc(sizeof(No));

    strcpy((*p)->palavra, palavra);
    listaInicia(&(*p)->reg.linhas);
    listaInsere(linha, &(*p)->reg.linhas);

    (*p)->esq = NULL;
    (*p)->dir = NULL;
  }
  else if (strcmp(palavra, (*p)->palavra) > 0)
    insereT(&(*p)->dir, palavra, linha);
  else if (strcmp(palavra, (*p)->palavra) < 0)
    insereT(&(*p)->esq, palavra, linha);
  else
  { //pesquisa se tal linha ja foi inserida
    pLista aux;
    aux = (*p)->reg.linhas.primeiro;
    while (aux != NULL && aux->val != linha)
      aux = aux->prox;
    if (aux == NULL)
      listaInsere(linha, &(*p)->reg.linhas); //insere linha
  }
}

void caminhamento_centralT(pNo *p, FILE *handle)
{
  if ((*p) == NULL)
    return;
  caminhamento_centralT(&(*p)->esq, handle);
  imprimeNo(&(*p), handle);
  caminhamento_centralT(&(*p)->dir, handle);

}

void imprimeNo(pNo *p, FILE *handle)
{

  fprintf(handle, "%s ", (*p)->palavra);

  pLista aux;
  int i;

  aux = (*p)->reg.linhas.primeiro->prox;
  for (i = 0;; i++)
  {
    if (i == 0)
      fprintf(handle, "%d", aux->val);
    else
      fprintf(handle, ",%d", aux->val);
    aux = aux->prox;
    if (!aux)
      break;
  }
  fprintf(handle, "\n");

}

/* VERSAO DE TESTE

 void imprimeNo(apontano *p){

 printf("%s ", (*p)->palavra);

 apontalinha aux;
 int i;

 aux = (*p)->reg.linhas.primeiro->prox;
 for(i = 0;;i++){
 if(i == 0) printf("%d", aux->linha);
 else printf(",%d", aux->linha);
 aux = aux->prox;
 if(!aux) break;
 }
 printf("\n");

 }

 */
