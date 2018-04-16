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
#define PAI(x) 			((x)/2)
#define FILHO_ESQ(x) 	(x*2)
#define FILHO_DIR(x) 	((x*2)+1)

/*
 *INÍCIO FUNÇÕES AUXILIARES
 */

//Função auxiliar para comparar prioridade dos elementos;
//********************************************
int less_than(elemento *elem1, elemento *elem2)
{
	//Se elemento 1 ou elemento 2 não existerem retorna NULL;
	if (elem1 == NULL || elem2 == NULL)
	{
		return 0;
	}

	//Retorna elementos com a prioridade desejada;
	return elem1->prioridade < elem2->prioridade;
}

//Função auxiliar para a criação de elementos;
//********************************************
elemento * create_elem(int prioridade, const char * valor)
{
	//Alocação dinâmica de elementos;
	elemento *aux = (elemento*) malloc(sizeof(elemento));

	//Se elementos não existirem retorna NULL;
	if (aux == NULL)
	{
		return NULL;
	}

	//Alocação dinâmica para as strings dos elementos, na heap;
	aux->valor = (char*)calloc(strlen(valor)+1, sizeof(char));

	//Se strings não existirem libertar espaço de memória e retornar NULL;
	if (aux->valor == NULL)
	{
		free(aux);
		return NULL;
	}

	//Copiar as strings para a heap com a prioridade prentendida;
	strcpy(aux->valor, valor);
	aux->prioridade = prioridade;

	//Retorna o elemento;
	return aux;
}

/*
 *FIM FUNÇÕES AUXILIARES
 */


/*
cria uma heap novo com o tamanho máximo inidicado
Parâmetros:tamanho_maximo->tamanho máximo para a heap
Retorna: Apontador para a heap criada ou NULL se ocorrer um erro.
Observações: A heap é criada sem elementos.
*/
heap* heap_nova(int capacidade)
{
	//Alocar dinamicamente a heap;
	heap * aux = (heap *) malloc(sizeof(heap));

	//Verificar a existência da heap. Se já existir retornar NULL;
	if (aux == NULL)
	{
		return NULL;
	}

	//Criar uma heap vazia com a capacidade especificado pelo parâmetro "capacidade";
	aux->tamanho = 0;
	aux->capacidade = capacidade;
	//Alocar dinâmicamente cada elemento da heap;
	aux->elementos = (elemento **) calloc(capacidade+1, sizeof(elemento *));

	//Se não existirem elementos liberta espaço alocado anteriormente;
	if (aux->elementos == NULL)
	{
		free(aux);
		return NULL;
	}

	//Retorna apontador para a heap criada;
	return aux;
}

/*
adiciona um novo elemento à heap
Parâmetros: h->apontador para a heap; texto->string a guardar no elemento; prioridade->prioridade do elemento
Retorna: 1 se adicionou corretamente o novo elemento, 0 se a heap está cheia ou se não consegue criar o elemento.
Observações: A inserção de um elemento deve manter a consistência da heap. Exemplo de erro é o apontador para a heap ser NULL.
*/
int heap_insere(heap * h, const char * texto, int prioridade)
{
	//Declaração de variáveis;
	elemento *aux, *elem;
	int x;
	//pos = h->tamanho + 1;

	//Verifica se a heap está cheia. se sim não insere elementos;
	if (h->tamanho >= h->capacidade)
		return 0;

	//Criar elementos recorrendo à função auxiliar criada;
	elem = create_elem(prioridade, texto);

	//Verificar se elmentos não existem. Retornar NULL se sim;
	if (elem == NULL)
	{
		return 0;
	}

	//Coloca elementos no fim da heap;
	x = h->tamanho+1;
	h->elementos[x] = elem;
	h->tamanho++;

	//Se a prioridade do elemento filho for maior que a prioridade do elemento pai efetuar a troca dos dois;
	while (x != RAIZ && less_than(h->elementos[x], h->elementos[PAI(x)]))
	{
		aux = h->elementos[PAI(x)];
		h->elementos[PAI(x)] = h->elementos[x];
		h->elementos[x] = aux;
		x = PAI(x);
	}

	//mostraHeap(h, 1);
	return 1;
}

/*
elimina uma heap, libertando toda a memória ocupada
Parâmetros: h->apontador para a heap a apagar
Observações: Não esquecer de libertar toda a memória alocada para evitar memory leaks.
*/
void heap_apaga(heap *h)
{
	//Declaração de variáveis;
	int x;

	//Ciclo para apagar todos os elementos e as strings de cada um;
	for(x=1; x<=h->tamanho; x++)
	{
		free(h->elementos[x]->valor);
		free(h->elementos[x]);
		h->elementos[x]=NULL;
	}

	//Libertar toda a memória alocada;
	free(h->elementos);
	free(h);
  return;
}

/*
remove o elemento da raiz da heap
Parâmetros: h->apontador para a heap
Retorna: A string do elemento de menor prioridade, NULL se a heap estiver vazia ou em caso de erro.
Observações: Para manter a consistência da heap, a remoção da raiz implica a reordenação dos restantes elementos de acordo com a sua prioridade.
*/
char* heap_remove(heap * h)
{
	int i, biggestSon;
		elemento *aux;
		char *root;

		//Se a heap não existir ou tamanho for 0, retorna NULL
		if ((h == NULL)||h->tamanho==0)
				return NULL;

		//Guarda em root a string da RAIZ
		root = h->elementos[RAIZ]->valor;

		//Liberta da memória o elemento da RAIZ
		free(h->elementos[RAIZ]);

		//Atribui a RAIZ o elemento na posicao tamanho (ultimo elemento)
		h->elementos[RAIZ] = h->elementos[h->tamanho];
		//Atribui ao ultimo elemento o valor NULL
		h->elementos[h->tamanho] = NULL;

		i = RAIZ;

		//Após remover a RAIZ e ser-lhe atribuido o elemento em "tamanho", e' necessario ordenar e garantir que continua uma min-heap
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

		//Como foi removido um elemento, e necessario reduzir o tamanho da heap em 1
			h->tamanho--;

			return root;
}

/*
cria uma nova heap com os elementos do vetor v
Parâmetros: v->vetor de elementos; n_elementos->número de elementos do vetor v
Retorna: Apontador para a heap criada ou NULL se ocorrer um erro.
*/
heap* heap_constroi(elemento* v, int n_elementos)
{
	int i;
	elemento aux;

	//Se v não existir ou se n_elementos for 0 ou negativo, retorna NULL
	if(v == NULL || n_elementos <= 0)
		return NULL;

	//Cria uma nova heap
	heap *h = heap_nova(n_elementos);

	//Se a h não for criada, retorna NULL
	if(h == NULL)
	    return NULL;

	//Ciclo para percorrer todos os elementos do vetor e guardar em aux. Quando a heap estiver cheia, pára.
	  for(i = 0; i < n_elementos; i++)
	  {
		aux = v[i];

	    if(heap_insere(h, aux.valor, aux.prioridade) == 0)
	    {
	      return NULL;
	    }
	  }
	  	  return h;
}

/*
altera a pripridade de um elemento da heap
Parâmetros:h->apontador para a heap; indice_elemento->identificador do elemento; nova_prioridade->nova prioridade atribuída ao elemento da heap
Retorna: 1 se a prioridade for alterada com sucesso, -1 em caso de erro.
*/
int heap_altera_prioridade(heap *h, int indice, int nova_prioridade)
{
	int x;
	elemento *aux;

	//Atribui nova_prioridade à prioridade do elemento[indice]
	h->elementos[indice]->prioridade = nova_prioridade;

	//Verifica se a prioridade é a nova_prioridade. Se não for, retorna -1.
	if(h->elementos[indice]->prioridade != nova_prioridade)
		return -1;

	//Ciclo para ordenar os elementos. Ao alterar as prioridades, é necessário assegurar que se mantém como min-heap.
	for(x = h->tamanho ; x > RAIZ ; x--)
		{
			if (less_than(h->elementos[x], h->elementos[PAI(x)]))
			{
				aux = h->elementos[PAI(x)];
				h->elementos[PAI(x)] = h->elementos[x];
				h->elementos[x] = aux;
			}
		}
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
