/*****************************************************************/
/*          Biblioteca vetor | PROG2 | MIEEC | 2017/18           */
/*****************************************************************/

//BIBLIOTECA VETOR USADA NAS AULAS, LIGEIRAMENTE MODIFICADA PARA ACOMODAR O TRABALHO 3
//STRUCT ALTERADA PARA CONTER OS VALORES PRETENDIDOS
//REMOCAO DE FUNCOES DESNECESSARIAS PARA ESTE TRABALHO
//ALTERACAO DA FUNCAO VETOR_ELEMENTO
//ALTERACAO DA FUNCAO VETOR_INSERE DE ACORDO COM O PRETENDIDO

#include "vetor.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

vetor* vetor_novo()
{
	vetor* vec;

	/* aloca memoria para a estrutura vetor */
	vec = (vetor*)malloc(sizeof(vetor));
	if(vec == NULL)
	return NULL;

	vec->tamanho = 0;
	vec->capacidade = 0;
	vec->elementos = NULL;

	return vec;
}

void vetor_apaga(vetor* vec)
{
	int i;

	if(vec == NULL)
	return;

	/* liberta memoria de cada string */
	for (i = 0; i < vec->tamanho; i++)
	{
		free(vec->elementos[i].x);
		free(vec->elementos[i].y);
		free(vec->elementos[i].type);
	}

	/* liberta memoria dos apontares para as strings */
	free(vec->elementos);

	/* liberta memoria da estrutura vetor */
	free(vec);
}

int vetor_tamanho(vetor* vec)
{
	if(vec == NULL)
	return -1;

	return vec->tamanho;
}

v_elemento* vetor_elemento(vetor* vec, int indice)
{	
	v_elemento *aux;

	*aux  = vec->elementos[indice];

	if (vec == NULL || indice < 0 || indice >= vec->tamanho)
	return NULL;

	return aux;
}

int vetor_insere(vetor *vec, int x, int y, int type, int pos)
{
	int i;

	if(vec == NULL || pos < -1 || pos > vec->tamanho)
		return -1;

	
	// controlo de repeticoes
	for (i = 0; i < vec->tamanho; i++)
	{
		if ( x == vec->elementos[i].x && y == vec->elementos[i].y)
			return 0;
	}

	/* aumenta elementos do vetor se capacidade nao for suficiente */
	if(vec->tamanho == vec->capacidade)
	{
		if(vec->capacidade == 0)
		vec->capacidade = 1;
		else
		vec->capacidade *= 2;

		vec->elementos = (v_elemento*)realloc(vec->elementos, vec->capacidade * sizeof(v_elemento));
		if(vec->elementos == NULL)
		return -1;
	}

	/* se pos=-1 insere no fim do vetor */
	if(pos == -1)
		pos = vec->tamanho;

	/* copia todos os elementos a partir da posicao pos ate' ao fim do vetor para pos+1 */
	for(i=vec->tamanho-1; i>=pos; i--)
	{
		vec->elementos[i+1] = vec->elementos[i];
	}

	/* copia valor */
	vec->elementos[pos].x = x;
	vec->elementos[pos].y = y;
	vec->elementos[pos].type = type;

	vec->tamanho++;

	return pos;
}

