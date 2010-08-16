#include "vocabulario.h"

//lista
void iniciaL(lista *l)
{
  l->primeiro = (apontalinha) malloc(sizeof(linha));
  l->ultimo = l->primeiro;
  l->primeiro->prox = NULL;
}

int vaziaL(lista l)
{
  return (l.primeiro == l.ultimo);
}

void insereL(int linha, lista *l)
{
  l->ultimo->prox = (apontalinha) malloc(sizeof(linha));
  l->ultimo = l->ultimo->prox;
  l->ultimo->linha = linha;
  l->ultimo->prox = NULL;
}

//arvore
void inicializaT(apontano *d)
{
  (*d) = NULL;
}

void insereT(apontano *p, char *palavra, int linha)
{
  if ((*p) == NULL)
  {
    *p = (apontano) malloc(sizeof(no));

    strcpy((*p)->palavra, palavra);
    iniciaL(&(*p)->reg.linhas);
    insereL(linha, &(*p)->reg.linhas);

    (*p)->esq = NULL;
    (*p)->dir = NULL;
  }
  else if (strcmp(palavra, (*p)->palavra) > 0)
    insereT(&(*p)->dir, palavra, linha);
  else if (strcmp(palavra, (*p)->palavra) < 0)
    insereT(&(*p)->esq, palavra, linha);
  else
  { //pesquisa se tal linha ja foi inserida
    apontalinha aux;
    aux = (*p)->reg.linhas.primeiro;
    while (aux != NULL && aux->linha != linha)
      aux = aux->prox;
    if (aux == NULL)
      insereL(linha, &(*p)->reg.linhas); //insere linha
  }
}

void caminhamento_centralT(apontano *p, FILE *handle)
{
  if ((*p) == NULL)
    return;
  caminhamento_centralT(&(*p)->esq, handle);
  imprimeNo(&(*p), handle);
  caminhamento_centralT(&(*p)->dir, handle);

}

void imprimeNo(apontano *p, FILE *handle)
{

  fprintf(handle, "%s ", (*p)->palavra);

  apontalinha aux;
  int i;

  aux = (*p)->reg.linhas.primeiro->prox;
  for (i = 0;; i++)
  {
    if (i == 0)
      fprintf(handle, "%d", aux->linha);
    else
      fprintf(handle, ",%d", aux->linha);
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
