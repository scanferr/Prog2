/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "cidades.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

		close(f);

		return i;

}

int cidades_peek(const char *nomef, const char *nomecidade, cidade *resultado)
{
		FILE *f;
		cidade c;
		int position = 0;

		f = fopen (nomef, "rb");

		if(f == NULL)
		{
			printf("Impossivel abrir o ficheiro!\n");
			return -1;
		}

		while (fread(&c, sizeof(cidade),1, f) == 1)
		{
			if(strcmp(nomecidade, c.nome) == 0)
				return position;

			position++;
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
	int cont = 0;
	f = fopen(nomef, "rb+");

	   if(f == NULL)
	     {
		   printf("Impossivel abrir o ficheiro!\n");
		   return -1;
	     }


	   while(fread(&c, sizeof(cidade), 1, f) == 1)
	     {
		   	if(strcmp(nomecidade, c.nome) == 0)
	          {
	              // printf("%s\n", nomecidade);
	               break;

	          }

	            cont += sizeof(cidade);
	      }

	        fseek(f, cont, SEEK_SET);
	        fwrite(&nova ,sizeof(cidade), 1, f);
	        fclose(f);
	        return cont;

}

int cidades_resort(vetor *vec, char criterio)
{
  return -1;
}

char** cidades_similar (vetor *vec, const char *nomecidade, int deltapop, int *nsimilares)
{
  return NULL;
}
