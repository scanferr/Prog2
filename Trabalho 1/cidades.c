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

	int i, position, j;

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
		int i;
		int j;
		cidade temp;
		int n = vec->tamanho;

		if (criterio == 'a')
		{
			for (i = 0; i < (n - 1); i++)
			{
				for (j = 0; j < (n - i - 1); j++)
				{
					//Compare the adjacent positions
					if ((vec->elementos[j].area > vec->elementos[j + 1].area || (vec->elementos[j].area==vec->elementos[j+1].area && vec->elementos[j].populacao > vec->elementos[j+1].populacao)))
					{
						//Swap the numbers
						temp = vec->elementos[j]; // Temporary variable to hold the current number
						vec->elementos[j] = vec->elementos[j+1]; // Replace current number with adjacent number
	        			vec->elementos[j + 1] = temp; // Replace adjacent number with current number
	        			//printf("%d\n", temp);
					}
				}
			}
		}

		if (criterio == 'p')
			{
				for (i = 0; i < (n - 1); i++)
				{
					for (j = 0; j < (n - i - 1); j++)
					{
						if ((strcmp(vec->elementos[j].pais, vec->elementos[j + 1].pais) > 0) || (strcmp(vec->elementos[j].pais, vec->elementos[j + 1].pais) == 0 && vec->elementos[j].populacao > vec->elementos[j+1].populacao))
						{
							temp = vec->elementos[j];
							vec->elementos[j] = vec->elementos[j + 1];
							vec->elementos[j + 1] = temp;
						}
					}
				}
			}

		return 0;
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
	int i, pop, j, l, pos;
	//tamanho maximo do vetor com as cidades iguais. Como nao sabemos quantas cidades podem ser, aloca-se vetor para 1173 elementos(maximo)
	int totalstrings=1173;
	//cria o vetor auxiliar com as cidades iguais
	char **igual = (char**)malloc(sizeof(char*)*totalstrings);

	//aloca espaço para cada string, dentro do vetor
	for(i=0; i<totalstrings; i++)
	{
		igual[i]= (char*)malloc(sizeof(char)*totalstrings);
	}

	//percorre os nomes das cidades todos e quando encontra a cidade a pesquisar, guarda a sua populacao e a posicao onde esta
	for (i=0; i<vec->tamanho; i++)
	{
		if(strcmp(vec->elementos[i].nome, nomecidade)==0)
		{
		pop = vec->elementos[i].populacao;
		pos = i;

		}
	}

	//compara as populacoes das cidades todas e ve se estao entre o intervalo -delta e + delta, rejeitando a cidade a pesquisar (na posicao pos)
	for (i=0; i<vec->tamanho; i++)
	{
		if(vec->elementos[i].populacao <= pop + deltapop && vec->elementos[i].populacao >= pop - deltapop && i != pos)
		{
			//copia o valor das cidades com populacao dentro da gama para o vetor criado anteriormente
			strcpy(igual[l], vec->elementos[i].nome);
			//a funcao tem como atributo o numero de cidades encontrada, tem que contar
			l++;
		}
	}

	//retorna o numero de cidades dentro da gama (atributo da funcao)

	*nsimilares=l;

	//TESTES
	//j=vec->elementos[1192].populacao;
	//printf("%d\n", pop);
	//printf("Pop do Porto e %d\n", j);

	//imprime o vetor com as cidades
	return igual;
	//limpa a memoria do vetor criado, dado que criamos vetor para 1173 elementos
	free(igual);
}
