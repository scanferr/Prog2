/*****************************************************************/
/*      Biblioteca lista ligada | PROG2 | MIEEC | 2017/18        */
/*****************************************************************/

//BIBLIOTECA LISTA USADA NAS AULAS, LIGEIRAMENTE MODIFICADA PARA ACOMODAR O TRABALHO 3
//STRUCT ALTERADA PARA CONTER OS VALORES PRETENDIDOS
//REMOCAO DE FUNCOES DESNECESSARIAS PARA ESTE TRABALHO
//ALTERACAO DE RESTANTES FUNÇÕES

#include "lista.h"
#include <string.h>
#include <stdlib.h>

l_elemento* novo_elemento(int x, int y, int type)
{
	/* aloca memoria para a estrutura lista */
	l_elemento *item = (l_elemento *) malloc(sizeof(l_elemento));
	if(item == NULL)
		return NULL;

	item->x = x;
	item->y = y;
	item->id = type;

	/* item ainda nao tem proximo */
  item->proximo = NULL;
  item->anterior = NULL;

	return item;
}

lista* lista_nova()
{
	/* cria lista */
	lista *lst = (lista*) malloc(sizeof(lista));
	if(lst == NULL)
		return NULL;

	/* lista esta' vazia */
	lst->inicio = NULL;
	lst->fim = NULL;
	lst->tamanho = 0;

  return lst;
}


void lista_apaga(lista *lst)
{
	l_elemento *aux;

	if(lst == NULL)
		return;

	/* percorre toda a lista e liberta memoria de
	   cada item e respectiva string */
	while(lst->inicio)
	{
		aux = lst->inicio;
		lst->inicio = lst->inicio->proximo;
		free(aux);
	}

	free(lst);
	return;
}


int lista_tamanho(lista *lst)
{
	if(lst == NULL)
		return -1;
	return lst->tamanho;
}


l_elemento* lista_inicio(lista *lst)
{
	if(lst == NULL)
		return NULL;
	return lst->inicio;
}


l_elemento* lista_fim(lista *lst)
{
	if(lst == NULL)
		return NULL;
	return lst->fim;
}

l_elemento* lista_elemento(lista *lst, int pos)
{
	int i;
	l_elemento *curr = NULL;

	if (lst == NULL || pos < 0 || pos >= lst->tamanho)
		return NULL;

	curr = lst->inicio;
	for(i=0; i<pos; i++)
		curr = curr->proximo;

	return curr;
}

l_elemento* lista_insere(lista *lst, int x, int y, int type, l_elemento *pos)
{
	l_elemento *curr = NULL;


	/* cria novo item */
	curr = novo_elemento(x,y,type);

	if (curr == NULL)
        return NULL;

	lst->tamanho++;

	/* caso especial: inserir no fim da lista */
	if(pos == NULL)
	{
		/* se e' primeiro l_elemento */
		if (lst->inicio == NULL)
		{
			lst->inicio = lst->fim = curr;
		}
		else
		{
			curr->anterior = lst->fim;
			lst->fim->proximo = curr;
			lst->fim = curr;
		}
		return curr;
	}

	/* caso especial: inserir no inicio da lista */
	if (pos == lst->inicio)
	{
		curr->proximo = lst->inicio;
		lst->inicio->anterior = curr;
		lst->inicio = curr;
        return curr;
	}

	/* troca apontadores para inserir item */
	curr->anterior = pos->anterior;
	curr->proximo = pos;
	pos->anterior->proximo = curr;
	pos->anterior = curr;

	return curr;
}

