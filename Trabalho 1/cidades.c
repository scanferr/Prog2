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
 * parametro: first_city apontador para primeira cidade
 * parametro: second_city apontador para segunda cidade
 * retorno: sem retorno (void)
 * nota: funcao auxiliar
 */

void city_swap(cidade *first_city, cidade *second_city)
{

	cidade temporary_city = *first_city;
    *first_city = *second_city;
    *second_city = temporary_city;
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
    int array_size;

    file = fopen (nomef, "wb");

    if (file == NULL)
    {
        printf("Impossível abrir o ficheiro!\n");
        return -1;
    }

    array_size = vetor_tamanho(vec);

    for (i = 0; i < array_size; i++)
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
    int array_size;

    file = fopen (nomef, "rb");

    if(file == NULL)
    {
        printf("Impossível abrir o ficheiro!\n");
        return -1;
    }

    vetor *cities_array = cidades_load(nomef);

    array_size = vetor_tamanho(cities_array);

    for (i = 0; i < array_size; i++)
    {
        if (strcmp(nomecidade, cities_array->elementos[i].nome) == 0)
        {
        	//printf("Resultado antes e: %s %s %d %d\n", resultado->nome, resultado->pais, resultado->populacao, resultado->area);
        	resultado[0] = cities_array->elementos[i];
            //printf("Resultado depois e: %s %s %d %d\n", resultado->nome, resultado->pais, resultado->populacao, resultado->area);
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
	int array_size = vec->tamanho;

	if (criterio == 'a')
	{
		for (i = 0; i < (array_size - 1); i++)
		{
			for (j = 0; j < (array_size - i - 1); j++)
			{
				//Comparar areas

				if ((vec->elementos[j].area > vec->elementos[j + 1].area || (vec->elementos[j].area==vec->elementos[j + 1].area && vec->elementos[j].populacao > vec->elementos[j + 1].populacao)))
				{
					city_swap(&vec->elementos[j], &vec->elementos[j + 1]);
				}
			}
		}
		return 0;
	}

	if (criterio == 'p')
	{
		for (i = 0; i < (array_size - 1); i++)
		{
			for (j = 0; j < (array_size - i - 1); j++)
			{
				//Comparar paises

				if ((strcmp(vec->elementos[j].pais, vec->elementos[j + 1].pais) > 0) || (strcmp(vec->elementos[j].pais, vec->elementos[j + 1].pais) == 0 && vec->elementos[j].populacao > vec->elementos[j + 1].populacao))
				{
					city_swap(&vec->elementos[j], &vec->elementos[j + 1]);
				}
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
	int cidade_populacao;
	int cidade_posicao;
	int num_cidades_similares = 0;
	// tamanho maximo do vetor com as cidades iguais. Como nao sabemos quantas cidades podem ser, aloca-se vetor para 1173 elementos(maximo)
	int total_cidades = 1173;
	// cria o vetor auxiliar com as cidades iguais
	char **cidades_similares = (char**)malloc(sizeof(char*) * total_cidades);

	//aloca espaço para cada string, dentro do vetor
	for (i = 0; i < total_cidades; i++)
	{
		cidades_similares[i] = (char*)malloc(sizeof(char) * total_cidades);
	}

	//percorre os nomes das cidades todos e quando encontra a cidade a pesquisar, guarda a sua populacao e a posicao onde esta
	for (i = 0; i < vec->tamanho; i++)
	{
		if (strcmp(vec->elementos[i].nome, nomecidade) == 0)
		{
			cidade_populacao = vec->elementos[i].populacao;
			cidade_posicao = i;
		}
	}

	//compara as populacoes das cidades todas e ve se estao entre o intervalo -delta e +delta, rejeitando a cidade a pesquisar (na posicao pos)
	for (i = 0; i < vec->tamanho; i++)
	{
		if (vec->elementos[i].populacao <= cidade_populacao + deltapop && vec->elementos[i].populacao >= cidade_populacao - deltapop && i != cidade_posicao)
		{
			//copia o valor das cidades com populacao dentro da gama para o vetor criado anteriormente
			strcpy(cidades_similares[num_cidades_similares], vec->elementos[i].nome);
			//a funcao tem como atributo o numero de cidades encontrada, tem que contar
			num_cidades_similares++;
		}
	}

	//retorna o numero de cidades dentro da gama (atributo da funcao)
	*nsimilares = num_cidades_similares;

	return cidades_similares;

	//limpa a memoria do vetor criado, dado que criamos vetor para 1173 elementos
	free(cidades_similares);
}

