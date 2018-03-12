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
 * troca a posicao de duas cidades
 * parametro: first apontador para primeira cidade
 * parametro: second apontador para segunda cidade
 * retorno: sem retorno (void)
 * nota: funcao auxiliar
 */
void city_swap(cidade *first, cidade *second)
{
    cidade temporary_city = *first;
    *first = *second;
    *second = temporary_city;
}

/**
 * ordena por area e em caso de empate por populacao
 * parametro: first_city apontador para primeira cidade
 * parametro: second_city apontador para segunda cidade
 * retorno: sem retorno (void)
 * nota: funcao auxiliar
 */
void sort_area(cidade *first_city, cidade *second_city)
{
    if ((first_city->area > second_city->area) || (first_city->area == second_city->area && first_city->populacao > second_city->populacao))
    {
        city_swap(first_city, second_city);
    }
}

/**
 * ordena por pais e em caso de empate por populacao
 * parametro: first_city apontador para primeira cidade
 * parametro: second_city apontador para segunda cidade
 * retorno: sem retorno (void)
 * nota: funcao auxiliar
 */
void sort_country(cidade *first_city, cidade *second_city)
{
    if ((strcmp(first_city->pais, second_city->pais) > 0) || (strcmp(first_city->pais, second_city->pais) == 0 && first_city->populacao > second_city->populacao))
    {
        city_swap(first_city, second_city);
    }
}

/**
 * coloca num vetor inicialmente vazio a informacao contida em ficheiro binario
 * parametro: nomef nome do ficheiro
 * retorno: apontador para o vetor criado
 * nota: se existe erro na leitura do ficheiro ou vetor nao foi criado retorna NULL
 */
vetor* cidades_load(const char *nomef)
{
    FILE *file;
    cidade city;

    file = fopen (nomef, "rb");
    if (file == NULL)
    {
        printf("Impossível abrir o ficheiro!\n");
        return NULL;
    }

    vetor *cities = vetor_novo();
    while (fread(&city, sizeof(city), 1, file) == 1)
    {
        if (vetor_insere(cities, city, -1) == -1)
        {
            fclose(file);
            return NULL;
        }
    }

    fclose(file);
    return cities;
}

/**
 * coloca num ficheiro binario inicialmente vazio a informacao contida no vetor
 * parametro: nomef nome do ficheiro
 * parametro: vec apontador para o vetor
 * retorno: -1 se aconteceu algum erro ou numero de elementos guardados no ficheiro
 */
int cidades_save(const vetor *vec, const char *nomef)
{
	FILE *file;
	int i;

	file = fopen (nomef, "wb");

	if (file == NULL)
	{
	        printf("Impossível abrir o ficheiro!\n");
	        return -1;
	}

	for (i = 0; i < vetor_tamanho(vec); i++)
	{
	        fwrite(&vec->elementos[i], sizeof(cidade), 1, file);
	}

	fclose(file);
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
	FILE *file;
	int i;

	file = fopen (nomef, "rb");

	if(file == NULL)
	{
	        printf("Impossível abrir o ficheiro!\n");
	        return -1;
	}

	vetor *cities_array = cidades_load(nomef);

	for (i = 0; i < vetor_tamanho(cities_array); i++)
	{
	        if (strcmp(nomecidade, cities_array->elementos[i].nome) == 0)
	        {
	            resultado[0] = cities_array->elementos[i];
	            fclose(file);
	            return i;
	        }
	}

	fclose(file);
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
    FILE *file;
    cidade city;
    int position;

    file = fopen(nomef, "rb+");
    if (file == NULL)
    {
        printf("Impossível abrir o ficheiro!\n");
        return -1;
    }

    vetor *cities_array = cidades_load(nomef);
    position = cidades_peek(nomef, nomecidade, &city);
    vetor_atribui(cities_array, position, nova);
    cidades_save(cities_array, nomef);

    fclose(file);
    return position;
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
    int array_size = vetor_tamanho(vec);

    switch(criterio)
    {
    	case 'a':
                for (i = 0; i < (array_size - 1); i++)
                {
                    for (j = 0; j < (array_size - i - 1); j++)
                    {
                        sort_area(&vec->elementos[j], &vec->elementos[j + 1]);
                    }
                }
                return 0;

        case 'p':
        		for (i = 0; i < (array_size - 1); i++)
        	    {
        	        for (j = 0; j < (array_size - i - 1); j++)
        	        {
        	            sort_country(&vec->elementos[j], &vec->elementos[j + 1]);
        	        }
        	    }
        	    return 0;
    }

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
	int i;
	int pop_city;
	int pos_city;
	int similar_city = 0;

	int array_size = vetor_tamanho(vec);

	char **similar_array = (char**)malloc(sizeof(char*) * array_size);

	
	for (i = 0; i < array_size; i++)
	{
		similar_array[i] = (char*)malloc(sizeof(char) * array_size);
	}
	
	for (i = 0; i < array_size; i++)
	{
		if (strcmp(vec->elementos[i].nome, nomecidade) == 0)
		{
			pop_city = vec->elementos[i].populacao;
			pos_city = i;
		}
	}

	for (i = 0; i < array_size; i++)
	{
		if (vec->elementos[i].populacao <= pop_city + deltapop && vec->elementos[i].populacao >= pop_city - deltapop && i != pos_city)
		{
			strcpy(similar_array[similar_city], vec->elementos[i].nome);
			similar_city++;
		}
	}
	*nsimilares = similar_city;
	return similar_array;
}

