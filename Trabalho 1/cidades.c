/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "cidades.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
 * coloca num vetor inicialmente vazio a informacao contida em ficheiro binario
 * parametro: nomef nome do ficheiro
 * retorno: apontador para o vetor criado
 * nota: se existe erro na leitura do ficheiro ou vetor nao foi criado retorna NULL
 */

vetor* cidades_load(const char *nomef)
{
		FILE *f;
		cidade c;

		f = fopen (nomef, "rb");

		if(f == NULL)
		{
			printf("Impossivel abrir o ficheiro!\n");
			return NULL;
		}

		vetor *cidades = vetor_novo();

		while (fread(&c, sizeof(cidade),1, f) == 1)
		{
			if (vetor_insere(cidades, c, cidades->tamanho) == -1)
				return NULL;
		}

		fclose(f);

		return cidades;

}


/**
 * coloca num ficheiro binario inicialmente vazio a informacao contida no vetor
 * parametro: nomef nome do ficheiro
 * parametro: vec apontador para o vetor
 * retorno: -1 se aconteceu algum erro ou numero de elementos guardados no ficheiro
 */

int cidades_save(const vetor *vec, const char *nomef)
{

		FILE *f;
		vetor *cidades;
		int i;

		f = fopen (nomef, "wb");

		if(f == NULL)
		{
			printf("Impossivel abrir o ficheiro!\n");
			return -1;
		}

		for (i = 0; i < vec->tamanho; i++)
		{
			fwrite(&vec->elementos[i], sizeof(cidade),1, f);
		}

		fclose(f);

		return i;

}

/**
*  pesquisa um elemento (cidade) diretamente no ficheiro
*  parametro: nomef nome do ficheiro
*  parametro: nomecidade nome da cidade a pesquisar
*  parametro: resultado cidade encontrada (por referencia)
*  retorno: posicao do elemento encontrado no ficheiro ou -1 se ocorrer algum erro ou nao encontrar elemento
*/

int cidades_peek(const char *nomef, const char *nomecidade, cidade *resultado)
{
		FILE *f;
		int position = 0, i=0;

		f = fopen (nomef, "rb");

		if(f == NULL)
		{
			printf("Impossivel abrir o ficheiro!\n");
			return -1;
		}

		 vetor *v = cidades_load(nomef);

		for (position=0; position < vetor_tamanho(v); position++)
		{
			if(strcmp(nomecidade, v->elementos[position].nome)==0)
			{
				resultado[i] = v->elementos[position];

				return position;
			}

		}

		fclose(f);
		return -1;

}


/**
*  altera o valor de um elemento (cidade) diretamente no ficheiro, sem garantir que se mantem ordenado
*  parametro: nomef nome do ficheiro
*  parametro: nomecidade nome da cidade a alterar
*  parametro: novo elemento (cidade) a substituir a cidade original
*  retorno: posicao do elemento alterado no ficheiro ou -1 se ocorrer algum erro ou nao encontrar elemento
*/

int cidades_poke(const char *nomef, const char *nomecidade, cidade nova)
{
	FILE *f;
	cidade c;
	int cont, i, position, j;
	f = fopen(nomef, "rb+");

	   if(f == NULL)
	     {
		   printf("Impossivel abrir o ficheiro!\n");
		   return -1;
	     }

	 vetor *v = cidades_load(nomef); //carrega num vetor o ficheiro

	 i = cidades_peek(nomef,nomecidade,&c); //atribui a i a posiçao da cidade

	 v->elementos[i]=nova; //elementos i passa a ser a cidade nova

	 //Testes

	 //printf("%s\n", nova.nome);
	 //printf("%s\n", nova.pais);
	 //printf("%d\n", nova.populacao);
	 //printf("%d\n", nova.area);

	 //fwrite(&c, sizeof(cidade),1, f);
	 //printf("%d\n", i);

	 j = cidades_save(v,nomef); //guarda no ficheiro os vetores actualizados

	 fclose(f);

	 return i; //retorna a posicao

}

/**
*  reordena o vetor de cidades crescentemente, de acordo com criterio especificado
*  parametro: vec apontador para vetor
*  parametro: criterio carater que indica o criterio de ordenacao
*             se 'p', ordena por pais e, em caso de empate, por populacao ;
*             se 'a', ordena por area e, em caso de empate, por populacao
*  retorno: -1 se ocorrer um erro ou 0 se for bem sucedido
*/

int cidades_resort(vetor *vec, char criterio)
{
  return -1;
}


/**
procura as cidades similares em populacao a uma cidade especificada
 * parametro: vec apontador para o vetor de cidades
*  parametro: nomecidade nome da cidade referencia
*  parametro: deltapop diferenca maxima (valor absoluto) em populacao relativamente 'a populacao da cidade referencia
*  parametro: nsimilares numero de resultados encontrados (por referencia)
*  retorno: vetor(array) de strings com o nome das cidades encontradas
*           as cidades retornadas mantem a ordem em que estavam guardadas no vetor original
*  nota: se cidade referencia nao existe ou nao encontra cidades similares, retorna NULL
*/

char** cidades_similar (vetor *vec, const char *nomecidade, int deltapop, int *nsimilares)
{
  return NULL;
}
