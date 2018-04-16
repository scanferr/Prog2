/*****************************************************************/
/*         Trabalho pratico 2 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAIZ 			(1)
#define PAI(x) 			(x/2)
#define FILHO_ESQ(x) 	(x*2)
#define FILHO_DIR(x) 	((x*2)+1)


int less_than(elemento * elem1, elemento * elem2)
{
	if (elem1 == NULL || elem2 == NULL)
	{
		return 0;
	}

	return elem1->prioridade < elem2->prioridade;
}

elemento * create_elem(int prioridade, const char * valor)
{
	elemento * aux = (elemento *) malloc(sizeof(elemento));

	if (aux == NULL)
		return NULL;

	aux->valor = (char*)calloc(strlen(valor)+1, sizeof(char));

	if (aux->valor == NULL)
	{
		free(aux);
		return NULL;
	}

	strcpy(aux->valor, valor);
	aux->prioridade = prioridade;

	return aux;
}

heap* heap_nova(int capacidade)
{
	heap * aux = (heap*)malloc(sizeof(heap));

	if (aux == NULL)
		return NULL;

	aux->tamanho = 0;
	aux->capacidade = capacidade;
	aux->elementos = (elemento**)calloc(capacidade+1, sizeof(elemento*));

	if (aux->elementos == NULL)
	{
		free(aux);
		return NULL;
	}

	return aux;
}

int heap_insere(heap * h, const char * texto, int prioridade)
{
	elemento *aux, *elem;
	int i;

	elem = create_elem(prioridade, texto);

	if (elem == NULL)
		return 0;

	if(h->tamanho >= h->capacidade)
		return 0;

	i = h->tamanho;
	h->elementos[i] = elem;
	h->tamanho++;

	while (i != RAIZ && less_than(h->elementos[i], h->elementos[PAI(i)]))
	{
		aux = h->elementos[PAI(i)];
		h->elementos[PAI(i)] = h->elementos[i];
		h->elementos[i] = aux;
		i = PAI(i);
	}
	return 1;
}

void heap_apaga(heap *h)
{
	int i;

	for(i=0; i<h->tamanho; i++)
		{
			free(h->elementos[i]->valor);
			free(h->elementos[i]);
			h->elementos[i]=NULL;
		}

	free(h->elementos);
	free(h);
}

char* heap_remove(heap * h)
{
	/*int i, biggestSon;
	elemento *aux;
	char *root;

	if ((h == NULL)||h->tamanho==0)
			return NULL;

	root = h->elementos[RAIZ]->valor;
	free(h->elementos[RAIZ]);

	h->tamanho--;
	h->elementos[RAIZ] = h->elementos[h->tamanho];
	h->elementos[h->tamanho] = NULL;

	i = RAIZ;

	while(FILHO_ESQ(i) <= h->tamanho)
	{
		biggestSon = FILHO_ESQ(i);

		if (FILHO_DIR(i) < h->tamanho && less_than(h->elementos[FILHO_DIR(i)], h->elementos[FILHO_ESQ(i)]))
			biggestSon = FILHO_DIR(i);

		if (less_than(h->elementos[biggestSon], h->elementos[i]))
		{
			aux = h->elementos[biggestSon];
			h->elementos[biggestSon] = h->elementos[i];
			h->elementos[i] = aux;
			i = biggestSon;

		}
		else
			break;
	}
		return root;*/
	return NULL;

}


heap* heap_constroi(elemento* v, int n_elementos)
{
	int i;
	elemento aux;

	if(v == NULL || n_elementos <= 0)
		return NULL;

	heap *h = heap_nova(n_elementos);

	if(h == NULL)
	    return NULL;

	  for(i = 0; i < n_elementos; i++)
	  {
		aux = v[i];

	    if(heap_insere(h, aux.valor, aux.prioridade) == 0)
	    {
	      heap_apaga(h);
	      return NULL;
	    }
	  }
	  return h;
}

int heap_altera_prioridade(heap *h, int indice, int nova_prioridade)
{
	int i, k;
	elemento *aux, *aux1;
	//char *str;

	//j = h->elementos[indice]->prioridade;

	h->elementos[indice]->prioridade = nova_prioridade;

	//=h->tamanho;

	for(k=RAIZ+1; k <= h->tamanho; k++)
		{
			if (less_than(h->elementos[k], h->elementos[PAI(k)]))
			{
				aux = h->elementos[PAI(k)];
				h->elementos[PAI(k)] = h->elementos[k];
				h->elementos[k] = aux;
				k = PAI(k);
			}
		}

	if(h->elementos[FILHO_ESQ(RAIZ)]->prioridade < h->elementos[FILHO_DIR(RAIZ)]->prioridade)
	{
		if(h->elementos[RAIZ]->prioridade > h->elementos[FILHO_ESQ(RAIZ)]->prioridade)
		{
			aux1=h->elementos[RAIZ];
			h->elementos[RAIZ] = h->elementos[FILHO_ESQ(RAIZ)];
			h->elementos[FILHO_ESQ(RAIZ)] = aux1;
		}
	}
	//mostraHeap(h,2);
	return 1;
}

void mostraHeap(heap *h, int indice)
{
  int i, nivel = 0;

  if (indice <= h->tamanho)
  {
    i = indice;
    while(i > 1)
    {
      i = i/2;
      nivel++;
    }

    mostraHeap(h, indice*2);

    for(i = 0; i < 3 * nivel; i++)
      printf("     ");

    printf("%s (%d)\n",h->elementos[indice]->valor, h->elementos[indice]->prioridade);

    mostraHeap(h, indice*2+1);
  }
}
